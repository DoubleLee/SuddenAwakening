TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
	Logger.cpp \
	StringUtilities.cpp \
	RandomGenerator.cpp \
	Game.cpp \
	ConfigLoader.cpp \
	tinyxml2.cpp \
	State.cpp \
    AudioEffects.cpp \
    StateMainMenu.cpp \
    Button.cpp \
    StateGamePlay.cpp

HEADERS += \
	Logger.h \
	StringUtilities.h \
	RandomGenerator.h \
	Game.h \
	ConfigLoader.h \
	tinyxml2.h \
	State.h \
    AudioEffects.h \
    StateMainMenu.h \
    Button.h \
    StateGamePlay.h

win32:INCLUDEPATH += C:\SFMLMinGW\include
win32:DEPENDPATH += C:\SFMLMinGW\include
win32:LIBS += -LC:\SFMLMinGW\lib



LIBS += -L/usr/lib64 -lsfml-audio-2.0 -lsfml-graphics-2.0 -lsfml-network-2.0 -lsfml-window-2.0 -lsfml-system-2.0
win32: LIBS += -lsfml-main


unix: QMAKE_CXXFLAGS += -std=c++11
