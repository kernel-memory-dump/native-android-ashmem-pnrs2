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