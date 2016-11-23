
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


package novak.sebastian.info.ashmem.util;

import android.os.IBinder;


import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

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
    public static IBinder getIBinderViaServiceManager(String serviceName) {

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

