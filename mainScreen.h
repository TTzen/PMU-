#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include "configMenu.h"
#include "measure.h"
#include <QUdpSocket>

namespace Ui {
class mainScreen;
}

class mainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainScreen(QWidget *parent = 0);
    ~mainScreen();

signals:
    void DatagramSendToMeaSure(QNetworkDatagram);
    void DatagramSendToSync(QNetworkDatagram);

public slots:
    void processDatagram();
    void changeWindows(int);//切换窗口

private:
    Ui::mainScreen* ui;

    configMenu*     m_configmenu;
    QUdpSocket*     m_udpService;
};

#endif // MAINSCREEN_H
