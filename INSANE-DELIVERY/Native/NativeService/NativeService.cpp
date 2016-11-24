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
#include <cutils/log.h>
#include <binder/Parcel.h>
#include <pthread.h>
#include <binder/MemoryHeapBase.h>


using namespace android;

#define MEMORY_SIZE 2*1024*1024
#define LOG_TAG "NativeServiceAshmem"


typedef struct ThreadArgs_t {
	int32_t fd;
	const char* imgPath;
	NativeService* serviceHandle;
} ThreadArgs;

void* imageLoadingWorker(void *context);
int openAshmem(int* fd);
int getImgSize(FILE* imageFp);


NativeService::NativeService()
{

}

void NativeService::triggerCallback(int result)
{
    __callback->imageLoadedAsync(result);
}
/////////////////////////////////////////////////////////////////////////////////////
int getImgSize(FILE* imageFp) 
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
    // copy into local
    ThreadArgs* argsPtr = (ThreadArgs*) context;
    ThreadArgs args = *argsPtr;



    NativeService* serviceHandle = args.serviceHandle;
    int i = 0;
    uint8_t* fashm = (uint8_t*) mmap(NULL, MEMORY_SIZE, PROT_WRITE, MAP_SHARED, args.fd, 0);

    if (fashm == MAP_FAILED) 
	{
        ALOGE("mmap failed!");
        serviceHandle->triggerCallback(INativeService::OTHER_ERROR);
        return NULL;    
    }

    FILE *fpImg;
    fpImg = fopen(args.imgPath, "rb");
	// assert that we managed to open the image file
    if(fpImg == NULL) 
	{
		serviceHandle->triggerCallback(INativeService::IMAGE_NOT_FOUND);
		return NULL;
	}
	// get image size
	uint32_t imgSize = getImgSize(fpImg);
	if(imgSize == 0) {
		serviceHandle->triggerCallback(INativeService::IMAGE_NOT_FOUND);
		return NULL;
	}
	
	// assert that the image can be loaded into ashmem region
	if(MEMORY_SIZE < (imgSize)) 
	{
		serviceHandle->triggerCallback(INativeService::NOT_ENOUGH_MEMORY);
		return NULL;
	}
	
	uint32_t numBytes = 0;
	
	// write image size in first 4 bytes
	//memcpy(fashm, &imgSize, 4);
	fashm[3] = ((imgSize >> 24) & 0xFF);
    fashm[2] = ((imgSize >> 16) & 0xFF);
    fashm[1] = ((imgSize >>  8) & 0xFF);
    fashm[0] = ((imgSize      ) & 0xFF);
	
	// load image into ashmem region
	numBytes = fread(fashm + 4, 1, imgSize, fpImg);
	// asert that the image was successfully loaded into ashmem region
	if(numBytes != imgSize) {
		serviceHandle->triggerCallback(INativeService::OTHER_ERROR);
		return NULL;
	}
	
	fclose(fpImg);
	
	serviceHandle->triggerCallback(INativeService::IMAGE_LOADED_OK);

    return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////
void NativeService::registerCallback(sp<INativeCallback> callback) 
{
    ALOGV("%s enter", __FUNCTION__);
    __callback = callback;
    triggerCallback(INativeService::OTHER_ERROR);
}

void NativeService::loadImageAsync(int32_t fd, const char* imgPath)
{
	ALOGV("%s enter", __FUNCTION__);
	
	ThreadArgs* args = (ThreadArgs*) malloc(sizeof(ThreadArgs));
	if(args == NULL) 
	{
		ALOGE("loadImageAsync: FATAL ERROR, MALLOC FAILED");
		triggerCallback(INativeService::OTHER_ERROR);
		return;
	}
	triggerCallback(INativeService::OTHER_ERROR);
	args->fd = fd;
	args->imgPath = imgPath;
	args->serviceHandle = this;
	
	pthread_t pt;
    pthread_create( &pt, NULL, imageLoadingWorker, (void*)args);
    pthread_detach(pt); 
}

