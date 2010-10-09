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

#include "surveydata.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <KDE/KDebug>
#include <KDE/KConfigGroup>
#include <KDE/KComponentData>

#include "notification.h"


static const QString CONFIG_GROUP_NAME = QString("General");
static const QString END_DATE_KEY = QString("SurveyEndDate");
static const QString SURVEY_STARTED_KEY = QString("SurveyStarted");
static const QString NOTIFICATION_COUNT_KEY = QString("NotificationCount");

SurveyData::SurveyData()
{
    QDir homeDir;
    homeDir.cd(QDir::homePath());
    QFileInfo surveyFileInfo(homeDir, ".notificationsurvey");
    if (!surveyFileInfo.exists())
    {
        homeDir.mkdir(".notificationsurvey");
    }

    homeDir.cd(".notificationsurvey");
    surveyFileInfo.setFile(homeDir, ".surveystats");
    KComponentData componentData(QByteArray("notificationsurvey"));
    m_config = KSharedConfig::openConfig(componentData,
                                         surveyFileInfo.canonicalFilePath());

}

SurveyData::~SurveyData()
{

}

void SurveyData::setSurveyEndDate(const QDateTime& endDate)
{
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    cg.writeEntry(END_DATE_KEY, endDate.toString());
    m_config->sync();
}

QDateTime SurveyData::surveyEndDate() const
{
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    QString dateString = cg.readEntry(END_DATE_KEY, QString());
    return QDateTime::fromString(dateString);

}

void SurveyData::setSurveyStarted(bool isSurveyStarted)
{
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    cg.writeEntry(SURVEY_STARTED_KEY, isSurveyStarted);
    m_config->sync();
}

bool SurveyData::isSurveyStarted() const
{
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    return cg.readEntry(SURVEY_STARTED_KEY, false);
}

bool SurveyData::needToDoSurvey() const
{
    if (notificationCount() > 0 && notificationCount() % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

void SurveyData::increaseNotificationCount()
{
    int newCount = notificationCount() + 1;
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    cg.writeEntry(NOTIFICATION_COUNT_KEY, newCount);
    m_config->sync();
}

int SurveyData::notificationCount() const
{
    KConfigGroup cg(m_config, CONFIG_GROUP_NAME);
    int count = cg.readEntry(NOTIFICATION_COUNT_KEY, 0);
    return count;
}

void SurveyData::logNotification(Notification* notification)
{

}
