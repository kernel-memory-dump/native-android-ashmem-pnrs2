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


#define LOG_TAG "servisKlijent"

#include <cutils/log.h>
#include <utils/CallStack.h>
#include <unistd.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>

#include "IExample.h"

using namespace android;

int main() {
    sp <IServiceManager> smanager =defaultServiceManager();
    sp<IBinder> binder = smanager -> getService(String16("Example")); 
   sp <IExample> example = interface_cast <IExample> (binder);
    int testValue =example ->getExample(); 
  ALOGI("Test value: %d", testValue);

 }