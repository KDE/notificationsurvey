/*
 * Notification Survey Applet
 *
 * Copyright 2010 Matt Rogers <mattr@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy 
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "surveyapplet.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsLinearLayout>

#include <KDE/KIconLoader>

#include <Plasma/Extender>
#include <Plasma/ToolTipContent>
#include <Plasma/ToolTipManager>

#include "notificationhandler.h"
#include "busywidget.h"

K_EXPORT_PLASMA_APPLET(notificationsurvey, NotificationsSurvey)

NotificationsSurvey::NotificationsSurvey(QObject* parent,
                                         const QVariantList &arguments)
    : Plasma::PopupApplet(parent, arguments),
      m_icon("applications-system"),
      m_handler(new NotificationHandler(this)),
      m_busyWidget(0)
{
    setBackgroundHints(NoBackground);
    setAspectRatioMode(Plasma::IgnoreAspectRatio);
    
}

NotificationsSurvey::~NotificationsSurvey()
{

}

void NotificationsSurvey::init()
{
    Plasma::ToolTipContent data(i18n("Listening for notifications"),
                                QString(),
                                KIcon("dialog-information"));
    Plasma::ToolTipManager::self()->setContent(this, data);
   
    m_handler->init();

    m_busyWidget = new BusyWidget(this);
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addItem(m_busyWidget);
    setStatus(Plasma::NeedsAttentionStatus);
}


#include "surveyapplet.moc"

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
