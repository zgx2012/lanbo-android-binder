LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ArithmeticClientMain.cpp \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils \
    liblog \
    libarithmetic

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../impl/arithmetic \

LOCAL_MODULE:= arithmetic_client

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)
