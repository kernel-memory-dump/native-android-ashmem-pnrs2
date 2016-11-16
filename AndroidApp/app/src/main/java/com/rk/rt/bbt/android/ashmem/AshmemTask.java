
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

import android.os.Handler;
import android.os.MemoryFile;
import android.support.annotation.NonNull;

import java.io.IOException;

/**
 *  Allocates Ashmem regions with given size as a {@link MemoryFile}. Should be executed within a separate Thread.
 *  Performs callback to UiThread, after allocation is complete.
 *  Each ashmem region shall be named as specified by {@link #ASHMEM_REGION_NAME_TEMPLATE} where timestamp is replaced by currentSystem time in
 *  milliseconds.
 *
 */
public class AshmemTask implements Runnable {

    /**
     * Template for ashmem region names, {TIMESTAMP} is replaced by {@link System#currentTimeMillis()}
     */
    private static final String ASHMEM_REGION_NAME_TEMPLATE = "com.rt.rk.bbt.android.ashmem-{TIMESTAMP}";

    /**
     * Callback specification for clients utilizing AshmemTask as a Thread
     */
    interface AshmemTaskCallback {

        /**
         * Callback to be invoked after region was allocated, targets the UiThread.
         * @param mf - reference to allocated Ashmem region, null if allocation failed
         */
        void onAshmemRegionAllocated(MemoryFile mf);
    }

    private AshmemTaskCallback callback;
    private int regionSize;

    /**
     *
     * @param callback - will be invoked after Ashmem region was allocated
     * @param regionSize - size of region in bytes
     */
    public AshmemTask(@NonNull AshmemTaskCallback callback, @NonNull int regionSize) {
        this.callback = callback;
        this.regionSize = regionSize;
    }

    @Override
    public void run() {
        final String ashmemName = ASHMEM_REGION_NAME_TEMPLATE.replace("{TIMESTAMP}", Long.toString(System.currentTimeMillis()));
        try {
            final MemoryFile mf = new MemoryFile(ashmemName, regionSize);

            // Acquire handler to MainLooper in order to send memoryFile to MainActivity
            // The callback should be executed on UIThread, inside MainActivity's Context
            Handler mainHandler = new Handler(MainActivity.getAppContext().getMainLooper());

            mainHandler.post(new Runnable() {

                @Override
                public void run() {
                    callback.onAshmemRegionAllocated(mf);
                }
            });

        } catch (IOException e) {
            e.printStackTrace();
        }


    }
}
