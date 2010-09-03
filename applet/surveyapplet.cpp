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

#include <QtGui/QPainter>

#include <Plasma/Extender>
#include <Plasma/ToolTipContent>
#include <Plasma/ToolTipManager>

#include "notificationhandler.h"

K_EXPORT_PLASMA_APPLET(notificationsurvey, NotificationsSurvey)

NotificationsSurvey::NotificationsSurvey(QObject* parent,
                                         const QVariantList &arguments)
    : Plasma::PopupApplet(parent, arguments),
      m_icon("applications-system"),
      m_handler(new NotificationHandler(this))
{
    setBackgroundHints(DefaultBackground);
    
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
}

void NotificationsSurvey::paintInterface(QPainter *p,
                                         const QStyleOptionGraphicsItem *option,
                                         const QRect& contentsRect)
{
    Q_UNUSED(option);

    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    // We place the icon
    p->drawPixmap(7, 7, m_icon.pixmap((int)contentsRect.width(),(int)contentsRect.height()-14 ));
}

#include "surveyapplet.moc"

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
