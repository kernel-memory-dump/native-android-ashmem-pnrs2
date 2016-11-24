
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


package novak.sebastian.info.ashmem.presenter;

import android.content.Intent;
import android.net.Uri;
import android.os.MemoryFile;
import android.util.Log;

import novak.sebastian.info.ashmem.MainActivity;
import novak.sebastian.info.ashmem.jni.JNIWrapper;
import novak.sebastian.info.ashmem.jni.StatusCodes;
import novak.sebastian.info.ashmem.jni.JNIWrapper.JNIWrapperCallback;
import novak.sebastian.info.ashmem.util.AppState;

import novak.sebastian.info.ashmem.view.MainView;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

/**
 * Implements App Logic for MainView
 */
public class MainPresenterImpl implements MainPresenter, JNIWrapperCallback {

    private static final String TAG = MainPresenterImpl.class.getSimpleName();
    private static final int REQUEST_CODE = 1337;
    public static final int REGION_SIZE = 2*1024*1024; //

    private MainView view;
    private JNIWrapper jniWrapper;
    private MemoryFile memoryRegion;


    public MainPresenterImpl(MainView mainView) {
        this.view = mainView;
        // share app Context across app
        AppState.getInstance().setAppContext(this.view.asActivity().getApplicationContext());
    }

    @Override
    public void onUIReady() {
        Log.v(TAG, "UI ready! Locking down buttons!");
        // lock UI, user can't select an image before an memory region is allocated
        //view.setUIEnabled(false);

        // initialize JNIWrapper
        jniWrapper = new JNIWrapper(this);

        /**
         *  Create a new Thread to perform AshmemTask in order to acquire a new MemoryFile.
         *  Upon its completion it will trigger AshmemTaskCallback
         *  Callback runs on UI thread.
         */
         final AshmemTask task = new AshmemTask(new AshmemTask.AshmemTaskCallback() {
            @Override
            public void onAshmemRegionAllocated(MemoryFile mf) {
                Log.v(TAG, "AshmemRegion allocated! UI can be enabled!");
                memoryRegion = mf;
                // executing on UI thread, unlock UI
                // user can now select image, memory is ready
                //view.setUIEnabled(true);
            }
         }, REGION_SIZE);

         // allocate memory region in new thread
         Thread workerThread = new Thread(task);
         workerThread.start();
         // return to UI thread
    }

    @Override
    public void onSelectImage() {
        Log.v(TAG, "Attempting to contact Gallery for image selection!");
        Intent pickIntent = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        pickIntent.setType("image/*");
        view.asActivity().startActivityForResult(pickIntent, REQUEST_CODE);
    }

    @Override
    public void onImageSelected(int requestCode, int resultCode, Intent data) {
        // ignore other results
        if(requestCode != REQUEST_CODE) {
            return;
        }

        if(data == null || data.getData() == null) {
            // image loading failed
            Log.e(TAG, "OnActivityResult triggered, failed to acquire image URL");
            return;
        }

        Uri uri = data.getData();
        Log.v(TAG, "Acquired image path! URI is:" + uri.getPath());

        // update UI
        view.setImagePath(uri.getPath());
    }

    @Override
    public void onLoadImage() {
        //String imgPath = view.getPath();
        //int success = jniWrapper.loadImageViaJNI();
        jniWrapper.initiateImageLoadNative(memoryRegion, "/data/data/bbt2.jpg");

    }


    public void onError() {
        Log.e(TAG, "JNI wrapper encountered an error!");
    }

    public void onImageLoaded(StatusCodes status) {
        Log.v(TAG, "onImageLoaded -> JNI wrapper received callback from Native:" + status);

        Bitmap bitmap = jniWrapper.convertToBitmap(memoryRegion);
        mf.close(); 
        view.setImage(bmp);
        

    }





}
