LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    CommService.cpp \
    CommServiceMain.cpp \
    ListenerManager.cpp \
    EventManager.cpp \

LOCAL_SHARED_LIBRARIES := \
	libbinder \
    libutils \
    libcutils \
    liblog \
    libbasecomm \
    libcommunication \
    libcommservice \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../libs/comm-core \

LOCAL_MODULE:= comm_server

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)