
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

// INativeCallback.aidl
//package com.rk.rt.bbt.android.ashmem;
package com.course.android.nativeservice;

/**
 * Callback from native service via Binder, targeting the MainActivity
 */
interface INativeCallback {

    /**
     * Notification from NativeService that the image was loaded into the specified Ashmem region
     */
    void imageLoadedAsync(int success);


}
