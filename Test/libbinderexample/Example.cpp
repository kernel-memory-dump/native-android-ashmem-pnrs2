#include "Example.h"

using namespace android;
#include <cutils/log.h>
#include <binder/Parcel.h>

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

static void* triggerCallback(void *context)
{
    while(true)
     {
       sp<INativeCallback> callback  = static_cast< sp<INativeCallback>> (*context);
       callback.onImageLoadedAsync(true);
     }

       return NULL;
}

void Example::registerCallback(sp<INativeCallback> callback) 
{
    pthread_t pt;
    pthread_create( &pt, NULL, triggerCallback, (void*)&callback );
    pthread_detach(pt);
}