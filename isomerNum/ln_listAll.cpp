#include <Python.h>
#include "listAll.h"

static PyObject *listAll_lsMonosub(PyObject *self, PyObject *args){
    int n;
    char* substit;
    PyObject* names = PyList_New(0);
    if(!PyArg_ParseTuple(args,"is", &n, &substit))
        return NULL;
    alkyl *from = new alkyl[n];
    from[0].setThis("\0",0);
    from[1].setThis("C",1);
    for(int i=2;i<n;i++)
        lsa::in_lsAlkylPart(&from[i], i, from);
    n--;
    if(n%3==0) // three are the same
        for(alkyl* comes = &from[n/3]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
        for(alkyl* comes3 = comes2; comes3; comes3 = comes3->next())
            PyList_Append(names, Py_BuildValue("s", lsa::in_lsMonosub(substit, comes, comes2, comes3).data()));
    for(int a=n/3+1;a<=n;a++){
        if(a<=n/2) // biggest are the same
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-2*a]; comes3; comes3 = comes3->next())
                PyList_Append(names, Py_BuildValue("s", lsa::in_lsMonosub(substit, comes, comes2, comes3).data()));
        if((n-a)%2==0) // smallest are the same
            for(alkyl* comes = &from[(n-a)/2]; comes; comes = comes->next())
            for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[a]; comes3; comes3 = comes3->next())
               PyList_Append(names, Py_BuildValue("s", lsa::in_lsMonosub(substit, comes, comes2, comes3).data()));
        int b=(n-a)/2+1;
        while(b<=n-a && b<a){
            for(alkyl* comes = &from[a]; comes; comes = comes->next())
            for(alkyl* comes2 = &from[b]; comes2; comes2 = comes2->next())
            for(alkyl* comes3 = &from[n-a-b]; comes3; comes3 = comes3->next())
                PyList_Append(names, Py_BuildValue("s", lsa::in_lsMonosub(substit, comes, comes2, comes3).data()));
            b++;
        }
    }
    delete []from;
    return names;
}

static PyObject *listAll_lsAlkene(PyObject *self, PyObject *args){
    int n;
    char* substit;
    PyObject* names = PyList_New(0);
    if(!PyArg_ParseTuple(args,"is", &n, &substit))
        return NULL;
    alkyl *from = new alkyl[n];
    from[0].setThis("\0",0);
    from[1].setThis("C",1);
    for(int i=2;i<n;i++)
        lsa::in_lsAlkylPart(&from[i], i, from);
    for(int i=1;i<n/2;i++)
        for(alkyl* comes = &from[i]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n-i]; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+substit+comes2->name()).data()));
    if(n%2==0)
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+substit+comes2->name()).data()));
    else
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n/2+1]; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+substit+comes2->name()).data()));
    delete []from;
    return names;
}

static PyObject *listAll_lsAlkenes(PyObject *self, PyObject *args){
    int n;
    PyObject* names = PyList_New(0);
    if(!PyArg_ParseTuple(args,"i", &n))
        return NULL;
    alkyl *from1 = new alkyl[n];
    from1[0].setThis("\0",0);
    from1[1].setThis("C",1);
    for(int i=2;i<n;i++)
        lsa::in_lsAlkylPart(&from1[i], i, from1);
    alkyl *from = new alkyl[n];
    from[1].setThis("C",1);
    for(int i=2;i<n;i++)
        lsa::in_lsPartAlkene(&from[i], i, from1);
    for(int i=1;i<n/2;i++)
        for(alkyl* comes = &from[i]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n-i]; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+"="+comes2->name()).data()));
    if(n%2==0)
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = comes; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+"="+comes2->name()).data()));
    else
        for(alkyl* comes = &from[n/2]; comes; comes = comes->next())
        for(alkyl* comes2 = &from[n/2+1]; comes2; comes2 = comes2->next())
            PyList_Append(names, Py_BuildValue("s", (comes->verName()+"="+comes2->name()).data()));
    delete []from;
    delete []from1;
    return names;
}

static PyMethodDef lsaMethod[] = {
    {"lsMonosub",listAll_lsMonosub,METH_VARARGS},
    {"lsAlkene",listAll_lsAlkene,METH_VARARGS},
    {"lsAlkenes",listAll_lsAlkenes,METH_VARARGS},
    {NULL,NULL}
};

static struct PyModuleDef lsaModule = {
    PyModuleDef_HEAD_INIT,
    "listAll",
    NULL,
    -1,
    lsaMethod
};

PyMODINIT_FUNC
PyInit_listAll(void){
    PyObject *m;
    m = PyModule_Create(&lsaModule);
    return m;
}
