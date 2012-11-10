#ifndef WEBPARSE_H
#define WEBPARSE_H

#include <QObject>
#include <QtNetwork/QNetworkReply>

#include "menue.h"


class WebParse : public QObject
{
    Q_OBJECT
public:
    QList<Menue> download();
    explicit WebParse(QString location, QObject *parent = 0);
    QString getDay() const;

private:
    QList<Menue> parsePage(QString html);
    QNetworkReply *m_reply;
    QNetworkAccessManager *qnam();
    QNetworkAccessManager *m_qnam;
    QString m_location;
    QList<Menue> m_results;
    QString m_today;
    QString breakName(QString in, int lineLen);
    QString replaceHtml(QString in);
    QString m_day;

private slots:
    void replyFinished();

signals:
    void parsed();

public slots:

};

#endif // WEBPARSE_H
