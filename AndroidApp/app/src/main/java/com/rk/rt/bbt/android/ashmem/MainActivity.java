
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

package com.rk.rt.bbt.android.ashmem;

import android.content.Context;
import android.os.IBinder;
import android.os.MemoryFile;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.jar.JarFile;

/**
 * Application Entry point.
 *
 * Access to Application's Context is provided with {@link }
 */
public class MainActivity extends AppCompatActivity implements AshmemTask.AshmemTaskCallback{

    private static final String TAG = MainActivity.class.getSimpleName();
    public static final int REGION_SIZE = 1024;


    private static Context appContext;



    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        appContext = getApplicationContext();

        // register native callback
        registerNativeCallback();

        // utilize a Thread in order to asynchronously allocate an Ashmem region
        // after the region was allocated, perform JNI call in order to instruct the native service to load the image
        allocateAshmemRegion();
/*
        IBinder binder = (IBinder) ServiceManager.getService("Example");
        IExample example = IExample.Stub.asInterface(binder);
        try {
            int value = example.getExample();
            Log.d(TAG, "value = " + value);
        } catch
                (RemoteException e) {
            Log.d(TAG, "getExample FAILED");
        }
*/
    }

    /**
     *  Create a new Thread to perform AshmemTask in order to acquire a new MemoryFile.
     *  Upon its completion {@link AshmemTask} will trigger {@link #onAshmemRegionAllocated(MemoryFile)} callback
     */
    private void allocateAshmemRegion() {
        Thread workerThread = new Thread(new AshmemTask(MainActivity.this, REGION_SIZE));
        workerThread.start();
    }

    @Override
    public void onAshmemRegionAllocated(MemoryFile mf) {

    }

    /**
     * Image was successfully loaded into Ashmem region pointed by
     */
    private void renderImage() {
        Log.d(TAG, "[imageLoadedAsync][enter]");
    }

    /**
     * Sends a reference to MainActivity to the native service via Binder.
     * This callback will be invoked as a notification that the image was loaded into specified Ashmem region.
     */
    private void registerNativeCallback() {
        final INativeCallback callback = new INativeCallback.Stub() {
            @Override
            public void imageLoadedAsync(boolean success) throws RemoteException {
                Log.d(TAG, "[imageLoadedAsync][enter]");
                MainActivity.this.renderImage();
                Log.d(TAG, "[imageLoadedAsync][exit]");
            }
        };
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     *
     * @param mf
     * @param imagePath
     */
    public native void loadImageViaJNI(MemoryFile mf, String imagePath);


    public static Context getAppContext() {
        return appContext;
    }


}
