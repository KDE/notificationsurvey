/*
 * Notification Survey Notification Handler
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
 */

#ifndef NOTIFICATIONHANDLER_H
#define NOTIFICATIONHANDLER_H

#include <QtCore/QObject>

#include <Plasma/DataEngine>

class QString;

class NotificationHandler: public QObject
{
Q_OBJECT
public:
    NotificationHandler (QObject* parent = 0);
    virtual ~NotificationHandler();

    void init();

private slots:
    void prepareNotification(const QString& source);
    void dataUpdated(const QString& source, 
                     const Plasma::DataEngine::Data &data);
    void teardownNotification(const QString& source);
    

private:
    Plasma::DataEngine* m_engine;
    QStringList m_notifications;
};


#endif

/* vim: set et tw=78 sts=4 sw=4 ts=16 : */
