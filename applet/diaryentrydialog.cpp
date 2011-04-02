/*
 * Notifications Survey Diary Entry Dialog
 *
 * Copyright 2011 Matt Rogers <mattr@kde.org>
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

#include "diaryentrydialog.h"

DiaryEntryDialog::DiaryEntryDialog(QWidget* parent)
    : KDialog(parent)
{
    QWidget* w = new QWidget(this);
    m_designerUi.setupUi(w);
    setMainWidget(w);

    setCaption("New Diary Entry");
    setButtons(KDialog::Ok | KDialog::Cancel);

    setEscapeButton(KDialog::Cancel);
    setDefaultButton(KDialog::Ok);
}

DiaryEntryDialog::~DiaryEntryDialog()
{

}



/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
