QT += widgets
requires(qtConfig(treeview))

SOURCES       = main.cpp \
    myfilemodel.cpp \
    window.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/dirview
INSTALLS += target

HEADERS += \
    myfilemodel.h \
    window.h
