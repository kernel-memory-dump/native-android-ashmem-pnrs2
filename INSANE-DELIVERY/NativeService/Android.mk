include $(CLEAR_VARS)

LOCAL_MODULE := nativeServiceImgLoad


LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES +=  liblog
LOCAL_SHARED_LIBRARIES += libnativecommon

LOCAL_C_INCLUDES += ../NativeCommon/

LOCAL_SRC_FILES += Example.cpp
LOCAL_SRC_FILES += BnExample.cpp
LOCAL_SRC_FILES += servisServer.cpp

include $(BUILD_EXECUTABLE)

