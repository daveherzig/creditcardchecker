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

#include "util.h"
#include "creditcard.h"

#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

const QString Util::XML_ROOT_KEY = QString("creditcard");
const QString Util::XML_NUMBER_KEY = QString("number");
const QString Util::XML_BLOCK_KEY = QString("block");
const QString Util::XML_MONTH_KEY = QString("month");
const QString Util::XML_YEAR_KEY = QString("year");

int Util::validateNumber(QString number)
{
    qDebug() << "Util::validateNumber";

    // check length
    if (number.trimmed().size() != 16) {
        return NUMBER_LENGTH_WRONG;
    }

    // check number
    bool ok;
    number.toLong(&ok);
    if (!ok) {
        return NOT_A_NUMBER;
    }

    // apply luhn formula
    int sum = 0;
    bool flag = false;
    for (int i=number.size()-1; i>=0; i--) {
        QString digit = QString(number.at(i));
        int n = digit.toInt();
        if (flag) {
            n = n * 2;
        }
        if (n >= 10) {
            n = n / 10 + n % 10;
        }
        sum += n;
        flag = !flag;
    }
    qDebug() << "credit card sum: " << sum;
    if (sum % 10 != 0) {
        return INVALID_NUMBER;
    }

    // check credit card type
    if (number.startsWith("4")) {
        return VALID_VISA;
    } else if (number.startsWith("51") ||
               number.startsWith("52") ||
               number.startsWith("53") ||
               number.startsWith("54") ||
               number.startsWith("55")) {
        return VALID_MASTER;
    } else {
        return VALID_NUMBER;
    }
}

void Util::saveData(CreditCard *c, QString filename)
{
    qDebug() << "Util::saveData";
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    if (!file.isOpen()) {
        qDebug() << "could not open file " << filename;
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(XML_ROOT_KEY);
    xmlWriter.writeStartElement(XML_NUMBER_KEY);
    for (int i=0; i<4; i++) {
        xmlWriter.writeTextElement(XML_BLOCK_KEY, c->getNumber(i));
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeTextElement(XML_YEAR_KEY, QString::number(c->getYear()));
    xmlWriter.writeTextElement(XML_MONTH_KEY, c->getMonth());
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

void Util::loadData(CreditCard *c, QString filename)
{
    qDebug() << "Util::loadData";

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen()) {
        qDebug() << "could not open file " << filename;
        return;
    }

    QXmlStreamReader xmlReader(&file);
    int index = 0;
    while (xmlReader.readNextStartElement()) {

        if (xmlReader.name() == XML_ROOT_KEY) {
            while (xmlReader.readNextStartElement()) {
                if (xmlReader.name() == XML_NUMBER_KEY) {
                    while(xmlReader.readNextStartElement()) {
                        if (xmlReader.name() == XML_BLOCK_KEY) {
                            QString text = xmlReader.readElementText();
                            qDebug() << "read block: " << text;
                            c->setNumber(text, index);
                            index++;
                        } else {
                            xmlReader.skipCurrentElement();
                        }
                    }
                } else if (xmlReader.name() == XML_YEAR_KEY) {
                    QString text = xmlReader.readElementText();
                    qDebug() << "read year: " << text;
                    c->setYear(text.toInt());
                } else if (xmlReader.name() == XML_MONTH_KEY) {
                    QString text = xmlReader.readElementText();
                    qDebug() << "read month: " << text;
                    c->setMonth(text);
                } else {
                    xmlReader.skipCurrentElement();
                }
            }
        }
    }

    file.close();
}
