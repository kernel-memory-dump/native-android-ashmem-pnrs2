##########################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libnativecommon
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder

LOCAL_SRC_FILES += IExample.cpp
LOCAL_SRC_FILES += INativeCallback.cpp

include $(BUILD_SHARED_LIBRARY)
##########################################

