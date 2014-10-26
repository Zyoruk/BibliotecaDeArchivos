TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    konstants.cpp \
    pointers/diskpointer.cpp \
    pointers/rampointer.cpp

HEADERS += \
    konstants.h \
    array/array.h \
    interfaces/iData.h \
    interfaces/interfaceNode.h \
    interfaces/iPointer.h \
    pointers/diskpointer.h \
    pointers/rampointer.h

