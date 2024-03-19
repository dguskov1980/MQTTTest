#include <QHostInfo>
#include <QThread>
#include "publisher_thread.h"

PublisherThread::PublisherThread()
{


}

PublisherThread::~PublisherThread()
{
    qDebug() << "~PublisherThread";
     workerThread->quit();
     workerThread->wait();

}

void PublisherThread::init()
{
    workerThread = new QThread();
    m_client.moveToThread(workerThread);
    connect(this, &PublisherThread::startTransfer, &m_client, &FilePublisher::createConnection, Qt::QueuedConnection);
    connect(workerThread, &QThread::started, &m_client, &FilePublisher::started);
    connect(workerThread, &QThread::finished, &m_client, &FilePublisher::deleteData);

    connect(&m_client, &FilePublisher::updateData,this, &PublisherThread::updateDataSlot);
    connect(&m_client, &FilePublisher::updateSubscriberData,this, &PublisherThread::updateSubscriberDataSlot);

    workerThread->start();
}

void PublisherThread::doWork(const QString &s_host,const QString &username,const QString &pass,const quint16 port,const QString& willTopic, const QString &filePath)
{
    _filePath = filePath;
    _username = username;
    _password = pass;
    _port = port;
    _willTopic = willTopic;
    QString* ipAddress = &_ipAddress;
    QHostInfo::lookupHost(s_host, [ipAddress,this](const QHostInfo &host){
       if (!host.addresses().isEmpty()) {
           qDebug() << "IP-adress:" << host.addresses().first();
             *ipAddress = host.addresses().first().toString();
           emit this->startTransfer(*ipAddress, this->_username, this->_password,this->_port, this->_willTopic, this->_filePath);

       } else {
           qDebug() << "cannot get Ip address";
       }
    });
}

void PublisherThread::updateDataSlot(const int& number)
{
    qDebug() << "updateDataSlot " << number;
    emit setData( tr(" Count lines transfer: %1").arg(number));
}

void PublisherThread::updateSubscriberDataSlot(const int& number)
{
    qDebug() << "updateSubscriberDataSlot " << number;
    emit setSubsciberData( tr(" Publish msg received: %1").arg(number));
}

