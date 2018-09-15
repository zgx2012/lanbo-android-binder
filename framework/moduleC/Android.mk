LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ModuleCService.cpp \
    ModuleCMain.cpp \

LOCAL_SHARED_LIBRARIES := \
    libutils \
    liblog \
    libbinder \
    libbasecomm \
    libcommunication \
    libmoduleA \
    libmoduleB \
    libmoduleC \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
    $(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../libs/comm-core \

LOCAL_MODULE:= moduleC_server

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS += -Wall -Wextra -Werror

include $(BUILD_EXECUTABLE)