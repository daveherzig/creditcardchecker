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

#include "eventhandler.h"

#include <QDebug>

#include "mainwidget.h"
#include "util.h"

void EventHandler::onCheckButtonClicked()
{
    // retrieve input data
    qDebug() << "check button has been clicked. retrieve data from gui";
    CreditCard cc;
    qDebug() << "model address: " << &cc;
    emit retreiveGuiData(cc);
    qDebug() << cc.getNumber() << " " << cc.getMonth() << " " << cc.getYear();

    // calculate result
    cc.setValidationStatus(Util::validateNumber(cc.getNumber()));

    // display result
    emit updateResult(cc);
}
