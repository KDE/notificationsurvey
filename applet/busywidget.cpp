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

#include "busywidget.h"

#include <Plasma/PopupApplet>


BusyWidget::BusyWidget(Plasma::PopupApplet* parent)
 : Plasma::BusyWidget(parent),
   m_svg(new Plasma::Svg(this))
{
    setAcceptsHoverEvents(true);
    m_svg->setImagePath("icons/notification");
    m_svg->setContainsMultipleImages(true);
    setRunning(false);

}

BusyWidget::~BusyWidget()
{

}

void BusyWidget::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF iconRect(0,
                    0,
                    qMin(size().width(), size().height()),
                    qMin(size().width(), size().height()));

    iconRect.moveCenter(boundingRect().center());

    m_svg->paint(painter, iconRect, "notification-active");
}

void BusyWidget::setState(State state)
{
    Q_UNUSED(state);
}

void BusyWidget::resizeEvent(QGraphicsSceneResizeEvent*)
{
    m_svg->resize(contentsRect().size());
    m_svg->resize();
}

#include "busywidget.moc"

/* vim: set et sts=4 sw=4 ts=8 tw=78 : */

