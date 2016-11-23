#include "Example.h"
#define LOG NATIVE_SERVIS

using namespace android;
#include <cutils/log.h>
#include <binder/Parcel.h>
#include <pthread.h>

void* imageLoadingWorker(void *context);
int openAshmem(int* fd);
int inline getImgSize(FILE* imageFp);


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
/////////////////////////////////////////////////////////////////////////////////////
int inline getImgSize(FILE* imageFp) 
{
	if(imageFp == NULL) {
		return -1;
	}
	fseek(imageFp, 0L, SEEK_END);
    uint32_t imgSize = (uint32_t)ftell(imageFp);
    // restore file pointer to begining of file
	fseek(imageFp, 0L, SEEK_SET);
    return imgSize;
}

void* imageLoadingWorker(void* context)
{
    ALOGV("%s enter  POSIX THREAD ", __FUNCTION__);
    Example* example = (Example*) context;
    int i = 0;
	int32_t* fd = (int32_t*)arg;
    uint8_t* fashm = create_ashmem(fd);

    if (fashm == MAP_FAILED) 
	{
        ALOGE("mmap failed! %d, %s", errno, strerror(errno));
        example->triggerCallback(result);
        return NULL;    
    }

    FILE *fpImg;
    fpImg = fopen(file_name, "rb");
	// assert that we managed to open the image file
    if(fpImg == NULL) 
	{
		example->triggerCallback(result);
		return NULL;
	}
	// get image size
	uint32_t imgSize = getFileSize(fpImg);
	if(imgSize == -1) {
		example->triggerCallback(result);
		return NULL;
	}
	
	// assert that the image can be loaded into ashmem region
	if(ashmemSize < (imgSize)) 
	{
		example->triggerCallback(result);
		return NULL;
	}
	
	int numBytes = -1;
	
	// write image size in first 4 bytes
	memcpy(fashm, &imgSize, 4);
	
	// load image into ashmem region
	numBytes = fread(fashm + 4, 1, imgSize, fpImg);
	// asert that the image was successfully loaded into ashmem region
	if(numBytes != imgSize) {
		example->triggerCallback(result);
		return NULL;
	}
	
	fclose(fp);
	
	example->triggerCallback(result);

    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////
void Example::registerCallback(sp<INativeCallback> callback) 
{
    ALOGV("%s enter", __FUNCTION__);
    __callback = callback;
    pthread_t pt;
    pthread_create( &pt, NULL, imageLoadingWorker, (void*)this);
    pthread_detach(pt);
}

