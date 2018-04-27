#include "rttlogger.h"
#include <iostream>
#include <QString>

RTTLogger::RTTLogger() {

}

void RTTLogger::connectSignal(const QObject* sender, const char* signal, const QObject* receiver, const char* method) {
    connect(sender, signal, receiver, method);
}

void RTTLogger::printConnected() {
    std::cout << "Connected to host" << std::endl;
}

void RTTLogger::printError(qint16 error) {
    std::cout << "Error: " << error << std::endl;
}

void RTTLogger::printMessage(QString str) {
    std::cout << "Message: " << str.toStdString() << std::endl;
}

void RTTLogger::printChannel(qint32 id, qint32 value) {
    std::cout << "[" << id << "] " << value << std::endl;
}
