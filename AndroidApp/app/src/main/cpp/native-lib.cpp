
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
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE,
 *         TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
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


#include <jni.h>
#include <string>

extern "C" {

static JNIEnv* mainActivityEnv;
static jobject mainActivityObj;

// status codes that match StatusCodeEnum
#define IMAGE_LOADED_OK 0
#define NOT_ENOUGH_MEMORY 1
#define IMAGE_NOT_FOUND 2


/**
 * Constructs jobject representing an appropriate com.rt.rk.bbt.android.ashmem.StatusCode enum.
 */
jobject convertIntToEnum() {

}

void notifyMainActivity(int outcome) {

    // Construct an Enum
    jstring jstr = mainActivityEnv->NewStringUTF("This string comes from JNI");
    // First get the class that contains the method you need to call
    jclass clazz = mainActivityEnv->FindClass("the/package/MainActivity");
    // Get the method that you want to call
    jmethodID messageMe = mainActivityEnv->GetMethodID(clazz, "messageMe", "(Ljava/lang/String;)V");
    // Call the method on the object
    mainActivityEnv->CallVoidMethod(mainActivityObj, messageMe, jstr);
    // Get a C-style string
    jobject result;
    const char* str = mainActivityEnv->GetStringUTFChars((jstring) result, NULL);
    printf("%s\n", str);
    // Clean up
    mainActivityEnv->ReleaseStringUTFChars(jstr, str);

//    // Shutdown the VM.
//    vm->DestroyJavaVM();

    //return mainActivityEnv->NewStringUTF("Hello from JNI!");
}

JNIEXPORT jstring JNICALL Java_com_rk_rt_bbt_android_ashmem_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */ instance) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


JNIEXPORT void JNICALL Java_com_rk_rt_bbt_android_ashmem_MainActivity_loadImageViaJNI(JNIEnv *env, jobject instance, jobject mf, jstring imagePath_) {
    const char *imagePath = env->GetStringUTFChars(imagePath_, 0);


    env->ReleaseStringUTFChars(imagePath_, imagePath);
}

}


