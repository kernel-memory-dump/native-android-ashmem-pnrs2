
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


package novak.sebastian.info.ashmem;


import java.io.IOException;

import android.os.MemoryFile;
import android.test.ActivityInstrumentationTestCase2;
import android.test.UiThreadTest;
import android.widget.ImageView;
import android.widget.TextView;

/**
 * Instruments MainActivity and Unit-tests module 
 * 
 */
public class MainActivityTest extends extends ActivityInstrumentationTestCase2<MainActivity> {

    // test convert 
    JNIWrapper wrapper;
    MainActivity activity;
    
    MainPresenterImpl presenter;

    // set custom txtImagePath
	EditText txtImagePath;
	ImageView imageView2;

	MemoryFile presentersMemoryRegion;
    MemoryFile smallMemoryRegion;
    JNIWrapper jniWrapper;
    JNIWrapperCallback jniWrapperCallback;
    
    // Invalid IMAGE PATH, should result in StatusCodes::NOT_FOUND
    private final static String INVALID_PATH = "/data/data/invalid.jpg";
    // OK PATH, should be loaded and result in imageLoaded callback with statusCodes::IMAGE_LOADED_OK
    private final static String IMAGE_OK_PATH = "/data/data/bbt2.jpg";
    private static final int WAIT_FOR_ASYNC_IMAGE_LOAD = 6000;
    private static int SMALL_REGION_SIZE = 1024;

    StatusCodes lastReceivedStatusCode;
    boolean jniOnErrorInvoked;

    public MainActivityTest() {
		super(MainActivity.class);
	}
    

	@Override
	protected void setUp() throws Exception {
		super.setUp();
		
		activity = this.getActivity();
		txtImagePath = (EditText) activity.findViewById(R.id.txtImagePath);
		image = (ImageView) activity.findViewById(R.id.imageView1);

        Field presenterField = activity.getClass().getDeclaredField("presenter");
        presenterField.setAccessible(true);
        presenter = (MainPresenterImpl)activity.presenter;

        Field memoryRegionField = presenter.getClass().getDeclaredField("memoryRegion");
        presenterField.setAccessible(true);
        presentersMemoryRegion = presenter.memoryRegion;

        smallMemoryRegion = new MemoryFile("TEST-SMALL-REGION", SMALL_REGION_SIZE);
        Field f = mf.getClass().getDeclaredField("mFD");
        f.setAccessible(true);

        jniOnErrorInvoked = false;
        lastReceivedStatusCode = null;

        jniWrapperCallback = new JNIWrapperCallback() {
                @Override
                public void onError() {
                    jniOnErrorInvoked = true;
                }
                
                @Override
                public void onImageLoaded(StatusCodes status) {
                        lastReceivedStatusCode = status;
                 }
        };

        jniWrapper = new JNIWrapper(jniWrapperCallback);

	}

    /**
     *  Test that service can load an OK image and respond with IMAGE_LOADED_OK
     */ 
    @UiThreadTest
	public void testImageLoadedOk() throws IOException {
		try {
			txtImagePath.setText(IMAGE_OK_PATH);
            jniWrapper.initiateImageLoadNative(presentersMemoryRegion, IMAGE_OK_PATH);
            
			Thread.sleep(WAIT_FOR_ASYNC_IMAGE_LOAD);
			assertEquals(StatusCodes.NOT_FOUND, IMAGE_LOADED_OK);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

    /**
     *  ASsert that service  can handle a bad image path
     */ 
    @UiThreadTest
	public void testImageNotFound() throws IOException {
		try {
			txtImagePath.setText(INVALID_PATH);
            jniWrapper.initiateImageLoadNative(presentersMemoryRegion, INVALID_PATH);
            
			Thread.sleep(WAIT_FOR_ASYNC_IMAGE_LOAD);
			assertEquals(StatusCodes.NOT_FOUND, lastReceivedStatusCode);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

    /**
     *  ASsert that service it can detect if an image is too large
     */ 
    @UiThreadTest
	public void testImageTooLarge() throws IOException {
		try {
			txtImagePath.setText(INVALID_PATH);
            jniWrapper.initiateImageLoadNative(presentersMemoryRegion, imgPath);
            
			Thread.sleep(WAIT_FOR_ASYNC_IMAGE_LOAD);
			assertEquals(StatusCodes.NOT_ENOUGH_MEMORY, lastReceivedStatusCode);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

     /**
     *  ASsert that JNI can properly handle invalid arguments
     */ 
    @UiThreadTest
	public void testJNIError() throws IOException {
		try {
			txtImagePath.setText(INVALID_PATH);
            jniWrapper.initiateImageLoadNative(presentersMemoryRegion, imgPath);
            
			Thread.sleep(WAIT_FOR_ASYNC_IMAGE_LOAD);
			assertEquals(StatusCodes.NOT_ENOUGH_MEMORY, lastReceivedStatusCode);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}


}

