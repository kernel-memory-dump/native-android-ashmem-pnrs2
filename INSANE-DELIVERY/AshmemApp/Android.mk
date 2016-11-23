LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_PACKAGE_NAME := AshmemApp
LOCAL_MODULE_TAG := optional
LOCAL_DEX_PREOPT := false

LOCAL_SRC_FILES += $(call all-java-files-under, src)
LOCAL_SRC_FILES += $(call all-Iaidl-files-under, src)

include $(BUILD_PACKAGE)
