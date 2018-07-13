#ifndef RTTCONNECTOR_H
#define RTTCONNECTOR_H

#include <QObject>
#include <QSerialPort>

class RTTConnector : public QObject {
    Q_OBJECT
private:
    QSerialPort* serial;
    char* buffer;
public:
    explicit RTTConnector(QObject *parent = nullptr);
    ~RTTConnector();

    void connectToHost(const QString& name);
    void disconnectFromHost();

signals:
    void socketError(QString);
    void connectedToHost();
    void disconnectedFromHost();
    void lineRead(QString);

public slots:

private slots:
    void connectedToHostSlot();
    void disconnectedFromHostSlot();
    void readReadySlot();
};

#endif // RTTCONNECTOR_H
