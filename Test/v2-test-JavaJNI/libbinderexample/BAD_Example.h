#ifndef BP_EXAMPLE_H
#define BP_EXAMPLE_H

#include "BnExample.h"
#define TAG "ALOGV("%s enter", __FUNCTION__);"

namespace android {

    class Example: public BnExample {
    private:
        int32_t myField;
        sp<INativeCallback> callback;
    public:
        Example();
        int32_t getExample ();
        int32_t setExample (int32_t t);
        void registerCallback(sp<INativeCallback> callback);
        
    };

}

#endif