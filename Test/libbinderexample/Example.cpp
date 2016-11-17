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

void Example::registerCallback() 
{
    

}