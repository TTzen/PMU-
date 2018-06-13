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
            ui->WidgetMeasure->getDatagram(datagra);
        }
    }
}
