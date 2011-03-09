include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

# We add our source code here
set(notificationsurvey_SRCS
    notificationsurveyapplet.cpp
    notificationhandler.cpp
    notification.cpp
    busywidget.cpp
    surveycontrolwidget.cpp
    surveydata.cpp
    )

# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_notificationsurvey 
                ${notificationsurvey_SRCS})
target_link_libraries(plasma_applet_notificationsurvey
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS}
                      ${KDE4_KUTILS_LIBS})

install(TARGETS plasma_applet_notificationsurvey
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-applet-notificationsurvey.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

install(FILES notificationsurvey.notifyrc
        DESTINATION ${DATA_INSTALL_DIR}/notificationsurvey)

# vim: set et tw=78 sts=4 sw=4 ts=8 :
