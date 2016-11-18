#ifndef BP_EXAMPLE_H
#define BP_EXAMPLE_H

#include "IExample.h"
#include "INativeCallback.h"

namespace android
{

class BpExample : public BpInterface<IExample>
{

public:

    BpExample(const sp<IBinder>& impl);

    virtual int32_t getExample();
    virtual int32_t setExample(int32_t t);
    virtual void registerCallback(sp<INativeCallback> callback);

};

}

#endif
