QT += core
QT -= gui

CONFIG += c++11

TARGET = MCMediaLibrary
CONFIG += console
CONFIG -= app_bundle
DEFINES+= protobuf_MSVC_STATIC_RUNTIME=OFF
DEFINES+= protobuf_BUILD_SHARED_LIBS=ON
TEMPLATE = app
INCLUDEPATH += "C:/Program Files/taglib/include"
LIBS += -L"C:/Program Files/taglib/lib" -ltag

SOURCES += main.cpp \
    controller.cpp \
    mediascanner.cpp

LIBS += -LC:\Users\Michael\Downloads\Programming\protobuf-all-3.5.1\protobuf-3.5.1\cmake\build -llibprotobufd

include(../MCIPC/MCIPC.pri)
INCLUDEPATH += C:/Users/Michael/Downloads/Programming/protoc-3.5.1-win32/include \
	C:/Users/Michael/Downloads/Programming/protobuf-all-3.5.1/protobuf-3.5.1/src
HEADERS += \
    controller.h \
    mediascanner.h \
    mediameta.h

include(protobuf.pri)


PROTOS +=     MediaFile.proto \
    Playlist.proto \
MediaStatusMessage.proto
