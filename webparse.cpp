#include <QRegExp>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>
#include <QEventLoop>

#include "webparse.h"
#include "menue.h"

WebParse::WebParse(QString location, QObject *parent) :
    QObject(parent)
{
    m_location = location;

    m_qnam = new QNetworkAccessManager(this);
}

QList<Menue> WebParse::download()
{
    QUrl url("http://www.studentenwerkdarmstadt.de/essen/mensa-stadtmitte.html");

    QNetworkRequest request(url);
    connect(m_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished()));
    m_reply = m_qnam->get(request);

    QEventLoop loop;
    connect(this, SIGNAL(parsed()), &loop, SLOT(quit()));
    loop.exec();

    loop.deleteLater();
    return m_results;
}

/**
 * @brief Called when the result was downloaded
 *        Emits "getDone" if there are no more pages in the result set
 * @see WebParse::parsePage
 */
void WebParse::replyFinished()
{
    if (m_reply->error() == QNetworkReply::NoError ) {
        QString msg = m_reply->readAll();
        m_results = parsePage(msg);
    } else {
        qDebug() << "Network Error" << m_reply->errorString();
        m_results = QList<Menue>();
        m_results.append(Menue(m_reply->errorString(), "", "", ""));
    }

    m_reply->deleteLater();
    emit parsed();
}

/**
 * @brief Parses the results
 * @param html Downloaded HTML data
 * @return List of results
 */
QList<Menue> WebParse::parsePage(QString html)
{
    QList<Menue> results;

    QRegExp rx("<tr><th></th><th class=\"hl_today\">([\\w,\\s\\.\\d]+)</th></tr>");
    if (rx.indexIn(html) != -1)
        m_today = rx.cap(1);

    int pos = 0;
    rx.setPattern("<tr><td valign=\"top\">([\\s\\w&;\\.]*)</td><td valign=\"top\"><img class=\"spk_img\" src=\"components/com_spk/images/[\\w]*pict_k.jpg\" alt=\"([\\w]*)\" width=\"50px\" />([\\w&;\\s!\\-\\(\\d\\,\\)]*) [\\w]{1} ([\\d\\,]{4})");
    rx.setMinimal(true);

    while ((pos = rx.indexIn(html, pos)) != -1) {
        Menue result;

        result.setLocation(rx.cap(1).replace("&nbsp;", ""));
        result.setType(rx.cap(2));
        result.setName(replaceHtml(rx.cap(3)));
        result.setPrice(rx.cap(4).append(" €"));

        results.append(result);
        pos += rx.matchedLength();
    }

    rx.setPattern("<br />&nbsp;<br /><table border=\"1\" class=\"spk_table\"><tr><th></th><th class=\"hl_today\">([\\d\\.\\s\\w,]*)</th></tr>");
    if (rx.indexIn(html) != -1)
        m_day = rx.cap(1);

    return results;
}

QString WebParse::replaceHtml(QString in)
{
    return in.replace("&uuml;", "ü").replace("&quot;", "\"")
            .replace("&auml;", "ä").replace("&ouml;", "ö");
}

QString WebParse::breakName(QString in, int lineLen)
{
    for (int i = 0; i < 10; i++) {
        if (in.length() > lineLen * i) {
            in.insert(lineLen * i, "\n");
        }
    }
    return in;
}

/**
 * @brief Just returns a pointer to the network access manager
 * @return Network Access Manager
 */
QNetworkAccessManager *WebParse::qnam()
{
    return m_qnam;
}

QString WebParse::getDay() const
{
    return m_day;
}
