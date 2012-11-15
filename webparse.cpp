#include <QRegExp>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>
#include <QEventLoop>

#include "webparse.h"
#include "menue.h"

/**
 * @brief WebParse::WebParse WebParse Constructor
 * @param location Choosen location: Stadtmitte, Lichtwiese,
 *  Schöfferstraße, Haardtring or Dieburg
 * @param parent parent
 */
WebParse::WebParse(int location, QObject *parent) :
    QObject(parent)
{
    setLocation(location);

    //m_qnam = new QNetworkAccessManager(this);
}

/**
 * @brief WebParse::download Starts download of mensa-<location>.html
 *  and waits for it to finish
 * @return parsed results as List of Menues
 */
QList<Menue> WebParse::download()
{
    m_qnam = new QNetworkAccessManager(this);

    if (QDate::currentDate() == m_downloadDate[m_locationNum])
        return m_results[m_locationNum];

    QUrl url("http://www.studentenwerkdarmstadt.de/essen/mensa-" + m_location + ".html");

    QNetworkRequest request(url);
    connect(m_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished()));
    m_reply = m_qnam->get(request);

    QEventLoop loop;
    connect(this, SIGNAL(parsed()), &loop, SLOT(quit()));
    loop.exec();

    //loop.deleteLater();

    m_downloadDate[m_locationNum] = QDate::currentDate();
    return m_results[m_locationNum];
}

/**
 * @brief Called when the result was downloaded
 * @see WebParse::parsePage
 */
void WebParse::replyFinished()
{
    if (m_reply->error() == QNetworkReply::NoError ) {
        QString msg = m_reply->readAll();
        m_results[m_locationNum] = parsePage(msg);
    } else {
        qDebug() << "Network Error" << m_reply->errorString();
        m_results[m_locationNum] = QList<Menue>();
        m_results[m_locationNum].append(Menue(m_reply->errorString(), "", "", ""));
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
    Menue result;
    int pos = 0;

    QRegExp rx("<tr><th></th><th class=\"hl_today\">([\\w,\\s\\." \
               "\\d]+)</th></tr>");
    if (rx.indexIn(html) != -1)
        m_today = rx.cap(1);

    rx.setPattern("<tr><td valign=\"top\">([\\s\\w&;\\.]*)</td><td " \
                  "valign=\"top\"><img class=\"spk_img\" src=\"comp" \
                  "onents/com_spk/images/[\\w]*pict_k.jpg\" alt=\"" \
                  "([\\w]*)\" width=\"50px\" />([\\w&;\\s!\\-\\(" \
                  "\\d\\,\\)]*) [\\w]* ([\\d\\,]{4})");
    rx.setMinimal(true);

    while ((pos = rx.indexIn(html, pos)) != -1) {
        result.setLocation(rx.cap(1).replace("&nbsp;", ""));
        result.setType(rx.cap(2));
        result.setName(replaceHtml(rx.cap(3)));
        result.setPrice(rx.cap(4).append(" €"));

        results.append(result);
        pos += rx.matchedLength();
    }

    rx.setPattern("<br />&nbsp;<br /><table border=\"1\" class=" \
                  "\"spk_table\"><tr><th></th><th class=\"hl_" \
                  "today\">([\\d\\.\\s\\w,]*)</th></tr>");
    if (rx.indexIn(html) != -1)
        m_day = rx.cap(1);

    return results;
}

/**
 * @brief WebParse::replaceHtml replaces html codes for
 *  german umlautsm ß and quotation marks.
 *  Removes "Von unserer Suppenbar!"
 * @param in QString to look for umlauts in
 * @return QString, clean of html
 */
QString WebParse::replaceHtml(QString in)
{
    return in.replace("&uuml;", "ü").replace("&quot;", "\"")
            .replace("&auml;", "ä").replace("&ouml;", "ö")
            .replace("&szlig;", "ß").remove("Von unserer Suppenbar! ");
}

/**
 * @brief Just returns a pointer to the network access manager
 * @return Network Access Manager
 */
QNetworkAccessManager *WebParse::qnam()
{
    return m_qnam;
}

/**
 * @brief WebParse::getDay returns m_day, parsed from html
 * @return m_day
 */
QString WebParse::getDay() const
{
    return m_day;
}

void WebParse::setLocation(int newLocation)
{
    m_locationNum = newLocation;
    switch (newLocation) {
    case 0:
        m_location = "stadtmitte";
        break;
    case 1:
        m_location = "lichtwiese";
        break;
    case 2:
        m_location = "dieburg";
        break;
    case 3:
        m_location = "schofferstrase";
        break;
    case 4:
        m_location = "haardtring";
        break;
    }
}
