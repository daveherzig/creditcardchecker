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

#include "mainwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QDateTime>
#include <QMessageBox>

#include "eventhandler.h"
#include "util.h"

#include <string>
using namespace std;

MainWidget::MainWidget()
{
    createLayout();
    setupEventHandling();
}

MainWidget::~MainWidget() {
}

QString MainWidget::getCreditCardNumber()
{
    QString result("");
    for (int i=0; i<4; i++) {
        result += blockInput[i]->text();
    }    return result;
}

void MainWidget::getData(CreditCard & obj)
{
    qDebug() << "copy gui data into model";
    qDebug() << "model address: " << &obj;
    obj.setNumber(getCreditCardNumber());
    obj.setMonth(monthBox->currentText());
    obj.setYear(yearBox->currentText().toInt());
}

void MainWidget::onResultUpdate(CreditCard &obj)
{
    qDebug() << "validation status: " << obj.getValidationStatus();
    QString result;
    if (obj.getValidationStatus() == Util::VALID_NUMBER) {
        result = "Credit Card number is valid";
    } else if (obj.getValidationStatus() == Util::VALID_VISA) {
        result = "Credit Card number is valid (VISA)";
    } else if (obj.getValidationStatus() == Util::VALID_MASTER) {
        result = "Credit Card number is valid (MASTER)";
    } else if (obj.getValidationStatus() == Util::NUMBER_LENGTH_WRONG) {
        result = "Credit Card number has invlaid length";
    } else if (obj.getValidationStatus() == Util::NOT_A_NUMBER) {
        result = "Credit Card number is not valid (not a number)";
    } else if (obj.getValidationStatus() == Util::INVALID_NUMBER) {
        result = "Credit Card is not valid";
    } else {
        result = "Unknown code: ";
    }
    QMessageBox::information(this, "Validation Result", result);
}

void MainWidget::createLayout()
{
    QPixmap icon("creditcards.png");
    QLabel *iconLabel;
    if (icon.isNull()) {
        iconLabel = new QLabel("icon not found!");
    } else {
        iconLabel = new QLabel();
        iconLabel->setPixmap(icon.scaledToHeight(100));
    }
    QLabel *titleLabel = new QLabel("<H1>Credit Card Checker</H1>");

    blockInput = new QLineEdit*[4];
    for (int i=0; i<4; i++) {
        blockInput[i] = new QLineEdit();
        blockInput[i]->setMaxLength(4);
    }

    monthBox = new QComboBox();
    yearBox = new QComboBox();
    checkButton = new QPushButton("Check");
    clearButton = new QPushButton("Clear");

    this->setDefaultValues();

    // create layout
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(titleLabel, 0, 0, 1, 3);
    layout->addWidget(iconLabel, 0, 3);
    for (int i=0; i<4; i++) {
        layout->addWidget(blockInput[i], 1, i);
    }
    layout->addWidget(new QLabel("Month"), 2, 0);
    layout->addWidget(monthBox, 2, 1);
    layout->addWidget(new QLabel("Year"), 2, 2);
    layout->addWidget(yearBox, 2, 3);
    layout->addWidget(checkButton, 3, 0, 1, 2);
    layout->addWidget(clearButton, 3, 2, 1, 2);

    // set layout
    this->setLayout(layout);
}

void MainWidget::setDefaultValues()
{
    QString monthNames [] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"};
    for (QString mName : monthNames) {
        monthBox->addItem(mName);
    }

    // for the year, take the current year and add the next 10 years
    QDateTime currentDate = QDateTime::currentDateTime();
    int currentYear = currentDate.date().year();
    const int NUMBER_OF_YEARS = 10;
    for (int i=0; i<NUMBER_OF_YEARS; i++) {
        QString year = QString::number(currentYear + i);
        yearBox->addItem(year);
    }

    for (int i=0; i<4; i++) {
        blockInput[i]->setPlaceholderText("1234");
    }
}

void MainWidget::setupEventHandling()
{
    EventHandler *handler = new EventHandler();
    QObject::connect(
        checkButton, SIGNAL(clicked()),
        handler, SLOT(onCheckButtonClicked())
    );
    QObject::connect(
        handler, SIGNAL(retreiveGuiData(CreditCard&)),
        this, SLOT(getData(CreditCard&))
    );
    QObject::connect(
        handler, SIGNAL(updateResult(CreditCard&)),
        this, SLOT(onResultUpdate(CreditCard&))
    );
    for (int i=0; i<4; i++) {
        QObject::connect(
            clearButton, SIGNAL(clicked()),
            blockInput[i], SLOT(clear()));
    }
}
