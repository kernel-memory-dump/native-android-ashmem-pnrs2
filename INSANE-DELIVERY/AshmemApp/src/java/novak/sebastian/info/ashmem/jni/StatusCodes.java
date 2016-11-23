
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


package novak.sebastian.info.ashmem.jni;

/**
 * Status codes defining the outcome of requested JNI operation.
 */
public enum StatusCodes {
    IMAGE_LOADED_OK(0), // image was loaded successfully
    NOT_ENOUGH_MEMORY(1), // ashmem region was not large enough to store the image in
    IMAGE_NOT_FOUND(2),  // if requested image could be accessed/found
    OTHER_ERROR(3)

    private final int value;

    StatusCodes(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }
}
