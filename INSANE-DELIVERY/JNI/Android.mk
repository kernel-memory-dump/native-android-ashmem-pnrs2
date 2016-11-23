LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES :=	\
	native_client.cpp

LOCAL_MODULE:= libnative_client

LOCAL_SHARED_LIBRARIES += libcutils libutils libbinder libashmem_pnrs2

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../Native/NativeCommon/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../Native/NativeClient/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../Native/NativeService/

include $(BUILD_SHARED_LIBRARY)