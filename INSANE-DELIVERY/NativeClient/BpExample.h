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

#ifndef BP_EXAMPLE_H
#define BP_EXAMPLE_H

#include "IExample.h"

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
