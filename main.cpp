#include <QCoreApplication>
#include "rttlogger.h"
#include "rttconnector.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    RTTLogger logger;
    RTTConnector rttConnector;

    logger.connectSignal(&rttConnector, SIGNAL(connectedToHost()), &logger, SLOT(printConnected()));
    logger.connectSignal(&rttConnector, SIGNAL(socketError(qint16)), &logger, SLOT(printError(qint16)));
    logger.connectSignal(&rttConnector, SIGNAL(lineRead(QString)), &logger, SLOT(printMessage(QString)));

    rttConnector.connectToHost();

    return a.exec();
}
