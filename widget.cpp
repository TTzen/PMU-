#include "widget.h"
#include "ui_widget.h"
#include <QTableWidget>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <voltageSignal.h>
#include <currentSignal.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_udpSocket(new QUdpSocket(this))
{
    ui->setupUi(this);
    setFixedSize(size());

    //设置横向比例
    ui->Dev1_Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置纵向比例
    ui->Dev1_Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //向设备1的界面上添加条目
    int rowCount    = ui->Dev1_Table->rowCount();
    int columnCount = ui->Dev1_Table->columnCount();
    for (int i = 0; i < rowCount; ++i){
        for (int j = 0; j < columnCount; ++j){
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setFlags(Qt::NoItemFlags);
            ui->Dev1_Table->setItem(i, j, item);
        }
    }

    initUdpSocket();
    QObject::connect(this, SIGNAL(powerParaFinish(PowerQuality)), this, SLOT(displyPowerPara(PowerQuality)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUdpSocket()
{
    m_udpSocket->bind(QHostAddress(QHostAddress::AnyIPv4), 8766);
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagram()));
}

void Widget::displyPowerPara(PowerQuality PQ)
{
    voltageSignal v = PQ.A_voltageSignal();
    ui->Dev1_Table->item(0, 0)->setText(QString("%1").arg(v.Voltage()));
    ui->Dev1_Table->item(0, 1)->setText(QString("%1").arg(v.phase_angle()));
    ui->Dev1_Table->item(0, 2)->setText(QString("%1").arg(v.Freq()));
}

void Widget::processDatagram()
{
    if (m_udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = m_udpSocket->receiveDatagram();
        PowerQuality PQ = PowerQuality(datagram.data().data(), datagram.data().size());

        if (PQ.isValid()){
            emit powerParaFinish(PQ);
        }
    }
}
