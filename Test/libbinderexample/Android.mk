LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libbinderexample
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder

LOCAL_SRC_FILES += IExample.cpp
LOCAL_SRC_FILES += INativeCallback.cpp
LOCAL_SRC_FILES += BnExample.cpp
LOCAL_SRC_FILES += BpExample.cpp


include $(BUILD_SHARED_LIBRARY)

#######################################
include $(CLEAR_VARS)

LOCAL_MODULE := servisServer


LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES +=  liblog
LOCAL_SHARED_LIBRARIES += libbinderexample

LOCAL_SRC_FILES += Example.cpp
LOCAL_SRC_FILES += servisServer.cpp

include $(BUILD_EXECUTABLE)

#########################################
include $(CLEAR_VARS)
LOCAL_MODULE := servisKlijent


LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES +=  liblog
LOCAL_SHARED_LIBRARIES += libbinderexample


LOCAL_SRC_FILES += servisKlijent.cpp


include $(BUILD_EXECUTABLE)