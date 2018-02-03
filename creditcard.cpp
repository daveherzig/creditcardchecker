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

#include "creditcard.h"

QString CreditCard::getMonth() const
{
    return month;
}

void CreditCard::setMonth(QString value)
{
    month = value;
}

int CreditCard::getYear() const
{
    return year;
}

void CreditCard::setYear(int value)
{
    year = value;
}

int CreditCard::getValidationStatus() const
{
    return validationStatus;
}

void CreditCard::setValidationStatus(int value)
{
    validationStatus = value;
}

void CreditCard::setNumber(QString value)
{
    number = value;
}

QString CreditCard::getNumber()
{
    return number;
}

