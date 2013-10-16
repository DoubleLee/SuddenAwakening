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
    ResourceManager.hpp \
    AudioEffects.hpp \
    Button.hpp \
    ConfigLoader.hpp \
    Game.hpp \
    Logger.hpp \
    RandomGenerator.hpp \
    State.hpp \
    StateGamePlay.hpp \
    StateMainMenu.hpp \
    StringUtilities.hpp \
    tinyxml2.hpp

win32:INCLUDEPATH += C:\SFMLMinGW\include
win32:DEPENDPATH += C:\SFMLMinGW\include
win32:LIBS += -LC:\SFMLMinGW\lib



LIBS += -L/usr/lib64 -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
win32: LIBS += -lsfml-main


unix: QMAKE_CXXFLAGS += -std=c++11
