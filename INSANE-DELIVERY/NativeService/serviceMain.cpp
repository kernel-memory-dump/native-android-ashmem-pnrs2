#define LOG_TAG "NativeServiceServer"

#include <cutils/log.h>
#include <utils/CallStack.h>
#include <unistd.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>

#include "NativeService.h"

using namespace android;


int main() {
  defaultServiceManager()-> addService(String16("AshmemNativeService"), new NativeService());

  android::ProcessState::self() -> startThreadPool();
  IPCThreadState::self()-> joinThreadPool();
  return 0;
}