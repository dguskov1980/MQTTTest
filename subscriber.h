#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <qmqtt.h>
#include "data.h"
#include <QDebug>

class Subscriber : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit Subscriber(const QHostAddress& host = EXAMPLE_HOST,
                        const quint16 port = EXAMPLE_PORT,
                        QObject* parent = nullptr)
        : QMQTT::Client(host, port, parent)
        , _qout(stdout)
    {
        connect(this, &Subscriber::connected, this, &Subscriber::onConnected);
        connect(this, &Subscriber::error, this, &Subscriber::onError);
        connect(this, &Subscriber::subscribed, this, &Subscriber::onSubscribed);
        connect(this, &Subscriber::received, this, &Subscriber::onReceived);
    }
    virtual ~Subscriber() {}

    QTextStream _qout;
    qint16 _count;

signals:
    void updateData(const int& number);

public slots:
    void onError(const QMQTT::ClientError error)
    {
        qDebug() << "onError " << error;
    }

    void onConnected()
    {
        _count = 0;
        qDebug() << "Subscriber connected";
        subscribe(EXAMPLE_TOPIC, 0);
    }

    void onSubscribed(const QString& topic)
    {
        qDebug() << "subscribed " << topic << endl;
    }

    void onReceived(const QMQTT::Message& message)
    {
        qDebug() << "publish received: " << QString::fromUtf8(message.payload());
        _count++;
        emit updateData(_count);
    }
};

#endif // SUBSCRIBER_H
