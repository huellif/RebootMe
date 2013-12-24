SOURCES += main.cpp

symbian {
    my_deployment.pkg_prerules += vendorinfo

    DEPLOYMENT += my_deployment

    vendorinfo += "%{\"huellifSoft\"}" ":\"huellifSoft\""

    TARGET.UID3 += 0x20071fdb #from Nokia Developer support

    LIBS += -laknnotify -lcustrestartsys #reboot libary found in Symbian^3 sources

    TARGET.CAPABILITY += PowerMgmt #all reboot APIs need PowerMgmt

    ICON+= Icon.svg #thanks Blade for your icon

    #there are no Qt imports so the .sis doesn't need Qt dependencies
    default_deployment.pkg_prerules -= pkg_depends_webkit
    default_deployment.pkg_prerules -= pkg_depends_qt

    #Without of Qt we have to include this by hand
    INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\mw\
    INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\platform\
    INCLUDEPATH += C:\QtSDK\Symbian\SDKs\Symbian3Qt474\epoc32\include\platform\mw\
}

#pure native C++ is a bit faster
CONFIG -= qt
