#ifndef RTTCHANNEL_H
#define RTTCHANNEL_H

#endif // RTTCHANNEL_H
#include <QString>

struct RTTChannel {
    qint32 id;
    QString format;
    RTTChannel(qint32 _id, QString _format) {
        id = _id;
        format = _format;
    }
};
