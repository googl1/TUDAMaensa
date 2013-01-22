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
#include <QStringBuilder>

#include "menue.h"

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

/**
 * @brief Menue::Menue
 */
Menue::Menue()
{
}

/**
 * @brief Menue::Menue
 * @param name Name of menu
 * @param location Name of location
 * @param type Type of meal
 * @param price Price
 */
Menue::Menue
(QString name, QString location, QString type, QString price)
{
    m_name = name;
    m_location = location;
    m_type = type;
    m_price = price;
}

/**
 * @brief Menue::getLocation returns m_location
 * @return location of menu
 */
QString Menue::getLocation() const
{
    return m_location;
}

/**
 * @brief Menue::getName returns m_name
 * @return name of menu
 */
QString Menue::getName() const
{
    return m_name;
}

/**
 * @brief Menue::getType returns m_type
 * @return type of menu
 */
QString Menue::getType() const
{
    return m_type;
}

/**
 * @brief Menue::getPrice returns m_price
 * @return price
 */
QString Menue::getPrice() const
{
    return m_price;
}

/**
 * @brief Menue::isVeggie tells if menu is vegetarian
 * @return true if vegetarian, false if not
 */
bool Menue::isVeggie() const
{
    return !m_type.compare("fleischlos") || m_type.isEmpty();
}

/**
 * @brief Menue::isVegan tells if menu says it would be vegan
 * @return true if vegan, false if not
 */
bool Menue::isVegan() const
{
    return m_name.contains("vegan", Qt::CaseInsensitive);
}

/**
 * @brief Menue::setLocation sets m_location
 * @param location location of menu
 */
void Menue::setLocation(QString location)
{
    m_location = location;
}

/**
 * @brief Menue::setName sets m_name
 * @param name name of menu
 */
void Menue::setName(QString name)
{
    m_name = name;
}

/**
 * @brief Menue::setType sets m_type
 * @param type type of food
 */
void Menue::setType(QString type)
{
    m_type = type;
}

/**
 * @brief Menue::setPrice sets m_price
 * @param price price
 */
void Menue::setPrice(QString price)
{
    m_price = price;
}

/**
 * @brief Menue::getString returns QString represenation of menu
 * @return name price type and location
 */
QString Menue::getString() const
{
    QString message = m_name % QChar('\t') % m_price % QChar('\t')
            % m_type % QChar('\t') % m_location;
     return message;
}

