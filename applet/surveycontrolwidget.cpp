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

#include "surveyapplet.h"

SurveyControlWidget::SurveyControlWidget(Plasma::PopupApplet* parent)
 : QGraphicsWidget(parent)
{
    m_applet = qobject_cast<NotificationsSurvey*>(parent);
    QGraphicsGridLayout* gridLayout = new QGraphicsGridLayout(this);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setColumnStretchFactor(0, 5);
    gridLayout->setColumnStretchFactor(2, 5);
    gridLayout->setRowStretchFactor(0,5);
    gridLayout->setRowStretchFactor(3,5);

    if (!m_applet->isSurveyStarted()) {

        Plasma::PushButton* startButton = new Plasma::PushButton(this);
        startButton->setText(i18n("Start Survey"));

        connect(startButton, SIGNAL(clicked()),
                this, SLOT(startSurvey()));
        gridLayout->addItem(startButton, 1, 1);
    } else {
        Plasma::Label *surveyStatus = new Plasma::Label(this);
        Plasma::Label *surveyEndDate = new Plasma::Label(this);
        surveyStatus->setText(i18n("Survey in progress")); 
        surveyEndDate->setText(i18nc("placeholder is a date", "Ends %1")
                               .arg(m_applet->surveyEndDate().toString()));
        gridLayout->addItem(surveyStatus, 1, 1);
        gridLayout->addItem(surveyEndDate, 2, 1);
    }
    
}

SurveyControlWidget::~SurveyControlWidget()
{

}

void SurveyControlWidget::startSurvey()
{
    m_applet->startSurvey();
}
