/***************************************************************************
 *
 *
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                 Version 2, December 2004
 *
 *      Everyone is permitted to copy and distribute verbatim or modified
 *      copies of this license document, and changing it is allowed as long
 *      as the name is changed.
 *
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE, TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *         0. You just DO WHAT THE FUCK YOU WANT TO
 *
 *  -----------------------------------------------------
 *  Sebastian Novak @ GitHub https://github.com/kernel-memory-dump
 *  -----------------------------------------------------
 *
 *
 * @author  Sebastian Novak
 *
 *
 ****************************************************************************/
 
#include "BnNativeService.h"

namespace android {

    /**
     * Implementation of INativeService, invoked through Stub, BnNativeService
     */
class NativeService: public BnNativeService {
    private:
        int32_t myField;
        sp<INativeCallback> __callback;
    public:
        NativeService();
        void registerCallback(sp<INativeCallback>);
        void loadImageAsync(int32_t);
        void triggerCallback(int);
    };

}