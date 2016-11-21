
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

package com.course.android.nativeservice;

import android.app.Activity;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.*;
import java.*;
import com.*;
import android.widget.*;
import android.util.Log;
import android.view.View;


public class MainActivity extends Activity {

    public static final String TAG = "MainActivity";
    public INativeCallback callback;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //testNativeService();
    }

    public void registerNativeService(View v) {
        Toast.makeText(getApplicationContext(), "Attempting to register callback--->", Toast.LENGTH_LONG).show();
        testNativeService();

    }

    private void testNativeService() {
	   IBinder binder = (IBinder) ServiceManager.getService("Example");
       if(binder == null) {
        Toast.makeText(getApplicationContext(), "Failed to acquire bind native service", Toast.LENGTH_LONG).show();
        return;
       }
       IExample example = IExample.Stub.asInterface(binder);

       callback = new INativeCallback.Stub() {
            @Override
            public void imageLoadedAsync(boolean success) throws RemoteException {
                MainActivity.this.runOnUiThread(new Runnable() {
                        public void run() {
                        Toast.makeText(MainActivity.this, "Callback from native service!", Toast.LENGTH_LONG).show();
                        Log.d(TAG, "[callbackFunction][enter]");
                        Log.d(TAG, "[callbackFunction][exit]");    
                        
                        }
                });

            }
        };

        try {

            int value = example.getExample();
            example.registerCallback(callback);
            Log.d(TAG, "value = " + value);
        } catch (RemoteException e) {
        Log.d(TAG, "getExample FAILED");
        Toast.makeText(getApplicationContext(), "HERP DERP binder failture abortttmissionnn", Toast.LENGTH_LONG).show();
        }

    }
}
