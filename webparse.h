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
#ifndef WEBPARSE_H
#define WEBPARSE_H

#include <QObject>
#include <QtNetwork/QNetworkReply>
#include <QDate>

#include "menue.h"

/**
 * @brief The WebParse class is a web parser for
 * http://www.studentenwerkdarmstadt.de/essen/mensa-<location>.html
 */
class WebParse : public QObject
{
    Q_OBJECT
public:
    QList<Menue> download();
    explicit WebParse(int location, QObject *parent = 0);
    QString getDay() const;
    void setLocation(int newLocation);
    QString getLocationName();

private:
    QList<Menue> parsePage(QString html);
    QNetworkReply *m_reply;
    QNetworkAccessManager *qnam();
    QNetworkAccessManager *m_qnam;
    QString m_location;
    int m_locationNum;
    QList<Menue> m_results[5];
    QString m_today;
    QString breakName(QString in, int lineLen);
    QString replaceHtml(QString in);
    QString m_day;
    QDate m_downloadDate[5];

private slots:
    void replyFinished();

signals:
    void parsed();

public slots:

};

#endif // WEBPARSE_H
