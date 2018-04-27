#include <QCoreApplication>
#include "rttlogger.h"
#include "rttconnector.h"
#include "rttparser.h"
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    RTTLogger logger;
    RTTConnector rttConnector;
    RTTParser rttParser;
    logger.connectSignal(&rttConnector, SIGNAL(connectedToHost()), &logger, SLOT(printConnected()));
    logger.connectSignal(&rttConnector, SIGNAL(socketError(qint16)), &logger, SLOT(printError(qint16)));
    QObject::connect(&rttConnector, SIGNAL(lineRead(QString)), &rttParser, SLOT(parseSlot(QString)));
    logger.connectSignal(&rttParser, SIGNAL(lineParsed(int,int)), &logger, SLOT(printChannel(qint32,qint32)));

    rttParser.addChannel(0, "BPM");
    rttParser.addChannel(1, "RTOR");
    rttConnector.connectToHost();

    return a.exec();
}
