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
