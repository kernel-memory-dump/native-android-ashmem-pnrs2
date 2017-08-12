# native-android-ashmem-pnrs2

Android Open Source Project - IPC - native system service

Communication flow:

App creates and ASHMEM region, passes it -> 
        JNI passes it via client proxy to the native service stub 
               -> Native Service loads the image into the shared memory region
                      -> Android app is notified via AIDL specified Callback
