/*
 * Notification for the Notification Survey
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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QtCore/QObject>
#include <KDE/KWindowSystem>

class Notification: public QObject
{
Q_OBJECT

public:
    Notification(QObject* parent = 0);
    virtual ~Notification();

    void updateTimestamp();

    void captureScreenshot();
    QPixmap screenshot() const;

    void setApplicationName(const QString& appName);
    QString applicationName() const;

    void setSummary(const QString& summary);
    QString summary() const;

    void setMessage(const QString& message);
    QString message() const;

    void setActionList(const QStringList& actionList);
    QStringList actionList() const;

private:
    class Private;
    Private* const d; 

};

#endif

/* vim: set et sts=4 sw=4 ts=8 tw=78 : */
