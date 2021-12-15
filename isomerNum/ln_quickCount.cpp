#include <Python.h>
#include "quickCount.h"

static PyObject *quickCount_alkane(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",qct::alkane(numC));
}

static PyObject *quickCount_alkene(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",qct::alkene(numC));
}

static PyObject *quickCount_alkyl(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",qct::alkyl(numC));
}

static PyObject *quickCount_monoAlkene(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",qct::monoAlkene(numC));
}

static PyObject *quickCount_cycloAlk(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",qct::cycloAlk(numC));
}

static PyMethodDef qctMethod[] = {
    {"alkane",quickCount_alkane,METH_VARARGS},
    {"alkene",quickCount_alkene,METH_VARARGS},
    {"alkyl",quickCount_alkyl,METH_VARARGS},
    {"monoAlkene",quickCount_monoAlkene,METH_VARARGS},
    {"cycloAlk",quickCount_cycloAlk,METH_VARARGS},
    {NULL,NULL}
};

static struct PyModuleDef qctModule = {
    PyModuleDef_HEAD_INIT,
    "quickCount",
    NULL,
    -1,
    qctMethod
};

PyMODINIT_FUNC
PyInit_quickCount(void){
    PyObject *m;
    m = PyModule_Create(&qctModule);
    return m;
}
