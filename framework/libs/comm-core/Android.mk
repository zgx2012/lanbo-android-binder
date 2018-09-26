LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-cpp-files-under, .)

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/..

LOCAL_MODULE:= libbasecomm
LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := -Werror -Wall

include $(BUILD_SHARED_LIBRARY)
