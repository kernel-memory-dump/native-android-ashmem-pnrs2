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

#include "NativeService.h"
#define LOG NATIVE_SERVIS

using namespace android;
#include <cutils/log.h>
#include <binder/Parcel.h>
#include <pthread.h>

typedef struct ThreadArgs_t {
	int32_t fd;
	const char* imgPath;
	NativeService* serviceHandle;
} ThreadArgs;

void* imageLoadingWorker(void *context);
int openAshmem(int* fd);
int inline getImgSize(FILE* imageFp);


NativeService::NativeService()
{

}

int32_t NativeService::getNativeService() 
{

    return this->myField;
}

int32_t NativeService::setNativeService(int32_t t) 
{
    this->myField = t;
    return this->myField+1;
}

void NativeService::triggerCallback(int result)
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
    ThreadArgs* args = (ThreadArgs*) context;
    NativeService* serviceHandle = args->serviceHandle;
    int i = 0;
	int32_t* fd = (int32_t*)args->fd;
    uint8_t* fashm = create_ashmem(fd);

    if (fashm == MAP_FAILED) 
	{
        ALOGE("mmap failed! %d, %s", errno, strerror(errno));
        serviceHandle->triggerCallback(INativeService::IMAGE_LOADED_OK);
        return NULL;    
    }

    FILE *fpImg;
    fpImg = fopen(args->imgPath, "rb");
	// assert that we managed to open the image file
    if(fpImg == NULL) 
	{
		serviceHandle->triggerCallback(INativeService::IMAGE_NOT_FOUND);
		return NULL;
	}
	// get image size
	uint32_t imgSize = getFileSize(fpImg);
	if(imgSize == -1) {
		serviceHandle->triggerCallback(INativeService::IMAGE_NOT_FOUND);
		return NULL;
	}
	
	// assert that the image can be loaded into ashmem region
	if(ashmemSize < (imgSize)) 
	{
		serviceHandle->triggerCallback(INativeService::NOT_ENOUGH_MEMORY);
		return NULL;
	}
	
	int numBytes = -1;
	
	// write image size in first 4 bytes
	memcpy(fashm, &imgSize, 4);
	
	// load image into ashmem region
	numBytes = fread(fashm + 4, 1, imgSize, fpImg);
	// asert that the image was successfully loaded into ashmem region
	if(numBytes != imgSize) {
		serviceHandle->triggerCallback(OTHER_ERROR);
		return NULL;
	}
	
	fclose(fp);
	
	serviceHandle->triggerCallback(INativeService::IMAGE_LOADED_OK);

    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////
void NativeService::registerCallback(sp<INativeCallback> callback) 
{
    ALOGV("%s enter", __FUNCTION__);
    __callback = callback;
}

void NativeService::loadImageAsync(int32_t, const char*)
{

	ThreadArgs args;
	args.fd = fd;
	args.imgPath = imgPath;
	args.serviceHandle = this;
	pthread_t pt;
    pthread_create( &pt, NULL, imageLoadingWorker, (void*)&args);
    pthread_detach(pt);
}
