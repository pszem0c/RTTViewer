#include "rttconnector.h"
#include <QTcpSocket>

RTTConnector::RTTConnector(QObject *parent) : QObject(parent) {
    serial = new QSerialPort;
    buffer = new char[4096];

    //    connect(socket, SIGNAL(connected()), this, SLOT(connectedToHostSlot()));
    //    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    //    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedFromHostSlot()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readReadySlot()));

}

RTTConnector::~RTTConnector() {
    delete serial;
    delete[] buffer;
}

void RTTConnector::connectToHost(const QString &name) {
    serial->setPortName(name);
    serial->setBaudRate(115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        emit connectedToHost();
    } else {
        emit socketError("Open error");
    }
}

void RTTConnector::disconnectFromHost() {
    if (serial->isOpen()) {
        serial->close();
        emit disconnectedFromHost();
    }
}

void RTTConnector::connectedToHostSlot() {
    emit connectedToHost();
}

void RTTConnector::disconnectedFromHostSlot() {

}

void RTTConnector::readReadySlot() {
    QString str;
    std::fill(buffer, buffer+ 4096, 0);
    serial->read(buffer, serial->bytesAvailable());
    str = QString(buffer);
    emit lineRead(str);
}
