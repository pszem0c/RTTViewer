#ifndef RTTCONECTOR_H
#define RTTCONECTOR_H

#include <QObject>

class RTTConector : public QObject
{
    Q_OBJECT
public:
    explicit RTTConector(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RTTCONECTOR_H