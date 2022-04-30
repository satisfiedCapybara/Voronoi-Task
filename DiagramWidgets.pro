QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    sources/Algorithms.cpp \
    sources/Exception.cpp \
    sources/Precision.cpp \
    sources/PrimitiveGeometry.cpp \
    sources/TopologyShape.cpp \
    sources/VoronoiTask.cpp \
    widget.cpp

HEADERS += \
    headers/Algorithms.h \
    headers/Exception.h \
    headers/Precision.h \
    headers/PrimitiveGeometry.h \
    headers/TopologyShape.h \
    headers/TypedefType.h \
    headers/VoronoiTask.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
