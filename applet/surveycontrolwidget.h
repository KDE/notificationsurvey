/*
 * Notifications Survey Control Widget
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

#ifndef SURVEYCONTROLWIDGET_H
#define SURVEYCONTROLWIDGET_H

#include <QtGui/QGraphicsWidget>

namespace Plasma
{
    class Label;
    class PushButton;
    class PopupApplet;
}

class QGraphicsGridLayout;
class NotificationSurveyApplet;

class SurveyControlWidget : public QGraphicsWidget
{
Q_OBJECT

public:
    SurveyControlWidget(Plasma::PopupApplet* parent = 0);
    virtual ~SurveyControlWidget();

private:
    void updateSurveyStatus();

private slots:
    void startSurvey();

private:
    NotificationSurveyApplet* m_applet;
    QGraphicsGridLayout* m_layout;
    Plasma::PushButton* m_startButton;
    Plasma::Label* m_surveyStatus;
    Plasma::Label* m_surveyEndDate;
};

#endif
/* vim: set et fenc= ff=unix sts=4 sw=4 ts=16 : */
