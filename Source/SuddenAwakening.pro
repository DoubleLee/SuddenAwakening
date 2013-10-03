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

INCLUDEPATH += C:\SFMLMinGW\include
DEPENDPATH += C:\SFMLMinGW\include
LIBS += -LC:\SFMLMinGW\lib

CONFIG(release, release|debug){
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
win32: LIBS += -lsfml-main
}

CONFIG(debug, release|debug){
LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
win32: LIBS += -lsfml-main-d
}

unix: QMAKE_CXXFLAGS += -std=c++11
