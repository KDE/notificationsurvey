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
#include <Plasma/ExtenderItem>

#include "notificationhandler.h"
#include "busywidget.h"
#include "surveycontrolwidget.h"

K_EXPORT_PLASMA_APPLET(notificationsurvey, NotificationsSurvey)

class NotificationsSurvey::Private
{
public:
    Private()
    : icon("applications-system"),
      handler(new NotificationHandler),
      busyWidget(0),
      isSurveyStarted(false)
    {

    }

    ~Private()
    {
        delete handler;
        delete busyWidget;
    }

    KIcon icon;
    NotificationHandler* handler;
    BusyWidget* busyWidget;
    SurveyControlWidget* surveyControlWidget;
    bool isSurveyStarted;
    QDateTime surveyEndDate;
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
   
    d->handler->init();

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

void NotificationsSurvey::configChanged()
{
    KConfigGroup cg = config();

    d->isSurveyStarted = cg.readEntry("SurveyStarted", false);
    kDebug() << "Survey status - started: " << d->isSurveyStarted;
    if (d->isSurveyStarted) {
        QString dateString = cg.readEntry("SurveyEndDate");
        d->surveyEndDate = QDateTime::fromString(dateString);
        kDebug() << "Survey end date: " << d->surveyEndDate;
    }
}

void NotificationsSurvey::startSurvey()
{
    d->isSurveyStarted = true;

    KConfigGroup cg = config();
    cg.writeEntry("SurveyStarted", d->isSurveyStarted); 

    d->surveyEndDate = QDateTime::currentDateTime();
    d->surveyEndDate.addDays(28); //convert from magic number
    cg.writeEntry("SurveyEndDate", d->surveyEndDate.toString());

    emit configNeedsSaving();
}

QDateTime NotificationsSurvey::surveyEndDate() const
{
    return d->surveyEndDate;
}

bool NotificationsSurvey::isSurveyStarted() const
{
    return d->isSurveyStarted;
}

void NotificationsSurvey::initExtenderItem(Plasma::ExtenderItem* item)
{
    kDebug() << "initializing extender item";
    if (item->name() == "notifications") {
        //item->setIcon("dialog-information");
        d->surveyControlWidget = new SurveyControlWidget(this);
        item->setWidget(d->surveyControlWidget);
        //item->setTitle(i18n("Notifications Survey"));
    }
}


#include "surveyapplet.moc"

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
