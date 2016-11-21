
#include "INativeCallback.h"

namespace android 
{


class BpNativeCallback : public BpInterface<INativeCallback>
{

public:
    BpNativeCallback(const sp<IBinder>& impl);

    virtual void imageLoadedAsync(bool success);

};

}