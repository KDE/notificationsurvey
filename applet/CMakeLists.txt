# We add our source code here
set(notificationsurvey_SRCS
    surveyapplet.cpp
    notificationhandler.cpp
    notification.cpp
    )
 
# Now make sure all files get to the right place
kde4_add_plugin(plasma_applet_notificationsurvey 
                ${notificationsurvey_SRCS})
target_link_libraries(plasma_applet_notificationsurvey
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_notificationsurvey
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-notificationsurvey.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

# vim: set et tw=78 sts=4 sw=4 ts=8 :
