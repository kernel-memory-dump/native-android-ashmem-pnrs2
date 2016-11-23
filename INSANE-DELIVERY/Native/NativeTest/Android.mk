LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := testServiceClient


LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES +=  liblog
LOCAL_SHARED_LIBRARIES += libashmem_pnrs2

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../NativeCommon/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../NativeClient/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../NativeService/

LOCAL_SRC_FILES += servisKlijent.cpp


include $(BUILD_EXECUTABLE)