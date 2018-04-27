#ifndef RTTPARSER_H
#define RTTPARSER_H

#include <QObject>
#include <QList>

class RTTChannel;

class RTTParser : public QObject {
    Q_OBJECT
private:
    QList<RTTChannel*> channelList;

public:
    explicit RTTParser(QObject *parent = nullptr);
    ~RTTParser();

    void addChannel(qint32 id, QString format);
    void parseLine(QString line);

signals:
    void lineParsed(int id, int value);
public slots:
    void parseSlot(QString line);
};

#endif // RTTPARSER_H
