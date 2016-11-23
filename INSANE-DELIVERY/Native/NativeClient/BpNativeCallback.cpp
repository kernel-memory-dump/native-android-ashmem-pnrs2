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
