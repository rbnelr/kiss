#include "kiss.hpp"

#include <Python.h>
#include "structmember.h"

PyDoc_STRVAR(kiss_open_window_doc,
"open_window(caption: string, initial_size: (int, int) | None, initial_pos: (int, int) | None) -> None\n\n"
"Opens a window and sets up a OpenGL context in it OpenGL 4.2 for now");

PyObject* kiss_open_window(PyObject* self, PyObject* args, PyObject* kwargs) {
	LPCWSTR caption;
	iv2 initial_size = default_size;
	iv2 initial_pos = default_pos;

	static char* keywords[] = { "caption", "initial_size", "initial_pos", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "u|(ii)(ii)", keywords, &caption, &initial_size.x,&initial_size.y, &initial_pos.x,&initial_pos.y)) {
        return NULL;
    }

	open_window(caption, initial_size, initial_pos);

    Py_RETURN_NONE;
}


PyDoc_STRVAR(kiss_close_window_doc,
"close_window() -> None\n\n"
"Closes the window\n"
"(the library tries to close the window 'properly' when it exits even if you do not call this)");

PyObject* kiss_close_window(PyObject* self, PyObject* args) {
	close_window();

	Py_RETURN_NONE;
}

PyDoc_STRVAR(kiss_swap_buffers_doc,
			 "swap_buffers() -> None\n\n"
			 "Swap OpenGL buffers\n");

PyObject* kiss_swap_buffers(PyObject* self, PyObject* args) {
	swap_buffers();

	Py_RETURN_NONE;
}

#if 0 // is this needed? should i just return a dict instead?
//// Input struct

struct Py_Input {
	PyObject_HEAD

	Input	inp;
};

static void Input_dealloc (Py_Input* self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* Input_new (PyTypeObject* type, PyObject* args, PyObject* kwargs) {
	Py_Input* self;

	self = (Py_Input*)type->tp_alloc(type, 0);
	self->inp = {};

	return (PyObject*)self;
}

static int Input_init(Py_Input* self, PyObject* args, PyObject* kwargs) {
	if (!PyArg_ParseTuple(args, ""))
		return -1;

	return 0;
}

static PyMemberDef Input_members[] = {
	{"window_size",		T_OBJECT_EX,	offsetof(Py_Input, inp.window_size), 0, "Input window_size"},
	{"close",			T_BOOL,			offsetof(Py_Input, inp.close), 0, "Input close"},
	{NULL}  /* Sentinel */
};

//static PyObject* Input_foo(Py_Input* self, PyObject* args) {
//	int data;
//	PyObject* result;
//
//	if (!PyArg_ParseTuple(args, "i", &data)) {
//		return NULL;
//	}
//
//	/* We'll just return data + loc as our result. */
//	result = Py_BuildValue("i", data + self->loc);
//
//	return result;
//}
static PyMethodDef Input_methods[] = {
	//{"foo", (PyCFunction)Test_foo, METH_VARARGS,
	//"Return input parameter added to 'loc' argument from init.",
	//},
	{NULL}  /* Sentinel */
};

static PyTypeObject kiss_Input = {
	PyObject_HEAD_INIT(NULL)
	"kiss.Input",              /*tp_name*/
	sizeof(Py_Input),          /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)Input_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,/*tp_flags*/
	"MyTest objects",          /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	Input_methods,             /* tp_methods */
	Input_members,             /* tp_members */
	0,                         /* tp_getset */
	0,                         /* tp_base */
	0,                         /* tp_dict */
	0,                         /* tp_descr_get */
	0,                         /* tp_descr_set */
	0,                         /* tp_dictoffset */
	(initproc)Input_init,      /* tp_init */
	0,                         /* tp_alloc */
	Input_new,                 /* tp_new */
};

////
#endif

PyDoc_STRVAR(kiss_get_input_doc,
			 "get_input() -> Input\n\n"
			 "\n");

void dict_set (PyObject* dict, char const* key, bool val) { // key is utf8
	auto* pykey = PyUnicode_FromString(key);
	auto* pyval = PyBool_FromLong(val);

	PyDict_SetItem(dict, pykey, pyval);
}
void dict_set (PyObject* dict, char const* key, iv2 val) { // key is utf8
	auto* pykey = PyUnicode_FromString(key);
	auto* x = PyLong_FromLong(val.x);
	auto* y = PyLong_FromLong(val.y);
	auto* pytupl = PyTuple_Pack(2, x,y);

	PyDict_SetItem(dict, pykey, pytupl);
}

PyObject* kiss_get_input(PyObject* self, PyObject* args) {
	auto& inp = get_input();

	auto* inpd = PyDict_New();

	dict_set(inpd, "window_size", inp.window_size);
	dict_set(inpd, "close", inp.close);

	return inpd;
}

static PyMethodDef kiss_functions[] = {
	{ "open_window", (PyCFunction)kiss_open_window, METH_VARARGS|METH_KEYWORDS, kiss_open_window_doc },
	{ "close_window", kiss_close_window, METH_NOARGS, kiss_close_window_doc },
	{ "swap_buffers", kiss_swap_buffers, METH_NOARGS, kiss_swap_buffers_doc },
	{ "get_input", kiss_get_input, METH_NOARGS, kiss_get_input_doc },
	{ NULL, NULL, 0, NULL }
};

int exec_kiss(PyObject* module) {
	//if (PyType_Ready(&kiss_Input) < 0)
	//	return -1;
	//
	//Py_INCREF(&kiss_Input);
	//PyModule_AddObject(module, "Input", (PyObject*)&kiss_Input);

	PyModule_AddFunctions(module, kiss_functions);

	PyModule_AddStringConstant(module, "__author__", "Me");
	PyModule_AddStringConstant(module, "__version__", "0.1.0");
	//PyModule_AddIntConstant(module, "year", 2019);

	return 0; /* success */
}

PyDoc_STRVAR(kiss_c_doc,
		"A window handling and graphics library for OpenGL apps according to the KISS principle.\n"
		"(I was annoyed with existing libraries like pyglet that steal your control of the frame loop\nand want you to use their wierd timer system. Both for no apparent reason.)");

static PyModuleDef_Slot kiss_c_slots[] = {
    { Py_mod_exec, exec_kiss },
    { 0, NULL }
};

static PyModuleDef kiss_c_def = {
    PyModuleDef_HEAD_INIT,
    "kiss_c",
    kiss_c_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    kiss_c_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

#include "stdio.h"

PyMODINIT_FUNC PyInit_kiss_c() {
    return PyModuleDef_Init(&kiss_c_def);
}
