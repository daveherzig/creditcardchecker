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
#include <QFileDialog>

#include "mainwidget.h"
#include "util.h"

void EventHandler::onCheckButtonClicked()
{
    // retrieve input data
    qDebug() << "EventHandler::onCheckButtonClicked";
    CreditCard cc;
    emit retreiveGuiData(cc);

    // calculate result
    cc.setValidationStatus(Util::validateNumber(cc.getCompleteNumber()));

    // display result
    emit updateResult(cc);
}

void EventHandler::save()
{
    qDebug() << "EventHandler::save";
    CreditCard cc;
    emit retreiveGuiData(cc);
    QString filename = QFileDialog::getSaveFileName();
    if (!filename.isEmpty()) {
        Util::saveData(&cc, filename);
    }
}

void EventHandler::load()
{
    qDebug() << "EventHandler::load";
    CreditCard cc;
    QString filename = QFileDialog::getOpenFileName();
    if (!filename.isEmpty()) {
        Util::loadData(&cc, filename);
        qDebug("fire event pushGuiData");
        emit pushGuiData(cc);
    }
}
