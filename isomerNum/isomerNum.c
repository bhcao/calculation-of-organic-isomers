#include <Python.h>
#include "listAll.h"
#include "quickCount.h"
static PyObject *isomerNum_alkane(PyObject *self, PyObject *args){
    int numC;
    if(!PyArg_ParseTuple(args,"i",&numC))
        return NULL;
    return (PyObject*)Py_BuildValue("i",alkane(numC));
}

static PyMethodDef isoMethod[] = {
    {"alkane",isomerNum_alkane,METH_VARARGS},
    {NULL,NULL}
};

static struct PyModuleDef isoModule = {
    PyModuleDef_HEAD_INIT,
    "isomerNum",
    NULL,
    -1,
    isoMethod
};

PyMODINIT_FUNC
PyInit_isomerNum(void){
    PyObject *m;
    m = PyModule_Create(&isoModule);
    return m;
}
// An example of python/c api -- https://blog.csdn.net/xiaozoom/article/details/83097136
