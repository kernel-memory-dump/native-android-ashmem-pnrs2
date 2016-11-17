
#include "BnExample.h"

namespace android {

    class Example: public BnExample {
    private:
        int32_t myField;
    public:
        Example();
        int32_t getExample ();
        int32_t setExample (int32_t t);
        void registerCallback(sp<INativeCallback> callback);
        
    };

}