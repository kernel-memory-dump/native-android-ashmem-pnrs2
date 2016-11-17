package com.rk.rt.bbt.android.ashmem.util;

import android.os.IBinder;
import android.support.annotation.NonNull;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * Created by rtrk on 17.11.16..
 */

/**
 *  In order to access ServiceManager, which is a hidden class, we use Reflection in order to load the Class object and invoke
 *  the getService method.
 */
public class ServiceManagerFetcher {

    /**
     * Acquires a reference to the hidden class android.os.ServiceManager and invokes its getService method in order to acquire
     * a {@link IBinder} reference to the specified service.
     * @param serviceName - name of the service to be fetched, as previously registered to the ServiceManager.
     * @return {@link IBinder} IBinder reference to the specified Service if getService method was invoked successfully. Null otherwise.
     */
    public static IBinder getIBinderViaServiceManager(@NonNull  String serviceName) {

        Class<?> serviceManager = null;
        try {
            serviceManager = Class.forName("android.os.ServiceManager");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return null;
        }
        Method getService = null;
        try {
            getService = serviceManager.getMethod("getService", String.class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
            return null;
        }

        IBinder binder = null;
        try {
            binder = (IBinder) getService.invoke(null, serviceName);
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } finally {
            return binder;
        }

    }


    /*


*/

}

