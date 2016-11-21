#include "Example.h"
#define LOG NATIVE_SERVIS

using namespace android;
#include <cutils/log.h>
#include <binder/Parcel.h>
#include <pthread.h>

static sp<INativeCallback> _callback;

Example::Example()
{

}

int32_t Example::getExample() 
{

    return this->myField;
}

int32_t Example::setExample(int32_t t) 
{
    this->myField = t;
    return this->myField+1;
}



void* triggerCallback(void *context)
{
    ALOGV("%s enter  POSIX THREAD ", __FUNCTION__);
    while(true)
     {
      ALOGV("Triggering callback to Java!");
       _callback->imageLoadedAsync(true);
       sleep(5);
     }

       return NULL;
}

void Example::registerCallback(sp<INativeCallback> callback) 
{
    ALOGV("%s enter", __FUNCTION__);
    _callback = callback;
    pthread_t pt;
    pthread_create( &pt, NULL, triggerCallback, NULL);
    pthread_detach(pt);
}

