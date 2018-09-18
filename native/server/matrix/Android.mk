LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MatrixServerMain.cpp \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils \
    liblog \
    libmatrixservice

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../impl/matrix \

LOCAL_MODULE:= matrix_server

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)
