package com.course.android.nativeservice;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.*;
import java.*;
import com.*;
import android.util.Log;

public class MainActivity extends Activity {

    public static final String TAG = "MainActivity";
    public INativeCallback callback;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        testNativeService();
    }

    private void testNativeService() {
	   IBinder binder = (IBinder) ServiceManager.getService("Example");
       IExample example = IExample.Stub.asInterface(binder);

       callback = new INativeCallback.Stub() {
            @Override
            public void imageLoadedAsync(boolean success) throws RemoteException {
                Log.d(TAG, "[callbackFunction][enter]");
                Log.d(TAG, "[callbackFunction][exit]");
            }
        };

        try {
            int value = example.getExample();
            example.registerCallback(callback);
            Log.d(TAG, "value = " + value);
        } catch (RemoteException e) {
        Log.d(TAG, "getExample FAILED");
        }

    }
}
