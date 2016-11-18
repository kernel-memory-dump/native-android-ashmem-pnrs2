#include "INativeCallback"

namespace android 
{


class BpNativeCallback : public BpInterface<INativeCallback>
{

public:
    BpNativeCallback(const sp<IBinder>& impl);

    virtual void onImageLoaded(bool success);

};

}