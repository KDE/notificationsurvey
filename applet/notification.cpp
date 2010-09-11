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

#include "notification.h"

#include <QtGui/QPixmap>
#include <QtCore/QString>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>


class Notification::Private
{
public:
    QPixmap screenshot;
    QString applicationName;
    QString message;

};

Notification::Notification(QObject* parent)
   : QObject(parent), d(new Private)
{

}

Notification::~Notification()
{
    delete d;
}

void Notification::captureScreenshot()
{
    d->screenshot = QPixmap::grabWindow(QApplication::desktop()->winId());
}

QPixmap Notification::screenshot() const
{
    return d->screenshot;    
}

void Notification::setApplicationName(const QString& appName)
{
    d->applicationName = appName;
}

QString Notification::applicationName() const
{
    return d->applicationName;
}

void Notification::setMessage(const QString& message)
{
    d->message = message;
}

QString Notification::message() const
{
    return d->message;    
}

#include "notification.moc"

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
