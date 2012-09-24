TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL -lSDLmain -lSDL_image

SOURCES += \
    CSurface.cpp \
    CEvent.cpp \
    CApp_OnRender.cpp \
    CApp_OnLoop.cpp \
    CApp_OnInit.cpp \
    CApp_OnEvent.cpp \
    CApp_OnCleanup.cpp \
    CApp.cpp \
    CAnimation.cpp \
    CArea.cpp \
    CCamera.cpp \
    CEntity.cpp \
    CEntityCol.cpp \
    CFPS.cpp \
    CMap.cpp \
    CPlayer.cpp \
    CTile.cpp

HEADERS += \
    CSurface.h \
    CApp.h \
    CEvent.h \
    CAnimation.h \
    CArea.h \
    CCamera.h \
    CEntity.h \
    CFPS.h \
    CMap.h \
    CPlayer.h \
    CTile.h \
    Define.h

OTHER_FILES += \
    gfx/grid.bmp \
    myimage.bmp \
    gfx/x.bmp \
    gfx/o.bmp \
    README.txt

