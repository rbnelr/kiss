#pragma once
#include "win32_window.hpp"
#include "clean_windows_h.hpp"
#include "move_only.hpp"
#include "assert.h"
#include "win32_window.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace kiss {
	// Queue for passing commands like open_window and close_window to the window thread, this requires the use of a win32 semaphore, since i need to wait for both windows messages and our messages/commands
	//  We can't solve this by just using PostThreadMessage, since all windows messages can be dropped when the window is being resized for ex.
	class Remote_Proc_Caller {
		NO_MOVE_COPY_CLASS(Remote_Proc_Caller);

		struct Procedure {
			std::function<void()> proc;

			std::condition_variable	cv; // condition var for producer to wait on command completion
			bool processed = false; // flag since, condition vars are subject to spurious wakeups

			Procedure () {};
		};

		HANDLE		semaphore; // to wake up windows message loop thread, when a command was pushed on the queue

		std::mutex	queue_mtx; // multiple producer single consumer queue lock
		std::queue<Procedure*> queue;

	public:

		Remote_Proc_Caller () {
			semaphore = CreateSemaphore(NULL, 0, MAXINT, NULL);
			assert(semaphore != INVALID_HANDLE_VALUE);
		}
		~Remote_Proc_Caller () {
			CloseHandle(semaphore);
		}

		// post rpc from other thread to be executed on the window thread
		void execute_on_thread (std::function<void()> proc) { // execute proc on window thread (waits till executed)
			Procedure p;
			p.proc = std::move(proc);

			std::unique_lock<std::mutex> lck(queue_mtx);
			queue.push(&p);

			auto res = ReleaseSemaphore(semaphore, 1, NULL); // wake up window thread
			assert(res != 0);

			p.cv.wait(lck, [&] { return p.processed; }); // wait for window thread to process command
		}

		// on thread
		HANDLE get_wait_for_execute_procedure_handle () {
			return semaphore;
		}
		// on thread
		void thread_execute_procedure () { // on window thread
			Procedure* proc;
			{
				std::lock_guard<std::mutex> lck(queue_mtx);

				proc = queue.front();
				queue.pop();
			} // release lock, so other threads can queue up commands while we work on the old ones

			proc->proc();

			{
				std::lock_guard<std::mutex> lck(queue_mtx);
				proc->processed = true;
				proc->cv.notify_all();
			}
		}
	};
}
