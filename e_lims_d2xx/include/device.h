#ifndef _DEVICE_H
#define _DEVICE_H

#include <ftd2xx.h>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Types definition
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    DWORD flags;
    DWORD type;
    DWORD id;
    DWORD loc_id;
    char serial_number[64];
    char description[64];
} device_information_t;


/**
 * @brief Get the device information.
 *
 * @param ftHandle The device handle
 * @param id The device id
 * @param information A pointer to device_information_t where the information will be written
 * @return The status of the operation
 */
FT_STATUS get_device_information(FT_HANDLE ftHandle, uint32_t id, device_information_t* information);

#endif // _DEVICE_H