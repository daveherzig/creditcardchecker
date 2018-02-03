/*
 * Copyright (C) 2018 David Herzig (dave.herzig@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>

#include "creditcard.h"

class MainWidget;

/*!
 * \brief The EventHandler class
 * This class is used to handle the event when the check button is clicked.
 * Of course, for this project, this is kind of over engineering, but it
 * should just demonstrate the separation of gui and event handling.
 */
class EventHandler : public QObject
{
Q_OBJECT

public slots:
    void onCheckButtonClicked();

signals:
    void retreiveGuiData(CreditCard & obj);
    void updateResult(CreditCard & obj);
};

#endif // EVENTHANDLER_H
