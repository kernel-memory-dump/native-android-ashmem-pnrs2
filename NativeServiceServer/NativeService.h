
#include "BnNativeServiceServer.h"
#define TAG "ALOGV("%s enter", __FUNCTION__);"

namespace android {

    class NativeService: public BnNativeServiceServer {
    private:
        int32_t myField;
        sp<INativeCallback> callback;
    public:
        NativeService();
        void registerCallback(sp<INativeCallback> callback);
        
    };

}