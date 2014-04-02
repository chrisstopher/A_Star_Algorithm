TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Vec2i.cpp \
    Map.cpp \
    Score.cpp \
    Node.cpp \
    Astar.cpp \
    Heuristics.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    Vec2i.h \
    Map.h \
    Score.h \
    Node.h \
    Astar.h \
    Heuristics.h \
    Dynamic2dArray.h
