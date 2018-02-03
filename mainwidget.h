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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "creditcard.h"

class QComboBox;
class QLineEdit;
class QPushButton;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();
    ~MainWidget();
    QString getCreditCardNumber();

public slots:
    void getData(CreditCard & obj);
    void onResultUpdate(CreditCard &obj);

private:
    MainWidget(const MainWidget & obj);
    MainWidget operator=(const MainWidget & obj);

    void createLayout();
    void setDefaultValues();
    void setupEventHandling();

    QComboBox *monthBox;
    QComboBox *yearBox;

    QLineEdit *block1Input;
    QLineEdit *block2Input;
    QLineEdit *block3Input;
    QLineEdit *block4Input;

    QPushButton *checkButton;
};

#endif // MAINWIDGET_H
