LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= ICommService.cpp

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \
	libbasecomm \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
	$(LOCAL_PATH)/../../include \
	$(LOCAL_PATH)/../comm-core \

LOCAL_MODULE:= libcommservice
LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := -Werror -Wall

include $(BUILD_SHARED_LIBRARY)
