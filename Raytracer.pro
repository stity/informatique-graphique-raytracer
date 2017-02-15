TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    ray.cpp \
    vector.cpp \
    sphere.cpp \
    scene.cpp \
    material.cpp \
    object.cpp \
    boundingbox.cpp

HEADERS += \
    ray.h \
    vector.h \
    sphere.h \
    scene.h \
    helpers.h \
    material.h \
    geometry.h \
    object.h \
    boundingbox.h

QMAKE_CFLAGS_RELEASE += -fopenmp
QMAKE_CFLAGS_DEBUG += -fopenmp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS +=  -fopenmp \
                 -O3
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE +=  -O3
QMAKE_LFLAGS_RELEASE -=  -O1

OTHER_FILES += \
    girl.obj

