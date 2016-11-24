

#include <jni.h>
#include <utils/Log.h>

#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <INativeService.h>
#include <INativeCallback.h>
#include "native_client.h"


#define TAG JNI_WRAPPER
#define NATIVE_SERVICE_NAME "AshmemNativeService"

using namespace android;

JNIEXPORT int JNICALL Java_novak_sebastian_info_ashmem_jni_JNIWrapper_loadImageViaJNI__Landroid_os_MemoryFile_2Ljava_lang_String_2(JNIEnv* env, jobject ,  jobject jMemoryFile, jstring jImgPath) {
    ALOGV("%s enter:", __FUNCTION__);
    // Extract FileDescriptor to allocated region
    jclass clsMF = env->FindClass("android/os/MemoryFile");
    jfieldID fldFD = env->GetFieldID(clsMF, "mFD", "Ljava/io/FileDescriptor;");
    jobject objFD = env->GetObjectField(jMemoryFile, fldFD);

    jclass clsFD = env->FindClass("java/io/FileDescriptor");
    fldFD = env->GetFieldID(clsFD, "descriptor", "I");
    jint fd = env->GetIntField(objFD, fldFD);
    int32_t fdAllocatedRegion = (int32_t)fd;

    jboolean iscopy;
    const char* imgPathCString = (env)->GetStringUTFChars(jImgPath, &iscopy);

    static sp<INativeService> nativeService = 0;

    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder>	binder = sm->getService(String16(NATIVE_SERVICE_NAME));
    if(binder == NULL) {
        return -1;
    }

    nativeService = INativeService::asInterface(binder);
    ALOGV("Sending file descriptor %x", fdAllocatedRegion);
    nativeService->loadImageAsync(fdAllocatedRegion,  imgPathCString);

    // clean up
    env->DeleteLocalRef(clsFD);
    env->DeleteLocalRef(objFD);
    env->DeleteLocalRef(clsMF);

    if(iscopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(jImgPath, imgPathCString);
    }

    return 0;

}
