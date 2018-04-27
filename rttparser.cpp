#include "rttparser.h"
#include "rttchannel.h"

RTTParser::RTTParser(QObject *parent) : QObject(parent) {

}

RTTParser::~RTTParser() {
   for (QList<RTTChannel* >::iterator it = channelList.begin(); it != channelList.end(); it++) {
        delete *it;
   }
}

void RTTParser::addChannel(qint32 id, QString format) {
    channelList.append(new RTTChannel(id, format));
}

void RTTParser::parseLine(QString line) {
    QStringList lineDataList = line.split("=");
    for (QList<RTTChannel* >::iterator it = channelList.begin(); it != channelList.end(); it++) {
        if (((QString)lineDataList.at(0)).contains((*it)->format)) {
            emit lineParsed((*it)->id, ((QString)lineDataList.at(1)).toInt());
        }
    }
}

void RTTParser::parseSlot(QString line) {
    parseLine(line);
}
