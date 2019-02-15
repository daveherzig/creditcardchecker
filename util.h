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

#ifndef UTIL_H
#define UTIL_H

#include <QString>

class CreditCard;

class Util
{
private:
    /*!
     * \brief Util
     * Private constructor as this is a utility class.
     */
    Util();

public:

    const static int VALID_NUMBER = 0;
    const static int VALID_VISA = 1;
    const static int VALID_MASTER = 2;
    const static int NUMBER_LENGTH_WRONG = 3;
    const static int NOT_A_NUMBER = 4;
    const static int INVALID_NUMBER = 5;

    const static QString XML_ROOT_KEY;
    const static QString XML_NUMBER_KEY;
    const static QString XML_BLOCK_KEY;
    const static QString XML_MONTH_KEY;
    const static QString XML_YEAR_KEY;

    /*!
     * \brief Implementation of the Luhn algorithmus to check wether a credit card
     * number is valid or not.
     * \param number The credit card number
     * \return A number (code) about the validation. All possible codes are defined
     * as constant static variables in this class.
     */
    static int validateNumber(QString number);

    static void saveData(CreditCard *c, QString filename);
    static void loadData(CreditCard *c, QString filename);
};

#endif // UTIL_H
