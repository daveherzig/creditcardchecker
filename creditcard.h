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

#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <QString>

/*!
 * \brief The CreditCard class
 * Simple class with some attributes and only getter and setter methods. This class
 * acts as the model class within this project.
 */
class CreditCard
{
private:
    // input values
    QString number;
    QString month;
    int year;

    // output values
    int validationStatus;
    QString type;

public:
    void setNumber(QString number);
    QString getNumber();
    QString getMonth() const;
    void setMonth(QString value);
    int getYear() const;
    void setYear(int value);
    QString getType() const;
    void setType(const QString &value);
    int getValidationStatus() const;
    void setValidationStatus(int value);
};

#endif // MODEL_H
