#include "rttparser.h"
#include "rttchannel.h"

#include <QDebug>



RTTParser::RTTParser(QObject *parent) : QObject(parent) {

}

RTTParser::~RTTParser() {
   for (QList<RTTChannel* >::iterator it = channelList.begin(); it != channelList.end(); it++) {
        delete *it;
   }
   channelList.clear();
}

bool RTTParser::pairLessThan(const QPair<qint32, qint32> p1, const QPair<qint32, qint32> p2) {
    return p1.first < p2.first;
}

void RTTParser::addChannel(qint32 id, QString format) {
    channelList.append(new RTTChannel(id, format));
}

void RTTParser::removeChannel(qint32 id) {
    for (QList<RTTChannel* >::iterator it = channelList.begin(); it != channelList.end(); it++) {
        if ((*it)->id == id) {
            RTTChannel* ptr = *it;
            channelList.removeOne(ptr);
            delete ptr;
            break;
        }
    }
}

void RTTParser::parseLine(QString line) {
    QStringList channelDataList = line.split("\r\n");
    for (auto s : channelDataList) {
        qDebug() << s;
    }
    QList<QPair<qint32, float> > dataList;
    for (QList<QString>::iterator it = channelDataList.begin(); it != channelDataList.end(); it++) {
        QStringList lineDataList = (*it).split("=");
        for (QList<RTTChannel* >::iterator it = channelList.begin(); it != channelList.end(); it++) {
            if (QString::compare((QString)lineDataList.at(0),(*it)->format, Qt::CaseInsensitive) == 0) {
                dataList.append(QPair<qint32, float>((*it)->id, ((QString)lineDataList.at(1)).toFloat()));
            }
        }
    }
    if (dataList.count() > 0) {
        std::sort(dataList.begin(),dataList.end(), RTTParser::pairLessThan);
        emit lineParsed(dataList);
    }
}

void RTTParser::parseSlot(QString line) {
    parseLine(line);
}
