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
        REGISTER_CALLBACK = IBinder::FIRST_CALL_TRANSACTION, 
    };

    virtual void registerCallback(sp<INativeCallback> callback) = 0;

    DECLARE_META_INTERFACE(Example);
};

}

#endif
