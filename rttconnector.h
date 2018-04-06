#ifndef RTTCONNECTOR_H
#define RTTCONNECTOR_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

class RTTConnector : public QObject {
    Q_OBJECT
private:
    QTcpSocket* socket;
    char* buffer;
public:
    explicit RTTConnector(QObject *parent = nullptr);
    ~RTTConnector();

    void connectToHost();
    void disconnectFromHost();

signals:
    void socketError(qint16);
    void connectedToHost();
    void disconnectedFromHost();
    void lineRead(QString);

public slots:

private slots:
    void connectedToHostSlot();
    void errorSlot(QAbstractSocket::SocketError error);
    void disconnectedFromHostSlot();
    void readReadySlot();
};

#endif // RTTCONNECTOR_H
