#define LOG_NDEBUG 0
#define LOG_TAG "BnExample"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BnNativeServiceServer.h"

using namespace android;

status_t BnNativeServiceServer::onTransact(uint32_t code, const Parcel& data,
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
            sp<INativeCallback> callback = interface_cast<INativeCallback>(data.readStrongBinder());
            // call underlying implementation
            registerCallback(callback);
            
            reply->writeNoException();
            break;
        }

    }

    ALOGV("%s exit", __FUNCTION__);
    return NO_ERROR;
}
