LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	ModuleA.cpp \
	ModuleB.cpp \
	ModuleC.cpp \
	ModuleFactory.cpp \
	Communication.cpp \

LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \
	libbasecomm \
	libmoduleA \
	libmoduleB \
	libmoduleC \
	#liblog \

LOCAL_C_INCLUDES += \
    $(JNI_H_INCLUDE) \
	$(LOCAL_PATH)/../../include \
	$(LOCAL_PATH)/../comm-core \
	$(LOCAL_PATH)/../../include/communication \

LOCAL_MODULE:= libcommunication
LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := -Werror -Wall

include $(BUILD_SHARED_LIBRARY)
