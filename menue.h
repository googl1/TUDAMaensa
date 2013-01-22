/**
 *  This file is part of TUDA Maensa.
 *
 *  TUDA Maensa is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TUDA Maensa is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TUDA Maensa.  If not, see <http://www.gnu.org/licenses/>.
**/
#ifndef MENUE_H
#define MENUE_H

#include <QString>

/**
 * @brief The Menue class represents one menu.
 *  It contains it name, price, type and location as QStrings.
 */
class Menue //: public QObject
{
   // Q_OBJECT
public:
    Menue(QString name, QString location, QString type, QString price);
    Menue();
    QString getName() const;
    QString getLocation() const;
    QString getType() const;
    QString getPrice() const;
    bool isVeggie() const;
    bool isVegan() const;
    void setLocation(QString location);
    void setName(QString name);
    void setType(QString type);
    void setPrice(QString price);
    QString getString() const;

private:
    QString m_name;
    QString m_location;
    QString m_type;
    QString m_price;


};

#endif // MENUE_H
