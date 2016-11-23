LOCAL_PATH := $(call my-dir)

########################################
include $(CLEAR_VARS)

LOCAL_MODULE := libashmem_pnrs2
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder

LOCAL_C_INCLUDES += $(LOCAL_PATH)/NativeCommon/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/NativeClient/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/NativeService/

LOCAL_SRC_FILES += NativeCommon/INativeCallback.cpp
LOCAL_SRC_FILES += NativeCommon/INativeService.cpp
LOCAL_SRC_FILES += NativeClient/BpNativeCallback.cpp
LOCAL_SRC_FILES += NativeClient/BpNativeService.cpp
LOCAL_SRC_FILES += NativeService/BnNativeService.cpp

include $(BUILD_SHARED_LIBRARY)

##############################


