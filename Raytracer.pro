TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ray.cpp \
    vector.cpp \
    sphere.cpp \
    scene.cpp \
    material.cpp

HEADERS += \
    ray.h \
    vector.h \
    sphere.h \
    scene.h \
    helpers.h \
    material.h

QMAKE_CFLAGS_RELEASE += -fopenmp
QMAKE_CFLAGS_DEBUG += -fopenmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp

