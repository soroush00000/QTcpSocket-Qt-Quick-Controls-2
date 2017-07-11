#include <QtCore>
#include <QtNetwork>
#include <QTcpSocket>


class QTcpSocket;
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

public slots:
    void getText(const QString& in);
    bool connectToHost(QString host);
    bool writeData(QByteArray data);
    void readFortune();
//    void requestNewFortune();

private:
    QTcpSocket *socket;
    QDataStream in;
    QString currentFortune;
};
