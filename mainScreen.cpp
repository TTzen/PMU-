#include "mainScreen.h"
#include "ui_mainScreen.h"
#include "configMenu.h"
#include <QMessageBox>
#include <QDebug>

mainScreen::mainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainScreen),
//    m_meaSure(new meaSure),
    m_configmenu(new configMenu(this)),
    m_udpService(new QUdpSocket(this))
{
    ui->setupUi(this);
    m_udpService->bind(QHostAddress::AnyIPv4, 8766);

    //显示设置框
    QObject::connect(ui->Dev1, SIGNAL(triggered(bool)), m_configmenu, SLOT(show()));
    //处理网络数据
    QObject::connect(m_udpService, SIGNAL(readyRead()), this, SLOT(processDatagram()));
    //数据发送给测量界面
    QObject::connect(this, SIGNAL(DatagramSendToMeaSure(QNetworkDatagram)), ui->WidgetMeasure, SLOT(getDatagram(QNetworkDatagram)));
    //数据发送给同步界面
    QObject::connect(this, SIGNAL(DatagramSendToSync(QNetworkDatagram)), ui->WidgetSync, SLOT(getDatagram(QNetworkDatagram)));
    //切换窗口时自动调整界面
    QObject::connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeWindows(int)));
}

mainScreen::~mainScreen()
{
    delete ui;
}


void mainScreen::processDatagram()
{
    if (m_udpService->hasPendingDatagrams()){
        QNetworkDatagram datagra = m_udpService->receiveDatagram();

        if (ui->tabWidget->currentWidget() == ui->WidgetMeasure){
            emit DatagramSendToMeaSure(datagra);
        } else if(ui->tabWidget->currentWidget() == ui->WidgetSync){
            emit DatagramSendToSync(datagra);
        }
    }
}

void mainScreen::changeWindows(int index)
{
    if (index == 0){
        //当前窗口时1,测量界面时
        resize(753, 561);
    } else if (index == 1){
        //当前窗口时2,同步界面时
        resize(1200, 400);
    }
}
