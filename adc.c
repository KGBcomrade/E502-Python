#include <Python.h>
#include <x502api.h>
#include <e502api.h>

PyObject* ADCopen(PyObject *self, PyObject *args) {
	t_x502_hnd p = X502_Create();
	E502_OpenUsb(p, NULL);

	return PyLong_FromLong(p);
}

PyObject* ADCclose(PyObject *self, PyObject *args) {
	t_x502_hnd p;
	if(!PyArg_ParseTuple(args, "l", &p))
		return NULL;
	X502_Free(p);
	
	Py_RETURN_NONE;
}

static struct PyMethodDef methods[] = {
	{"open", (PyCFunction)ADCopen, METH_VARARGS},
	{"close", (PyCFunction)ADCclose, METH_VARARGS},
	{NULL, NULL}
};

static struct PyModuleDef module = {
	PyModuleDef_HEAD_INIT,
	"adc",
	NULL,
	-1,
	methods
};

PyMODINIT_FUNC PyInit_adc() {
	return PyModule_Create(&module);
}
