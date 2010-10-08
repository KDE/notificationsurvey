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
#include <KDE/KNotification>

#include <Plasma/Extender>
#include <Plasma/ToolTipContent>
#include <Plasma/ToolTipManager>
#include <Plasma/ExtenderItem>

#include "busywidget.h"
#include "surveydata.h"
#include "notification.h"
#include "notificationhandler.h"
#include "surveycontrolwidget.h"

K_EXPORT_PLASMA_APPLET(notificationsurvey, NotificationsSurvey)

class NotificationsSurvey::Private
{
public:
    Private()
    : icon("applications-system"),
      handler(new NotificationHandler),
      busyWidget(0),
      surveyControlWidget(0),
      surveyData(new SurveyData)
    {

    }

    ~Private()
    {
        delete handler;
        delete surveyData;
    }

    KIcon icon;
    NotificationHandler* handler;
    BusyWidget* busyWidget;
    SurveyControlWidget* surveyControlWidget;
    SurveyData* surveyData;
};

NotificationsSurvey::NotificationsSurvey(QObject* parent,
                                         const QVariantList &arguments)
    : Plasma::PopupApplet(parent, arguments),
      d(new NotificationsSurvey::Private)
{
    setBackgroundHints(NoBackground);
    setAspectRatioMode(Plasma::IgnoreAspectRatio);
    setPopupIcon(QIcon());
}

NotificationsSurvey::~NotificationsSurvey()
{
    delete d;
}

void NotificationsSurvey::init()
{
    Plasma::ToolTipContent data(i18n("Listening for notifications"),
                                QString(),
                                KIcon("dialog-information"));
    Plasma::ToolTipManager::self()->setContent(this, data);

    if (d->surveyData->isSurveyStarted()) {
        kDebug() << "survey has started. initializing handler";
        initializeHandler();
    }

    extender()->setEmptyExtenderMessage(i18n("Listening for notifications"));

    d->busyWidget = new BusyWidget(this);
    connect(d->busyWidget, SIGNAL(clicked()), this, SLOT(togglePopup()));
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addItem(d->busyWidget);
    setStatus(Plasma::NeedsAttentionStatus);

    configChanged();

    Plasma::ExtenderItem* eitem = new Plasma::ExtenderItem(extender());
    eitem->setName("notifications");
    eitem->setIcon("dialog-information");
    eitem->config().writeEntry("type", "notificationsurvey");
    initExtenderItem(eitem);
    extender()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}


void NotificationsSurvey::startSurvey()
{
    d->surveyData->setSurveyStarted(true);

    QDateTime surveyEndDate = QDateTime::currentDateTime();
    surveyEndDate = surveyEndDate.addDays(28); //convert from magic number

    d->surveyData->setSurveyEndDate(surveyEndDate);

}

QDateTime NotificationsSurvey::surveyEndDate() const
{
    return d->surveyData->surveyEndDate();
}

bool NotificationsSurvey::isSurveyStarted() const
{
    return d->surveyData->isSurveyStarted();
}

void NotificationsSurvey::initExtenderItem(Plasma::ExtenderItem* item)
{
    kDebug() << "initializing extender item";
    if (item->name() == "notifications") {
        item->setIcon("dialog-information");
        d->surveyControlWidget = new SurveyControlWidget(this);
        item->setWidget(d->surveyControlWidget);
        item->setTitle(i18n("Notification Survey Status"));
    }
}

void NotificationsSurvey::initializeHandler()
{
    d->handler->init();
    connect(d->handler, SIGNAL(notificationUpdated(Notification*)),
            this, SLOT(processNotification(Notification*)));
}

void NotificationsSurvey::processNotification(Notification* notification)
{
    d->surveyData->increaseNotificationCount();

    if (d->surveyData->needToDoSurvey())
    {
        notification->captureScreenshot();
        sendSurveyNotification(notification);
        d->surveyData->logNotification(notification);
    }
}

void NotificationsSurvey::sendSurveyNotification(Notification* notification)
{
    /* lots of magic strings */
    QString eventId = QLatin1String("new_diary_entry");
    KNotification* notify = new KNotification(eventId,
                                              KNotification::Persistent,
                                              this);
    notify->setFlags(KNotification::Persistent);
    notify->setComponentData(KComponentData("notificationsurvey"));
    notify->setActions( QStringList() << i18nc("@action", "No")
                                      << i18nc("@action", 
                                               "Yes, Create new diary entry"));
    QString bodyText = i18n("You recently received a notification from %1.\n"
                            "Would you like to create a new diary entry about"
                            "this notification?",
                            notification->applicationName());

    notify->setText(bodyText);

    notify->sendEvent();
}
#include "surveyapplet.moc"

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
