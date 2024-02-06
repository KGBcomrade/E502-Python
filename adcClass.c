#include "adcClass.h"
#include <string.h>

#define ERR_INV_ARGS {\
	PyErr_SetString(PyErr_NewException("TypeError", NULL, NULL), "Invalid arguments"); \
	return NULL; \
}

void adcDealloc(t_adc *self) {
	X502_Close(self->hnd);
	X502_Free(self->hnd);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject *adcNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
	t_adc *self = (t_adc*)type->tp_alloc(type, 0);
	if(self != NULL)
		self->hnd = X502_Create();

	return (PyObject*)self;
}

int adcInit(t_adc *self, PyObject *args, PyObject *kwds) {
	int32_t err = E502_OpenUsb(self->hnd, NULL);
	if(err != X502_ERR_OK)
		return -1;
	return 0;
}

PyObject* adcSetChannelCount(PyObject *self, PyObject *args) {
	t_adc *p = (t_adc*)(self);
	int count;
	if(!PyArg_ParseTuple(args, "i", &count))
		ERR_INV_ARGS
	int32_t err = X502_SetLChannelCount(p->hnd, count);
	if(err == X502_ERR_OK)
		Py_RETURN_NONE;
	PyErr_SetString(PyErr_NewException("Error", NULL, NULL), "Error setting channels count");
	return NULL;
}

PyObject* adcSetChannel(PyObject *self, PyObject *args) {
	t_adc *p = (t_adc*)self;
	int lChannel, pChannel, avg;
	float range;
	char *mode;
	if(!PyArg_ParseTuple(args, "iisfi", &lChannel, &pChannel, &mode, &range, &avg))
		ERR_INV_ARGS
	
	char* modes[] = {"comm", "diff", "zero"};
	int modeCode = -1, rangeCode = -1;
	for(size_t i = 0; i < 3; i++) 
		if(!strcmp(modes[i], mode)) {
			modeCode = 0;
			break;
		}
	if(modeCode == -1) {
		PyErr_SetString(PyErr_NewException("ValueError", NULL, NULL), "Unrecongized mode");
		return NULL;
	}

	int rangeInt = range >= 1 ? range : range * -10; // 0.5 -> -5, 0.2 -> -2
	switch(rangeInt) {
		default:
			PyErr_SetString(PyErr_NewException("ValueError", NULL, NULL), "Unrecongized range");
			return NULL;
			break;
		case 10:
			rangeCode = X502_ADC_RANGE_10;
			break;
		case 5:
			rangeCode = X502_ADC_RANGE_5;
			break;
		case 2:
			rangeCode = X502_ADC_RANGE_2;
			break;
		case 1:
			rangeCode = X502_ADC_RANGE_1;
			break;
		case -5:
			rangeCode = X502_ADC_RANGE_2;
			break;
		case -2:
			rangeCode = X502_ADC_RANGE_2;
			break;
	}

	int32_t err = X502_SetLChannel(p->hnd, lChannel, pChannel, modeCode, rangeCode, avg);
	if(err != X502_ERR_OK) {
		PyErr_SetString(PyErr_NewException("Error", NULL, NULL), "Error setting channel");
		return NULL;
	}
	Py_RETURN_NONE;
}

PyObject* adcSetFreq(PyObject *self, PyObject *args) {
	t_adc *p = (t_adc*)self;
	double freq, freq_c;
	PyObject *freq_cI = Py_None;

	if(!PyArg_ParseTuple(args, "d|O", &freq, &freq_cI))
		ERR_INV_ARGS
	if(freq_cI != Py_None)
		freq_c = PyFloat_AsDouble(freq_cI);
	
	int32_t err = X502_SetAdcFreq(p->hnd, &freq, freq_cI == Py_None ? NULL : &freq_c);
	if(err != X502_ERR_OK) {
		PyErr_SetString(PyErr_NewException("Error", NULL, NULL), "Error setting frequency");
		return NULL;
	}
	return PyFloat_FromDouble(freq);
}

PyObject* adcConfigure(PyObject *self, PyObject *args) {
	t_adc *p = (t_adc*)self;
	int32_t err = X502_Configure(p->hnd, 0);
	if(err != X502_ERR_OK) {
		PyErr_SetString(PyErr_NewException("Error", NULL, NULL), "Error configuring ADC");
		return NULL;
	}
	Py_RETURN_NONE;
}

PyObject* adcAsyncGetFrame(PyObject *self, PyObject *args, PyObject *kws) {
	t_adc *p = (t_adc*)self;
	char* keys[] = {"volts", "timeout", NULL};	
	PyObject *voltsI = Py_None, *timeoutI = Py_None;
	if(!PyArg_ParseTupleAndKeywords(args, kws, "|OO", keys, &voltsI, &timeoutI))
		ERR_INV_ARGS
	int volts, timeout;
	if(voltsI == Py_None)
		volts = 1;
	else
		volts = PyLong_AsLong(voltsI);
	if(timeoutI == Py_None)
		timeout = 1000;
	else
		timeout = PyLong_AsLong(timeoutI);

	//Channel count
	int cc = -1;
	int32_t err = X502_GetLChannelCount(p->hnd, &cc);
	//Reading
	if(err == X502_ERR_OK) {
		double *buf = calloc(cc, sizeof(double));
		err = X502_AsyncGetAdcFrame(p->hnd, volts ? X502_PROC_FLAGS_VOLT : 0, timeout, buf);
		if(err == X502_ERR_OK) {
			PyObject* list = PyList_New(cc);
			for(size_t i = 0; i < cc; i++)
				PyList_SetItem(list, i, PyFloat_FromDouble(buf[i]));
			free(buf);

			return list;
		}
	}
	PyErr_SetString(PyErr_NewException("Error", NULL, NULL), "Error reading frame");
	return NULL;
}
