#include "filepublisher.h"
#include "QDebug"

FilePublisher::FilePublisher(const QHostAddress& host,
                             const quint16 port,
                             QObject* parent )
    : _number(0),
      m_client(nullptr),
      m_subscriber(nullptr)
{
}

void FilePublisher::started()
{
    qDebug() << "started";
    m_client = new Client();
    m_subscriber = new Subscriber();
    connect(m_client, &Client::connected, this, &FilePublisher::onConnected);
    connect(m_client, &Client::published, this, &FilePublisher::onPublished);
    connect(m_client, &Client::disconnected, this, &FilePublisher::onDisconnected);
    connect(m_subscriber, &Subscriber::updateData, this, &FilePublisher::updateSubscriberData);
  //  connect(m_client, &Client::subscribed, this, &FilePublisher::onSubscribed);

}
void FilePublisher::deleteData()
{
    qDebug() << "FilePublisher::deleteData";
    m_client->disconnectFromHost();
    m_subscriber->disconnectFromHost();
    delete m_client;
    delete m_subscriber;
}

void FilePublisher::createConnection(const QString &s_host,const QString &username,const QString &pass,const quint16 port, const QString& willTopic, const QString &filePath)
{
    if (m_client->isConnectedToHost())
    {
        qDebug() << "here";
        m_client->disconnectFromHost();
    }else
    {
        qDebug()<< "createConnection: " << s_host << ": " << filePath;
        _topic = willTopic;
        _filepath = filePath;
        m_subscriber->setUsername(username);
        m_subscriber->setPassword(pass.toUtf8());
        m_subscriber->setPort(port);
        m_subscriber->setHost(QHostAddress(s_host));
        m_subscriber->connectToHost();
        m_client->setUsername(username);
        m_client->setPassword(pass.toUtf8());
        m_client->setPort(port);
        m_client->setHost(QHostAddress(s_host));
    //    m_client->setWillTopic(_topic);
    //    m_client->setWillRetain(true);
    //    m_client->setWillQos(1);
        m_client->connectToHost();
    }
}

void FilePublisher::onSubscribed(const QString& topic)
{
    qDebug() << "subscribed " << topic << endl;
}

void FilePublisher::onDisconnected()
{
   qDebug() << "onDisconnected";
   _number = 0;
}
void FilePublisher::onPublished(const QMQTT::Message& message, quint16 msgid)
{
    qDebug() <<   "onPublished "  << msgid;
}

void FilePublisher::onConnected()
{
    qDebug() << "onConnected";
    QFile file( _filepath);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         qDebug() << "Не удалось открыть файл для чтения";
         return;
     }

     QTextStream in(&file);
     while (!in.atEnd()) {
         QString line = in.readLine();
         qDebug() << line;
         QMQTT::Message message(_number, _topic, line.toUtf8());
         _number++;
         m_client->publish(message);
     }
     emit updateData(_number);
     _number = 0;
     file.close();
}


