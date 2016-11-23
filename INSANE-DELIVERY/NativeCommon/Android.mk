##########################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libnativecommon
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder

LOCAL_SRC_FILES += INativceService.cpp
LOCAL_SRC_FILES += INativeCallback.cpp

# LOCAL_C_INCLUDES += ../NativeCommon/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../NativeService
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../NativeClient

include $(BUILD_SHARED_LIBRARY)
##########################################

