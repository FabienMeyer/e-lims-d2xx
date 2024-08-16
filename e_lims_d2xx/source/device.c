
#include <ftd2xx.h>
#include "device.h"

FT_STATUS get_device_information(FT_HANDLE ftHandle, uint32_t id, device_information_t* information)
{
    FT_STATUS ftStatus;
    FT_HANDLE ftHandleTemp;
    DWORD numDevs;

    // create the device information list
    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    // get device informations
    ftStatus = FT_GetDeviceInfoDetail(id, &information->flags, &information->type,
        &information->id, &information->loc_id, information->serial_number, information->description, &ftHandleTemp);

    return ftStatus;
}
