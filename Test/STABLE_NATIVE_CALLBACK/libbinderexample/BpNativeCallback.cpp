#define LOG_NDEBUG 0
#define LOG_TAG "BpNativeCallback"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BpNativeCallback.h"

using namespace android;


BpNativeCallback::BpNativeCallback(const sp<IBinder>& impl) :
	BpInterface<INativeCallback>(impl)
{

}

void BpNativeCallback::imageLoadedAsync(int result)
{
        Parcel data, reply;
        ALOGV("%s enter", __FUNCTION__);

        data.writeInterfaceToken(INativeCallback::getInterfaceDescriptor());
        data.writeInt32(result);

        remote()->transact(IMAGE_LOADED, data, &reply);
        reply.readInt32();

        ALOGV("%s exit", __FUNCTION__);

}
