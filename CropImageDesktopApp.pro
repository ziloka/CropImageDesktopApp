QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/imagecropperscene.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/imagecropperscene.hpp \
    include/mainwindow.hpp \
    include/custompainter.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    assets/Copy.bmp \
    assets/Cut.bmp \
    assets/DeleteSticky.bmp \
    assets/New.bmp \
    assets/Open.bmp \
    assets/Paste.bmp \
    assets/Save.bmp \
    assets/Sticky.bmp
