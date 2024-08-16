#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <ftd2xx.h>
#include "pymodule.h"
#include "pyclass_device.h"
#include "device.h"


#include <stdlib.h>
#include <stdint.h>


/**
 * @brief Method get_information docstring
 */
static const char method_get_information_doc[] = \
"get_information(self, index: int) -> Tuple[int, int, int, int, str, str]\n\
\n\
Get the device information\n\
\n\
:param index: The device index\n\
:type index: int\n\
\n\
:return: A tuple containing the device information as follow (from first to last elements):\n\
\n\
    * flags, int, the device flags\n\
    * type, int, the device type\n\
    * id, int, the device ID\n\
    * loc_id, int, the locations ID\n\
    * serial_number, str, the serial number\n\
    * description, str, the device description\n\
\n\
:rtype: (int, int, int, int, str, str)\n\
\n\
:raises FtError: when the info could not be read.\n\
\n";
static PyObject *method_get_information(Ftd2xxDeviceObject_t *self, PyObject *args)
{
    FT_STATUS ftStatus = FT_OK;
    int index;
    device_information_t information;

    // Parse arguments
    if(!PyArg_ParseTuple(args, "i", &index))
    {
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS

    ftStatus = get_device_information(self->handle, index, &information);

    Py_END_ALLOW_THREADS

    if(ftStatus != FT_OK)
    {
        // Failed to read the device information.
        PyErr_SetString(Ftd2xxError, "Failed to read the device information.");
        return NULL;
    }

    PyObject *rTuple = PyTuple_New(6);

    PyTuple_SetItem(rTuple, 0, PyLong_FromUnsignedLong(information.flags));
    PyTuple_SetItem(rTuple, 1, PyLong_FromUnsignedLong(information.type));
    PyTuple_SetItem(rTuple, 2, PyLong_FromUnsignedLong(information.id));
    PyTuple_SetItem(rTuple, 3, PyLong_FromUnsignedLong(information.loc_id));
    PyTuple_SetItem(rTuple, 4, PyUnicode_FromString(information.serial_number));
    PyTuple_SetItem(rTuple, 5, PyUnicode_FromString(information.description));

    return rTuple;
}


/**
 * @brief Class Ftd2xxDevice docstring
 */
static const char class_ftd2xx_device_doc[] = \
"Ftd2xxDevice()\n\
\n\
The class Ftd2xxDevice is the base class for the other classes and should not be used directly.\n\
\n";


/**
 * @brief Ftd2xxDevice members
 *
 */
static PyMemberDef members_device[] = {
    {"handle", T_ULONGLONG, offsetof(Ftd2xxDeviceObject_t, handle), 0, "The device handle (T_ULONGLONG)"},
    {NULL, 0, 0, 0, NULL} // Sentinel
};


/**
 * @brief Ftd2xxDevice methods
 */
static PyMethodDef methods_device[] = {
    {"get_information", (PyCFunction)method_get_information, METH_VARARGS, method_get_information_doc},
    {NULL, NULL, 0, NULL} // Sentinel
};


/**
 * @brief Init method
 */
static int Ftd2xxDevice_init(Ftd2xxDeviceObject_t *self, PyObject *args, PyObject *kwds)
{
    //if(!PyArg_ParseTuple(args, "i", &self->loc))
    //    return -1;

    return 0;
}


PyTypeObject Ftd2xxDevice_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "e_lims_d2xx.Ftd2xxDevice",
    .tp_doc = class_ftd2xx_device_doc,
    .tp_basicsize = sizeof(Ftd2xxDeviceObject_t),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)Ftd2xxDevice_init,
    .tp_members = members_device,
    .tp_methods = methods_device,
};
