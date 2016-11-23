/***************************************************************************
 *
 *
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                 Version 2, December 2004
 *
 *      Everyone is permitted to copy and distribute verbatim or modified
 *      copies of this license document, and changing it is allowed as long
 *      as the name is changed.
 *
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE, TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *         0. You just DO WHAT THE FUCK YOU WANT TO
 *
 *  -----------------------------------------------------
 *  Sebastian Novak @ GitHub https://github.com/kernel-memory-dump
 *  -----------------------------------------------------
 *
 *
 * @author  Sebastian Novak
 *
 *
 ****************************************************************************/

#define LOG_NDEBUG 0
#define LOG_TAG "BnNativeService"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BnNativeService.h"

using namespace android;

status_t BnNativeService::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags __attribute__((unused)))
{
    ALOGV("%s enter: code = %d", __FUNCTION__, code);

    // assert client has valid interface
    data.checkInterface(this);
    
    // 
    switch(code)
    {
        case REGISTER_CALLBACK:
        {
            ALOGV("%s enter: code REGISTER CALLBCACK", __FUNCTION__);
            sp<INativeCallback> callback = interface_cast<INativeCallback>(data.readStrongBinder());
            // call underlying implementation
            registerCallback(callback);
            ALOGV("%s enter: code REGISTER CALLBCACK - ALL OK, writeNoException!", __FUNCTION__);
            reply->writeNoException();
            break;
        }
        case LOAD_IMAGE_ASYNC:
        {

            ALOGV("%s enter: code LOAD_IMAGE_ASYNC", __FUNCTION__);
            // call underlying implementation
            int32_t fd = data.readFileDescriptor();
            char *imgPath;
            imgPath = (char *) data.readCString();
            ALOGV("fd is: %x , imgPath: %s", fd, imgPath);
            loadImageAsync(fd, imgPath);
            // client will be notified via callback 
            reply->writeNoException();
            break;
        }
        default:
        {
            ALOGE("BN RECEIVED UNKNOWN TRANSACTION CODE: %d", code);
            return UNKNOWN_TRANSACTION; // indicate error
        }

    }

    ALOGV("%s exit", __FUNCTION__);
    return NO_ERROR;
}
