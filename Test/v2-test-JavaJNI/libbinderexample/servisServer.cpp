#define LOG_TAG "servisServer"

#include <cutils/log.h>
#include <utils/CallStack.h>
#include <unistd.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>

//#include "IExample.h"
#include "Example.h"

using namespace android;


int main() {
  defaultServiceManager()-> addService(String16("Example"), new Example());

  android::ProcessState::self() -> startThreadPool();
  IPCThreadState::self()-> joinThreadPool();
  return 0;
}