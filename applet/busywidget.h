/*
 * Notification Survey Busy Widget
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

#ifndef BUSYWIDGET_H
#define BUSYWIDGET_H

#include <Plasma/BusyWidget>


class QStyleOptionGraphicsItem;
class QSequentialAnimationGroup;

namespace Plasma
{
    class Extender;
    class PopupApplet;
    class Svg;
}

class BusyWidget: public Plasma::BusyWidget
{
Q_OBJECT
public:
    enum State { NotStarted, Running, Notified, Ended };

    BusyWidget(Plasma::PopupApplet* parent);
    virtual ~BusyWidget();

    void paint(QPainter* painter, 
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = 0);

    void setState(State state);

protected:
    void resizeEvent(QGraphicsSceneResizeEvent* event);

private:
    Plasma::Svg* m_svg;
};


#endif

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
