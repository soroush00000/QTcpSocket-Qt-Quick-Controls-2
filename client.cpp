#include "client.h"
#include <QTcpSocket>
#include <QTextStream>

static inline QByteArray IntToArray(qint32 source);

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QIODevice::readyRead, this, &Client::readFortune);

}

bool Client::connectToHost(QString host)
{
    socket->connectToHost(host, 1024);
    return socket->waitForConnected();
}

void Client::getText(const QString &in)
{
    QByteArray textTemp = in.toUtf8();
    writeData(textTemp);
    qDebug()<<writeData(textTemp);
}

bool Client::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->write(IntToArray(data.size()));
        socket->write(data);
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

void Client::readFortune()
{
    in.startTransaction();
    QString nextFortune;
    in >> nextFortune;
    if(!in.commitTransaction())
        return;
}

QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
