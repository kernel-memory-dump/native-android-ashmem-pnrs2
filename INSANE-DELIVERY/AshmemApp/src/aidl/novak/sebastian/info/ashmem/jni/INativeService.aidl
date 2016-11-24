
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


// INativeService.aidl
package aidl.novak.sebastian.info.ashmem.jni;

import android.os.ParcelFileDescriptor;
import aidl.novak.sebastian.info.ashmem.jni.INativeCallback;

/**
 * Native image loading service
 */
interface INativeService {
	
	/**
	 * @param callback - in order to get notified when image loading is complete
	 * clients should previously use this method to register a callback.
	 */
    void registerCallback(INativeCallback callback);

    
}
