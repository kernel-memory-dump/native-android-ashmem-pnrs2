
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


package novak.sebastian.info.ashmem.jni;

import android.os.IBinder;
import android.os.MemoryFile;
import android.os.RemoteException;
import android.util.Log;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import novak.sebastian.info.ashmem.util.CommonUtils;
import novak.sebastian.info.ashmem.util.ServiceManagerFetcher;
import aidl.novak.sebastian.info.ashmem.jni.INativeCallback;
import aidl.novak.sebastian.info.ashmem.jni.INativeService;

/**
 *
 */
public class JNIWrapper {

    private static final String NATIVE_SERVICE_NAME = "AshmemNativeService";
    private static final String TAG = JNIWrapper.class.getName();

    /**
     * Client interface 
     */
    public interface JNIWrapperCallback {
        /**
         * Invoked if an Exception occured while using Binder IPC
         */
        void onError();
        void onImageLoaded(StatusCodes status);

    }

    //private MemoryFile mf;
    private JNIWrapperCallback callbackClient;

    public JNIWrapper(JNIWrapperCallback callbackClient) {
        this.callbackClient = callbackClient;
    }

    // Used to load the JNI Service client library on application startup.
    static {
        System.loadLibrary("native_client");
    }



    
    public void initiateImageLoadNative(MemoryFile mf, String path) {

        // obtain a reference to the NativeService via ServiceManager
        IBinder nativeServiceBinder = ServiceManagerFetcher.getIBinderViaServiceManager(NATIVE_SERVICE_NAME);
        if(nativeServiceBinder == null) {
            Log.e(TAG, "Failed to contact Native Service!");
            callbackClient.onError();
            return;
        }
        final INativeCallback nativeCallback = new INativeCallback.Stub() {

            //@Override
            public void imageLoadedAsync(int status) throws RemoteException {
                Log.d(TAG, "[callbackFunction][enter]");
                Log.d(TAG, "[callbackFunction][exit]");
                StatusCodes asEnum = CommonUtils.convertIntToStatusCodes(status);
                callbackClient.onImageLoaded(asEnum);
            }
        };

        
        INativeService serviceHandle = INativeService.Stub.asInterface(nativeServiceBinder);
        try {
            Log.d(TAG, "[SERVICE HANDLE?] is null?" + (serviceHandle == null));
            serviceHandle.registerCallback(nativeCallback);
            
            int errorCode = loadImageViaJNI(mf, path);
            

            if (errorCode != 0) {
                callbackClient.onError();
                return;
            } 

        } catch (RemoteException e) {

            Log.e(TAG, "[SERVICE HANDLE?] " + e.getMessage());
            e.printStackTrace();
            callbackClient.onError();
        }
    }
    
    /**
     *
     * @param mf
     * @param imagePath
     */
    public native int loadImageViaJNI(MemoryFile mf, String imagePath);

    



}
