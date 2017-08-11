TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

#CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d


#INCLUDEPATH += D:/SFML1/include
#DEPENDPATH += D:/SFML1/include
RC_FILE = project1_resource.rc
SOURCES += main.cpp \
    animation.cpp \
    animationmanager.cpp\
    player.cpp \
    level.cpp \
    entity.cpp \
    game.cpp \
    bullet.cpp \
    enemy.cpp \
    statusbar.cpp \
    loading.cpp

HEADERS += \
    animation.h \
    animationmanager.h\
    player.h \
    level.h \
    constants.h \
    entity.h \
    game.h \
    bullet.h \
    enemy.h \
    statusbar.h \
    loading.h

win32: LIBS += -L$$PWD/lib/ -lTinyXML2

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/TinyXML2.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libTinyXML2.a


win32: LIBS += -L$$PWD/lib/ -lBox2D

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/Box2D.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libBox2D.a

win32: LIBS += -L$$PWD/lib/SFML/ -lsfml-graphics

INCLUDEPATH += $$PWD/lib/SFML
DEPENDPATH += $$PWD/lib/SFML

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/sfml-graphics.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/libsfml-graphics.a

win32: LIBS += -L$$PWD/lib/SFML/ -lsfml-audio

INCLUDEPATH += $$PWD/lib/SFML
DEPENDPATH += $$PWD/lib/SFML

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/sfml-audio.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/libsfml-audio.a

win32: LIBS += -L$$PWD/lib/SFML/ -lsfml-main

INCLUDEPATH += $$PWD/lib/SFML
DEPENDPATH += $$PWD/lib/SFML

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/sfml-main.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/libsfml-main.a

win32: LIBS += -L$$PWD/lib/SFML/ -lsfml-system

INCLUDEPATH += $$PWD/lib/SFML
DEPENDPATH += $$PWD/lib/SFML

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/sfml-system.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/libsfml-system.a

win32: LIBS += -L$$PWD/lib/SFML/ -lsfml-window

INCLUDEPATH += $$PWD/lib/SFML
DEPENDPATH += $$PWD/lib/SFML

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/sfml-window.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/SFML/libsfml-window.a

RC_FILE = icon.rc
OTHER_FILES += icon.rc

DISTFILES += \
    icon.rc
