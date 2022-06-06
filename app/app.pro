###################################################
#            Basic configuration
###################################################

TEMPLATE = app
TARGET   = RayTracer

QT = core gui widgets
#win*:QT += winextras

CONFIG += strict_c++ c++2a
CONFIG -= flat

mac* | linux* | freebsd{
	CONFIG(release, debug|release):CONFIG *= Release optimize_full
	CONFIG(debug, debug|release):CONFIG *= Debug
}

ARCHITECTURE = x64

Release:OUTPUT_DIR=release/$${ARCHITECTURE}
Debug:OUTPUT_DIR=debug/$${ARCHITECTURE}

DESTDIR  = ../bin/$${OUTPUT_DIR}
OBJECTS_DIR = ../build/$${OUTPUT_DIR}/$${TARGET}
MOC_DIR     = ../build/$${OUTPUT_DIR}/$${TARGET}
UI_DIR      = ../build/$${OUTPUT_DIR}/$${TARGET}
RCC_DIR     = ../build/$${OUTPUT_DIR}/$${TARGET}

###################################################
#               INCLUDEPATH
###################################################

INCLUDEPATH += \
	../qtutils \
	../cpputils \
	../cpp-template-utils

###################################################
#                 SOURCES
###################################################

SOURCES += \
	src/camera.cpp \
	src/main.cpp \
	src/mainwindow.cpp \
	src/raytracer.cpp \
	src/scene.cpp \
	src/sphere.cpp

FORMS += \
	src/mainwindow.ui

HEADERS += \
	src/camera.h \
	src/color.hpp \
	src/mainwindow.h \
	src/math/ray.hpp \
	src/math/size2d.hpp \
	src/math/vector.hpp \
	src/raytracer.h \
	src/scene.h \
	src/sphere.h \
	src/types.hpp


###################################################
#                 LIBS
###################################################


LIBS += -L../bin/$${OUTPUT_DIR} -lcpputils

mac*|linux*|freebsd{
	PRE_TARGETDEPS += $${DESTDIR}/libcpputils.a
}

###################################################
#    Platform-specific compiler options and libs
###################################################

win*{
	#LIBS += -lole32 -lShell32 -lUser32
	QMAKE_CXXFLAGS += /MP /Zi /wd4251
	QMAKE_CXXFLAGS += /permissive- /Zc:__cplusplus
	QMAKE_CXXFLAGS_WARN_ON = /W4
	DEFINES += WIN32_LEAN_AND_MEAN NOMINMAX _SCL_SECURE_NO_WARNINGS

	Release:QMAKE_CXXFLAGS += /GL

	QMAKE_LFLAGS += /TIME
	Debug:QMAKE_LFLAGS += /INCREMENTAL /DEBUG:FASTLINK
	Release:QMAKE_LFLAGS += /DEBUG /OPT:REF /OPT:ICF /LTCG:INCREMENTAL
}

mac*{
	LIBS += -framework AppKit

	QMAKE_POST_LINK = cp -f -p $$PWD/$$DESTDIR/*.dylib $$PWD/$$DESTDIR/$${TARGET}.app/Contents/MacOS/ || true
}

###################################################
#      Generic stuff for Linux and Mac
###################################################

linux*|mac*|freebsd{
	QMAKE_CXXFLAGS_WARN_ON = -Wall

	Release:DEFINES += NDEBUG=1
	Debug:DEFINES += _DEBUG
}

win32*:!*msvc2012:*msvc* {
	QMAKE_CXXFLAGS += /FS
}
