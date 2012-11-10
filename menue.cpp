#include "menue.h"

#include <QStringBuilder>
#include <QTextEdit>

Menue::Menue()
{
}

Menue::Menue(QString name, QString location, QString type, QString price)
{
    m_name = name;
    m_location = location;
    m_type = type;
    m_price = price;
}

QString Menue::getLocation() const
{
    return m_location;
}

QString Menue::getName() const
{
    return m_name;
}

QString Menue::getType() const
{
    return m_type;
}

QString Menue::getPrice() const
{
    return m_price;
}

bool Menue::isVeggie() const
{
    return m_type.compare("fleischlos");
}

void Menue::setLocation(QString location)
{
    m_location = location;
}

void Menue::setName(QString name)
{
    m_name = name;
}

void Menue::setType(QString type)
{
    m_type = type;
}

void Menue::setPrice(QString price)
{
    m_price = price;
}

QString Menue::getString() const
{
    QString message = m_name % QChar('\t') % m_price % QChar('\t') % m_type % QChar('\t') % m_location;
     return message;
}

