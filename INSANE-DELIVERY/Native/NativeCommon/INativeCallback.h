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

#ifndef ANDROID_INATIVE_CALLBACK_H
#define ANDROID_INATIVE_CALLBACK_H

#include <binder/IInterface.h>

namespace android
{

/**
 * MetaInterface for sending a callback to Java Client
 *
 */
class INativeCallback : public IInterface {
public:
    
    enum
    {
        IMAGE_LOADED = IBinder::FIRST_CALL_TRANSACTION
    };

    /**
     * Callback for Java Client, where result specifies the outcome of an performed imageLoad.
     * Values are specified by StatusCodes enum.
     */
    virtual void imageLoadedAsync(int result) = 0;

    DECLARE_META_INTERFACE(NativeCallback);
};

}
#endif