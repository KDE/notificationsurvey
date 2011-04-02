/*
 * Notification Survey Control Widget
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

#include "surveycontrolwidget.h"

#include <QtGui/QGraphicsGridLayout>
#include <Plasma/PushButton>
#include <Plasma/Label>

#include "notificationsurveyapplet.h"

SurveyControlWidget::SurveyControlWidget(Plasma::PopupApplet* parent)
 : QGraphicsWidget(parent),
   m_layout(0)
{
    m_applet = qobject_cast<NotificationSurveyApplet*>(parent);


    m_startButton = new Plasma::PushButton(this);
    m_startButton->setText(i18n("Start Survey"));
    connect(m_startButton, SIGNAL(clicked()),
            this, SLOT(startSurvey()));

    m_surveyStatus = new Plasma::Label(this);
    m_surveyEndDate = new Plasma::Label(this);
    m_surveyStatus->setText(i18n("Survey in progress")); 
    m_surveyEndDate->setText(i18nc("placeholder is a date", "Ends: %1")
                             .arg(m_applet->surveyEndDate().toString()));

    m_layout = new QGraphicsGridLayout(this);
    m_layout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addItem(m_surveyStatus, 1, 1);
    m_layout->addItem(m_surveyEndDate, 2, 1);
    m_layout->addItem(m_startButton, 1, 1);

    updateSurveyStatus();
}

void SurveyControlWidget::updateSurveyStatus()
{

    if (!m_applet->isSurveyStarted()) {
        m_surveyStatus->hide();
        m_surveyEndDate->hide();
        m_startButton->show();
    } else {
        m_surveyStatus->setText(i18n("Survey in progress")); 
        m_surveyEndDate->setText(i18nc("placeholder is a date", "Ends: %1")
                                 .arg(m_applet->surveyEndDate().toString()));
        m_startButton->hide();
        m_surveyStatus->show();
        m_surveyEndDate->show();
    }

    m_layout->invalidate();
    update();

}

SurveyControlWidget::~SurveyControlWidget()
{

}

void SurveyControlWidget::startSurvey()
{
    m_applet->startSurvey();
    updateSurveyStatus();
}

/* vim: set et sts=4 sw=4 tw=78 : */

