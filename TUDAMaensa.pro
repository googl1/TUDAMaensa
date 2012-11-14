#-------------------------------------------------
#
# Project created by QtCreator 2012-11-09T10:33:50
#
#-------------------------------------------------

QT       += core gui network

TARGET = TUDAMaensa
TEMPLATE = app
RESOURCES     = maensa.qrc

SOURCES += main.cpp\
        mainwindow.cpp \
    menue.cpp \
    webparse.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    menue.h \
    webparse.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xed88754a
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

OTHER_FILES += \
    img/fischpict_k.png \
    img/wildpict_k.png \
    img/schweinpict_k.png \
    img/rindschweinpict_k.png \
    img/rindpict_k.png \
    img/lammpict_k.png \
    img/gefluegelpict_k.png \
    img/fleischlospict_k.png
