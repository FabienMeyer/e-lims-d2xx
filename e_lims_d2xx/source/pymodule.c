#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <windows.h>
#include "pymodule.h"
#include "pyclass_device.h"

PyObject *Ftd2xxError;

/**
 * @brief Module docstring
 */
static const char moduleDoc[] = \
"Python interface for the d2xx library\n\
\n\
\n\
";

/**
 * @brief Module definition
 */
static PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "e_lims_d2xx",  // Ensure this matches the module name
    .m_doc = moduleDoc,
    .m_size = -1,
};

/**
 * @brief Module init function
 *
 * @return PyMODINIT_FUNC
 */
PyMODINIT_FUNC PyInit_e_lims_d2xx(void)  // Rename this function
{
    PyObject *m;

    if(PyType_Ready(&Ftd2xxDevice_Type) < 0)
    {
        return NULL;
    }

    m = PyModule_Create(&module);

    if(m == NULL)
    {
        return NULL;
    }

    // Add Ftd2xxDevice class
    Py_INCREF(&Ftd2xxDevice_Type);
    if(PyModule_AddObject(m, "Ftd2xxDevice", (PyObject *)&Ftd2xxDevice_Type) < 0)
    {
        Py_DECREF(&Ftd2xxDevice_Type);
        Py_DECREF(m);
        return NULL;
    }

    // Create an exception
    Ftd2xxError = PyErr_NewException("e_lims_d2xx.Ftd2xxError", NULL, NULL);
    Py_XINCREF(Ftd2xxError);
    if(PyModule_AddObject(m, "Ftd2xxError", Ftd2xxError) < 0) {
        Py_XDECREF(Ftd2xxError);
        Py_CLEAR(Ftd2xxError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}