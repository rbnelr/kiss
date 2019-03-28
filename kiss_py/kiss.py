
def copy_dll():
	import os
	from shutil import copyfile

	try:
		dir = "../x64/Debug"
		for f in os.listdir(dir):
			copyfile(dir +"/"+ f, f)
	except:
		pass
	
	try:
		dir = "../x64/Release"
		for f in os.listdir(dir):
			copyfile(dir +"/"+ f, f)
	except:
		pass

copy_dll()

import kiss_c

open_window = kiss_c.open_window
close_window = kiss_c.close_window
swap_buffers = kiss_c.swap_buffers

def get_input():
	inp_dict = kiss_c.get_input()
	inp = type("Input", (), {})()
	inp.__dict__ = inp_dict
	return inp

