LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MonitorClientMain.cpp \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils \
    liblog \
    libmonitor

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../impl/monitor \

LOCAL_MODULE:= monitor_client

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)

#==============================================

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    MonitorCallbackMain.cpp \
    MonitorCallback.cpp \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils \
    liblog \
    libmonitor

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/../../impl/monitor \

LOCAL_MODULE:= monitor_callback

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)