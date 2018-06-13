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

public slots:
    void processDatagram();

private:
    Ui::mainScreen* ui;

    meaSure*        m_meaSure;      //测量窗口
    configMenu*     m_configmenu;
    QUdpSocket*     m_udpService;
};

#endif // MAINSCREEN_H
