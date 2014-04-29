LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared
LOCAL_CPP_FEATURES += exceptions
LOCAL_CFLAGS := -std=c++11
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
                   ../../Classes/CCGestureRecognizer/CCSwipeGestureRecognizer.cpp \
                   ../../Classes/SavedUserData.cpp \
                   ../../Classes/task.cpp \
                   ../../Classes/worldmap.cpp \
                   ../../Classes/loadGame.cpp \
                   ../../Classes/TableViewTestScene.cpp \
                   ../../Classes/CustomTableViewCell.cpp \
                   ../../Classes/Script.cpp \
                   ../../CLasses/genre.cpp \
                   ../../Classes/ProductionOffice.cpp \
                   ../../Classes/TestGame.cpp \
                   ../../Classes/Inventory.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../../Extensions
#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../../../template
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,extensions)

