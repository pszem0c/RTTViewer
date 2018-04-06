#ifndef RTTLOGGER_H
#define RTTLOGGER_H

#include <QObject>
#include <QString>

class RTTLogger : public QObject{
    Q_OBJECT
public:
    RTTLogger();

    void connectSignal(const QObject* sender, const char* signal, const QObject* receiver, const char* method);

public slots:
    void printConnected();
    void printError(qint16 error);
    void printMessage(QString str);

};

#endif // RTTLOGGER_H
