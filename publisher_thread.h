#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <qmqtt.h>
#include "filepublisher.h"
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

using namespace QMQTT;

class PublisherThread : public QObject
{
    Q_OBJECT
public:
    explicit PublisherThread();
    ~PublisherThread();

    Q_INVOKABLE void doWork(const QString &host,const QString &_username,const QString &_pass,const quint16 port, const QString& willTopic, const QString &filePath);

signals:
    void startTransfer(const QString &_host,const QString &_username,const QString &_pass,const quint16 port,const QString& willTopic,const QString &filePath);
    void connectToBroker();
    void setData(const QString& data);
    void setSubsciberData(const QString& data);

public slots:
    void init();
    void updateDataSlot(const int& number);
    void updateSubscriberDataSlot(const int& number);

private:

    QString _ipAddress;
    QString _filePath;
    QString _username;
    QString _password;
    quint16 _port;
    QString _willTopic;
    FilePublisher m_client;

    QThread *workerThread;

};

#endif // PUBLISHER_H
