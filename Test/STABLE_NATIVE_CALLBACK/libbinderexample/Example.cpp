#include "Example.h"
#define LOG NATIVE_SERVIS

using namespace android;
#include <cutils/log.h>
#include <binder/Parcel.h>
#include <pthread.h>



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

void Example::triggerCallback(int result)
{
    __callback->imageLoadedAsync(result);
}



void* imageLoadingWorker(void *context)
{
    ALOGV("%s enter  POSIX THREAD ", __FUNCTION__);
    Example* example = (Example*) context;
    int i = 0;
    while(true)
     {
        ALOGV("Triggering callback to Java!");
        example->triggerCallback((++i) % 10);
        sleep(5);
     }

       return NULL;
}

void Example::registerCallback(sp<INativeCallback> callback) 
{
    ALOGV("%s enter", __FUNCTION__);
    __callback = callback;
    pthread_t pt;
    pthread_create( &pt, NULL, imageLoadingWorker, (void*)this);
    pthread_detach(pt);
}

