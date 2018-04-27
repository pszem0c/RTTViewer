#include "rttconnector.h"
#include <QTcpSocket>

RTTConnector::RTTConnector(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;
    buffer = new char[100];

    connect(socket, SIGNAL(connected()), this, SLOT(connectedToHostSlot()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedFromHostSlot()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readReadySlot()));
}

RTTConnector::~RTTConnector() {
    disconnectFromHost();
    delete socket;
    delete[] buffer;
}

void RTTConnector::connectToHost() {
    socket->connectToHost("127.0.0.1", 19021);
    if (!socket->waitForConnected()) {
        qDebug() << "Error: " << socket->errorString();
    }
}

void RTTConnector::disconnectFromHost() {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnect();
        if(!socket->waitForDisconnected()) {
            qDebug() << "Error: " << socket->errorString();
        }
    }
}

void RTTConnector::connectedToHostSlot() {
    emit connectedToHost();
}

void RTTConnector::errorSlot(QAbstractSocket::SocketError error) {
    emit socketError((qint16)error);
}

void RTTConnector::disconnectedFromHostSlot() {

}

void RTTConnector::readReadySlot() {
    if (socket->canReadLine()) {
        QString str;
        socket->readLine(buffer, 100);
        str = QString(buffer);
        emit lineRead(str);
    }
}
