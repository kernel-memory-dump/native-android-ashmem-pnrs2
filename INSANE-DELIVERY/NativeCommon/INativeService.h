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

#ifndef ANDROID_IEXAMPLE_H
#define ANDROID_IEXAMPLE_H

#include <binder/IInterface.h>
#include "INativeCallback.h"

namespace android
{

class IExample : public IInterface
{
public:

    enum 
    {
        REGISTER_CALLBACK = IBinder::FIRST_CALL_TRANSACTION,   // poziv prvog da bi se startovalo enumiranje
        LOAD_IMAGE_ASYNC
        
    };

    virtual int32_t getExample() = 0;
    virtual int32_t setExample(int32_t t) = 0;
    virtual void registerCallback(sp<INativeCallback> callback) = 0;

    DECLARE_META_INTERFACE(Example);
};

}

#endif
