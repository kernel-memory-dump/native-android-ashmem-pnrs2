
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


import novak.sebastian.info.ashmem.jni.StatusCodes;

/**
 * Utility static functions used across the project
 */
public class CommonUtils {


    /**
     * Since EnumToValues Array is expensive, the result is stored and
     * re-used for consecutive calls.
     */
    private static StatusCodes[] cachedStatusCodesValues = null;

    /**
     * Converts given int into a {@link StatusCodes} instance.
     * @param value - used as an index for Enum->values array
     * @return {@link StatusCodes} instance representing specified value
     */
    public static StatusCodes convertIntToStatusCodes(int value) {
        if(cachedStatusCodesValues == null) {
            cachedStatusCodesValues = StatusCodes.values();
        }
        if(value < 0 || value > cachedStatusCodesValues.length) {
            return null;
        }

        return cachedStatusCodesValues[value];
    }
}
