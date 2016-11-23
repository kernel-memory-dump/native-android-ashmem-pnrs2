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
#define LOG_TAG "BnExample"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BnExample.h"

using namespace android;

status_t BnExample::onTransact(uint32_t code, const Parcel& data,
        Parcel* reply, uint32_t flags __attribute__((unused)))
{
    ALOGV("%s enter: code = %d", __FUNCTION__, code);

    data.checkInterface(this);
    
    // KOJU FUNKCIJU TREBA POZVATI, MORA DA BUDE ENUM 
    // ARRGUMENT SE NALAZI U data
    // MOZEMO DA SA READ UCITATI
    switch(code)
    {
        
        case GET_EXAMPLE:
        {
            int32_t example = getExample();

            reply->writeNoException();
            reply->writeInt32(example);

            break;
        }
        case SET_EXAMPLE:
        {

            int32_t argument;
            data.readInt32(&argument);
            int32_t example = getExample();
            ALOGD("%s WORKING - RECEIVED ARGUMENT: %d, SENDING ARGUMENT BACK %d ", __FUNCTION__, argument, example);
            reply->writeNoException();
            reply->writeInt32(argument);
            break;
        }
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

    }

    ALOGV("%s exit", __FUNCTION__);
    return NO_ERROR;
}
