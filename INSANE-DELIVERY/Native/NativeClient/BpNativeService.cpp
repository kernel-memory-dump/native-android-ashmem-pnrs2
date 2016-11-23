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
#define LOG_TAG "BpNativeService"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BpNativeService.h"


using namespace android;


BpNativeService::BpNativeService(const sp<IBinder>& impl) :
	BpInterface<INativeService>(impl)
{

}

void BpNativeService::registerCallback(sp<INativeCallback> callback)
{
        Parcel data, reply;
        ALOGV("%s enter", __FUNCTION__);

        data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
        data.writeStrongBinder(callback->asBinder());
        
        remote()->transact(REGISTER_CALLBACK, data, &reply);
        reply.readInt32();

        ALOGV("%s exit", __FUNCTION__);

}

void BpNativeService::loadImageAsync(int32_t fd, const char* imgPath)
{
        Parcel data, reply;
        ALOGV("%s enter", __FUNCTION__);
        ALOGV("fd is: %x , imgPath: %s", fd, imgPath);

        
        data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
        data.writeFileDescriptor(fd);
        data.writeCString(imgPath);

        remote()->transact(LOAD_IMAGE_ASYNC, data, &reply);
        ALOGV("%s exit", __FUNCTION__);

}





