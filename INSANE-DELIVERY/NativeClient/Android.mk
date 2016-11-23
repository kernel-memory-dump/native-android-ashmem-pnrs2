LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libnativeclient
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
#LOCAL_SHARED_LIBRARIES += libnativecommon

LOCAL_C_INCLUDES += ../NativeCommon/
LOCAL_SRC_FILES += BpNativeCallback.cpp
LOCAL_SRC_FILES += BpNativeService.cpp

include $(BUILD_SHARED_LIBRARY)

#######################################
