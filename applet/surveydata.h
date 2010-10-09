/*
 * Notifications Survey Configuration Handler
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

#ifndef SURVEYCONFIGURATION_H
#define SURVEYCONFIGURATION_H

#include <QtCore/QFileInfo>
#include <KDE/KSharedConfig>

class QString;

class Notification;

class SurveyData
{
public:
    SurveyData();
    virtual ~SurveyData();

    void setSurveyEndDate(const QDateTime& endDate);
    QDateTime surveyEndDate() const;

    void setSurveyStarted(bool isSurveyStarted);
    bool isSurveyStarted() const;

    bool needToDoSurvey() const;

    void increaseNotificationCount();
    int notificationCount() const;

    void logNotification(Notification*);

private:
    QString dataPath(const QString& file);

private:
    KSharedConfig::Ptr m_config;
};

#endif

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
