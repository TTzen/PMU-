#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <PowerQuality.h>

class QUdpSocket;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void powerParaFinish(PowerQuality);

public slots:
    void displyPowerPara(PowerQuality PQ);
    void processDatagram();

private:
    void initUdpSocket();


private:
    Ui::Widget* ui;
    QUdpSocket* m_udpSocket;
};

#endif // WIDGET_H
