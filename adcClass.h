#ifndef ADCCLASS_H
#define ADCCLASS_H

#include <Python.h>
#include <structmember.h>
#include <stddef.h>

#include "x502api.h"
#include "e502api.h"

struct ADC {
	PyObject_HEAD
	t_x502_hnd hnd;
};

typedef struct ADC t_adc;

void adcDealloc(t_adc *self);

PyObject *adcNew(PyTypeObject *type, PyObject *args, PyObject *kwds);

int adcInit(t_adc *self, PyObject *args, PyObject *kwds);

PyObject* adcSetChannelCount(PyObject *self, PyObject *args);

PyObject* adcSetChannel(PyObject *self, PyObject *args);

PyObject* adcSetFreq(PyObject *self, PyObject *args);

PyObject* adcConfigure(PyObject *self, PyObject *args);

PyObject* adcAsyncGetFrame(PyObject *self, PyObject *args, PyObject *kws);

PyObject* adcStreamsSetEnabled(PyObject *self, PyObject *args);

PyObject* adcStreamsStart(PyObject *self, PyObject *args);

PyObject* adcStreamsStop(PyObject *self, PyObject *args);

PyObject* adcSyncGetFrame(PyObject *self, PyObject *args, PyObject *kws);

#endif
