#ifndef ANDROID_INATIVE_CALLBACK_H
#define ANDROID_INATIVE_CALLBACK_H

#include <binder/IInterface.h>

namespace android
{


class INativeCallback : public IInterface {
public:
    
    enum
    {
        IMAGE_LOADED = IBinder::FIRST_CALL_TRANSACTION
    };

    virtual void imageLoadedAsync(bool success) = 0;

    // name of interface -> poziv BP
    DECLARE_META_INTERFACE(NativeCallback);
};

}
#endif