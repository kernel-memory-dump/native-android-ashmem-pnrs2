
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
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.IBinder;
import android.os.MemoryFile;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.rk.rt.bbt.android.ashmem.util.ServiceManagerFetcher;

import org.androidannotations.annotations.Click;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.OnActivityResult;
import org.androidannotations.annotations.ViewById;

import java.io.FileDescriptor;
import java.util.jar.JarFile;

/**
 * Application Entry point.
 *
 * Access to Application's Context is provided with {@link }
 */
@EActivity(R.layout.activity_main)
public class MainActivity extends AppCompatActivity implements AshmemTask.AshmemTaskCallback {

    private static final String TAG = MainActivity.class.getSimpleName();
    public static final int REGION_SIZE = 1024;
    // Native service will register itself to the ServiceManager under this name
    private static final String NATIVE_SERVICE_NAME = "com.rt.rk.bbt.android.ashmem.NativeService";
    public static final int REQUEST_CODE = 1337;


    private static Context appContext;

    @ViewById
    EditText txtImagePath;



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

        //FileDescriptor fd = extractFDFromMemoryFile();
      //  Bitmap image = BitmapFactory.decodeFileDescriptor(fileDescriptor);

    }


    final static INativeCallback nativeCallback = new INativeCallback.Stub() {
        @Override
        public void imageLoadedAsync(boolean success) throws RemoteException {
            Log.d(TAG, "[callbackFunction][enter]");
            Log.d(TAG, "[callbackFunction][exit]");
        }
    };

    /**
     * Sends a reference to MainActivity to the native service via Binder.
     * This callback will be invoked as a notification that the image was loaded into specified Ashmem region.
     */
    private void registerNativeCallback() {
       /*
        final INativeCallback nativeCallback = new INativeCallback.Stub() {
            @Override
            public void imageLoadedAsync(boolean success) throws RemoteException {
                Log.d(TAG, "[imageLoadedAsync][enter]");
                MainActivity.this.renderImage();
                Log.d(TAG, "[imageLoadedAsync][exit]");
            }
        };*/

        // obtain a reference to the NativeService via ServiceManager
        IBinder nativeServiceBinder = ServiceManagerFetcher.getIBinderViaServiceManager(NATIVE_SERVICE_NAME);
        if(nativeServiceBinder == null) {
            Log.e(TAG, "Failed to contact Native Service!");
            Toast.makeText(getAppContext(), "Failed to acquire bind native service", Toast.LENGTH_LONG).show();
            return;
        }
        //INativeService example = INativeService.Stub.asInterface(nativeServiceBinder);
        IExample example = IExample.Stub.asInterface(nativeServiceBinder);
        try {
            example.registerCallback(nativeCallback);
        } catch (RemoteException e) {
            e.printStackTrace();
        }


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

    @Click({R.id.btnSelectImage})
    void onImageSelectClicked() {
        //Intent intent = new Intent();
        //intent.setType("image/*");
        //intent.setAction(Intent.ACTION_GET_CONTENT);
        Intent pickIntent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        pickIntent.setType("image/* video/*");
        startActivityForResult(pickIntent, REQUEST_CODE);
    }

    @Click({R.id.btnLoadImage})
    void onLoadImageClicked() {

    }


    @OnActivityResult(REQUEST_CODE)
    void onResult(Intent data) {
        if(data == null || data.getData() == null) {
            // image loading failed
            Log.e(TAG, "OnActivityResult triggered, failed to acquire image URL");
            return;
        }

        Uri uri = data.getData();
        Log.v(TAG, "Acquired image path! URI is:" + uri.getPath());
        txtImagePath.setText(uri.getPath());
    }



/*
    @Override
    public void onClick(View view) {
        switch(view.getId()) {
            case R.id.btnSelectImage:
                onImageSelectClicked();
                break;
            case R.id.btnLoadImage:
                onLoadImageClicked();
                break;
            default:
                break;
        }
    }*/
}
