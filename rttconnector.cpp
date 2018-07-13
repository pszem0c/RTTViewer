#include "rttconnector.h"
#include <QTcpSocket>

RTTConnector::RTTConnector(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket;
    buffer = new char[4096];

        connect(socket, SIGNAL(connected()), this, SLOT(connectedToHostSlot()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedFromHostSlot()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readReadySlot()));

}

RTTConnector::~RTTConnector() {
    delete socket;
    delete[] buffer;
}

void RTTConnector::connectToHost() {
    socket->connectToHost("127.0.0.1", 19021);
    if (!socket->waitForConnected()) {
        qDebug() << "Error: " << socket->errorString();
    }
    if (socket->state() == QTcpSocket::ConnectedState) {


        qDebug() << "socket connected";
    }
}

void RTTConnector::disconnectFromHost() {
    if (socket->state() == QTcpSocket::ConnectedState) {
        socket->disconnectFromHost();
        if(socket->state() != QTcpSocket::UnconnectedState) {
            if(!socket->waitForDisconnected()) {
                qDebug() << "Error: " << socket->errorString();
            }
        }
    }
}

void RTTConnector::connectedToHostSlot() {
    emit connectedToHost();
}

void RTTConnector::errorSlot(QAbstractSocket::SocketError) {
    emit socketError(socket->errorString());
}

void RTTConnector::disconnectedFromHostSlot() {

}

void RTTConnector::readReadySlot() {
    if (socket->canReadLine()) {
        if (socket->bytesAvailable() > 4096) {
            socket->readAll();
        } else {
            QString str;
            std::fill(buffer,buffer+4096,0);
            socket->read(buffer, socket->bytesAvailable());
            str = QString(buffer);
            emit lineRead(str);
        }
    }
}
