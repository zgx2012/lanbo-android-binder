LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MatrixService.cpp \

LOCAL_SHARED_LIBRARIES := \
    libutils \
    liblog \
    libbinder \
    libmatrix

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../../include \

LOCAL_MODULE:= libmatrixservice

LOCAL_MODULE_TAGS := optional

#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_SHARED_LIBRARY)
