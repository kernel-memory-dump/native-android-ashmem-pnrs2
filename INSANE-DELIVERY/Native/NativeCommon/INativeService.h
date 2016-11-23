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

#ifndef ANDROID_INATIVE_SERVICE_H
#define ANDROID_INATIVE_SERVICE_H

#include <binder/IInterface.h>
#include "INativeCallback.h"

namespace android
{

/**
 * Meta interface for image loading NativeService
 */
class INativeService : public IInterface
{
public:

    enum 
    {
        REGISTER_CALLBACK = IBinder::FIRST_CALL_TRANSACTION, 
        LOAD_IMAGE_ASYNC
    };

    
    enum StatusCodesEnum
    { 
        IMAGE_LOADED_OK=0, 
        NOT_ENOUGH_MEMORY, 
        IMAGE_NOT_FOUND,
        OTHER_ERROR
    };

    /**
     *  Clients that use the loadImageAsync should previously register themselves
     */
    virtual void registerCallback(sp<INativeCallback>) = 0;

    /**
     *  Attempts to load specified image into specified ashmem region.
     *  This is performed in a separate thread, INativeCallback is triggered upon completion
     */
    virtual void loadImageAsync(int32_t, const char*) = 0;

    DECLARE_META_INTERFACE(NativeService);
};

}

#endif
