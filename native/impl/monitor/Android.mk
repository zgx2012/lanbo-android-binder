LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MonitorService.cpp \

LOCAL_SHARED_LIBRARIES := \
    libutils \
    liblog \
    libbinder \
    libmonitor

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../../include \

LOCAL_MODULE:= libmonitorservice

LOCAL_MODULE_TAGS := optional

#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_SHARED_LIBRARY)
