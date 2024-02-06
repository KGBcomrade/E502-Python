#include <Python.h>
#include "adcClass.h"
#include <structmember.h>
#include <x502api.h>
#include <e502api.h>


static PyMethodDef adcMethods[] = {
	{"setChannelCount", adcSetChannelCount, METH_VARARGS, NULL},
	{"setChannel", adcSetChannel, METH_VARARGS, NULL},
	{"setFreq", adcSetFreq, METH_VARARGS, NULL},
	{"configure", adcConfigure, METH_VARARGS, NULL},
	{"asyncGetFrame", adcAsyncGetFrame, METH_VARARGS | METH_KEYWORDS, NULL},
	{NULL}
};

static PyTypeObject adc_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "adc.ADC",               	    /* tp_name */
    sizeof(t_adc),                  /* tp_basicsize */
    0,                              /* tp_itemsize */
    (destructor)adcDealloc,         /* tp_dealloc */
    0,                              /* tp_vectorcall_offset */
    0,                              /* tp_getattr */
    0,                              /* tp_setattr */
    0,                              /* tp_as_async */
    0,                              /* tp_repr */
    0,                              /* tp_as_number */
    0,                              /* tp_as_sequence */
    0,                              /* tp_as_mapping */
    0,                              /* tp_hash */
    0,                              /* tp_call */
    0,                              /* tp_str */
    0,                              /* tp_getattro */
    0,                              /* tp_setattro */
    0,                              /* tp_as_buffer */
    0,                              /* tp_flags */
    0,                              /* tp_doc */
    0,                              /* tp_traverse */
    0,                              /* tp_clear */
    0,                              /* tp_richcompare */
    0,                              /* tp_weaklistoffset */
    0,                              /* tp_iter */
    0,                              /* tp_iternext */
    adcMethods,                     /* tp_methods */
    0,                              /* tp_members */
    0,                              /* tp_getset */
    0,                              /* tp_base */
    0,                              /* tp_dict */
    0,                              /* tp_descr_get */
    0,                              /* tp_descr_set */
    0,                              /* tp_dictoffset */
    (initproc) adcInit,             /* tp_init */
    0,                              /* tp_alloc */
    adcNew,                         /* tp_new */
};

static struct PyModuleDef module = {
	PyModuleDef_HEAD_INIT,
	"adc",
	NULL,
	-1,
	NULL
};

PyMODINIT_FUNC PyInit_adc() {
	PyObject *m = PyModule_Create(&module);
	if(m == NULL)
		return NULL;
	if(PyType_Ready(&adc_Type) < 0)
		return NULL;

	Py_INCREF(&adc_Type);
	PyModule_AddObject(m, "adc", (PyObject*) &adc_Type);

	return m;
}
