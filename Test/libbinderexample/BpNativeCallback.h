#include "INativeCallback"

namespace android 
{


class BpNativeCallback : public BpInterface<INativeCallback>
{

public:
    BpNativeCallback(const sp<IBinder>& impl);

    virtual onImageLoaded(bool success);

};

}