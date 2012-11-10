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
