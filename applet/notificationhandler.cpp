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

#include "notificationhandler.h"

#include <QtCore/QString>

#include <Plasma/DataEngineManager>
#include <Plasma/Service>
#include <Plasma/ServiceJob>

static const char engineName[] = "notifications";

NotificationHandler::NotificationHandler(QObject* parent)
    : QObject(parent),
      m_engine(0)
{
}

void NotificationHandler::init()
{
    kDebug() << "initializing engine";
    m_engine = Plasma::DataEngineManager::self()->loadEngine(engineName);

    if (!m_engine->isValid()) {
        kDebug() << "could not initialize engine";
        m_engine = 0;
        Plasma::DataEngineManager::self()->unloadEngine(engineName);
        return;
    }
    
    m_engine->connectAllSources(this);
    connect(m_engine, SIGNAL(sourceAdded(const QString&)),
            this, SLOT(prepareNotification(const QString&)));
}

NotificationHandler::~NotificationHandler()
{
    if (m_engine) {
        Plasma::DataEngineManager::self()->unloadEngine(engineName);
    }
}

void NotificationHandler::prepareNotification(const QString& source)
{
    kDebug() << "prepping new notification";
    if (m_engine) {
        kDebug() << "new source is" << source;
        m_engine->connectSource(source, this);
    }
    
}

void NotificationHandler::dataUpdated(const QString& source,
                                      const Plasma::DataEngine::Data& data)
{

    kWarning() << "New notification from" << source;
    kWarning() << "appname:" << data.value("appName").toString();
    kWarning() << "appicon:" << data.value("appIcon").toString();
    kWarning() << "summary:" << data.value("summary").toString();
    kWarning() << "body:" << data.value("body").toString();

}

#include "notificationhandler.moc"
/* vim: set et tw=78 sts=4 sw=4 ts=16 : */
