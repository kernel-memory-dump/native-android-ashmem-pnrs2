#define LOG_TAG "NativeServiceServer_DAEMON"

#include <cutils/log.h>
#include <utils/CallStack.h>
#include <unistd.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>


#include "NativeService.h"

using namespace android;


int main() {

  ALOGV("NATIVE SERVICE - ASHMEM STARTED!");
  defaultServiceManager()-> addService(String16("AshmemNativeService"), new NativeService());

  android::ProcessState::self() -> startThreadPool();
  IPCThreadState::self()-> joinThreadPool();
  return 0;
}