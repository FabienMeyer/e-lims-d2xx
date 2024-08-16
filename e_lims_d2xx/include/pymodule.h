#ifndef PYMODULE_H
#define PYMODULE_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "device.h"
 
///////////////////////////////////////////////////////////////////////////////
// External variables declaration
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Ftd2xx exception (Ftd2xxError)
 */
extern PyObject *Ftd2xxError;


#endif // _PYMODULE_H
 