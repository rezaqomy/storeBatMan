QT       += core gui
QT       += sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ShowCartPage.cpp \
    ShowProductsPage.cpp \
    addprudoctviewer.cpp \
    animation.cpp \
    customer.cpp \
    database.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    ordercard.cpp \
    product.cpp \
    productcard.cpp \
    showordermoreinformation.cpp

HEADERS += \
    addprudoctviewer.h \
    animation.h \
    customer.h \
    database.h \
    mainwindow.h \
    order.h \
    ordercard.h \
    product.h \
    productcard.h \
    showordermoreinformation.h

FORMS += \
    addprudoctviewer.ui \
    mainwindow.ui \
    showordermoreinformation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
target.path = $$[QT_INSTALL_EXAMPLES]/sql/cachedtable

RESOURCES += \
    Icons.qrc
