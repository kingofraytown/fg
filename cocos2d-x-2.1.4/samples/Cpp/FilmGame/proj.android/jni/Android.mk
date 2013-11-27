LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_CFLAGS := -std=gnu++11
LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/crew.cpp \
                   ../../Classes/baseRoom.cpp \
                   ../../Classes/roomConfig.cpp \
                   ../../Classes/StartPage.cpp \
                   ../../CLasses/sqlite3.c \
                   ../../Classes/Database.cpp \
                   ../../Classes/global.cpp \
                   ../../Classes/tinyxml/tinyxml.cpp \
                   ../../Classes/tinyxml/tinystr.cpp \
                   ../../Classes/tinyxml/tinyxmlerror.cpp \
                   ../../Classes/tinyxml/tinyxmlparser.cpp \
                   ../../Classes/CCGestureRecognizer/CCGestureRecognizer.cpp \
                   ../../Classes/CCGestureRecognizer/CCSwipeGestureRecognizer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

