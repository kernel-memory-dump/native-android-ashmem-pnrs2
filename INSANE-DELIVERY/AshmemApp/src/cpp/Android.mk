LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES :=	\
	native_client.cpp

LOCAL_MODULE:= native_client_lib

LOCAL_SHARED_LIBRARIES += libcutils libutils libbinder libnativecommon

LOCAL_C_INCLUDES += vendor/rtrk/example_product/libbinderexample/

include $(BUILD_SHARED_LIBRARY)