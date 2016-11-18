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
        GET_EXAMPLE = IBinder::FIRST_CALL_TRANSACTION,   // poziv prvog da bi se startovalo enumiranje
        SET_EXAMPLE,
        REGISTER_CALLBACK
    };

    virtual int32_t getExample() = 0;
    virtual int32_t setExample(int32_t t) = 0;
    virtual void registerCallback(sp<INativeCallback> callback) = 0;

    DECLARE_META_INTERFACE(Example);
};

}

#endif
