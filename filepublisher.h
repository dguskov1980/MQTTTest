#ifndef FILEPUBLISHER_H
#define FILEPUBLISHER_H

#include <qmqtt.h>
#include "data.h"
#include "subscriber.h"

using namespace  QMQTT;
class FilePublisher : public QObject
{
    Q_OBJECT
public:
    explicit FilePublisher(const QHostAddress& host = EXAMPLE_HOST,
                       const quint16 port = EXAMPLE_PORT,
                       QObject* parent = nullptr);

    virtual ~FilePublisher() {}

signals:
      void updateData(const int& number);
      void updateSubscriberData(const int& number);

public slots:
    void createConnection(const QString &s_host,const QString &username,const QString &pass,const quint16 port,const QString& willTopic,const QString &filePath);
    void onPublished(const QMQTT::Message& message, quint16 msgid);
    void onConnected();
    void started();
    void onDisconnected();
    void onSubscribed(const QString& topic);
    void deleteData();

private:

    quint16 _number;
    QString _filepath;

    Client *m_client;
    Subscriber* m_subscriber;
    QString _topic;
};

#endif // FILEPUBLISHER_H
