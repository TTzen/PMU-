#include "measure.h"
#include "ui_measure.h"
#include <QThread>
#include <QNetworkDatagram>
#include "PowerQuality.h"
#include "voltageSignal.h"
#include "currentSignal.h"
#include <QMessageBox>

meaSure::meaSure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::meaSure),
    m_runFlag(false)
{
    ui->setupUi(this);

    //A相的电压电流显示窗口
    m_A.UVoltage = ui->UaVoltageEdit;
    m_A.UPhase   = ui->UaPhaseEdit;
    m_A.UFreq    = ui->UaFreqEdit;
    m_A.ICurrent = ui->IaCurrentEdit;
    m_A.IPhase   = ui->IaPhaseEdit;

    //B相的电压电流显示窗口
    m_B.UVoltage = ui->UbVoltageEdit;
    m_B.UPhase   = ui->UbPhaseEdit;
    m_B.UFreq    = ui->UbFreqEdit;
    m_B.ICurrent = ui->IbCurrentEdit;
    m_B.IPhase   = ui->IbPhaseEdit;

    //C相的电压电流显示窗口
    m_C.UVoltage = ui->UcVoltageEdit;
    m_C.UPhase   = ui->UcPhaseEdit;
    m_C.UFreq    = ui->UcFreqEdit;
    m_C.ICurrent = ui->IcCurrentEdit;
    m_C.IPhase   = ui->IcPhaseEdit;

    //点击开始
    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onClickStart()));

    //点击结束
    QObject::connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(onClickStop()));
}

meaSure::~meaSure()
{
    delete ui;
}


void meaSure::getDatagram(QNetworkDatagram Datagram)
{
    processDatagram(Datagram);
}

void meaSure::onClickStart()
{
    //防止重复点击
    if (m_runFlag == true){
        return;
    }

    //切换图标
    ui->startButton->setIcon(QIcon(":/config/image/play_active.png"));
    ui->startButton->setIconSize(QSize(20, 20));

    ui->stopButton->setIcon(QIcon(":/config/image/stop_passive.png"));
    ui->stopButton->setIconSize(QSize(20, 20));

    m_IP = ui->EditSetIP->text();

    //切换标志位
    m_runFlag = true;
}

void meaSure::onClickStop()
{
    //防止重复点击
    if (m_runFlag == false){
        return;
    }

    //切换图标
    ui->startButton->setIcon(QIcon(":/config/image/play_passive.png"));
    ui->startButton->setIconSize(QSize(20, 20));

    ui->stopButton->setIcon(QIcon(":/config/image/stop_active.png"));
    ui->stopButton->setIconSize(QSize(20, 20));

    //切换标志位
    m_runFlag = false;
}

void meaSure::processDatagram(QNetworkDatagram &Datagram)
{
//    if (m_runFlag != true || Datagram.destinationAddress() != QHostAddress(m_IP)){
//        return;
//    }
    //解析电能参数
    PowerQuality PQ = PowerQuality(Datagram.data().data(), Datagram.data().size());
    if (PQ.isValid() != true){
        return;
    }

    ui->GPSInfoEdit->setText(PQ.ToLocalTime("%H-%m-%d %H:%M:%S").data());
    SetAnyPhaseDisplayInfo(m_A, PQ.A_voltageSignal(), PQ.A_currentSignal_ch1());
    SetAnyPhaseDisplayInfo(m_B, PQ.B_voltageSignal(), PQ.B_currentSignal_ch1());
    SetAnyPhaseDisplayInfo(m_C, PQ.C_voltageSignal(), PQ.C_currentSignal_ch1());
}


void meaSure::SetAnyPhaseDisplayInfo(AnyPhaseWindows &AnyPhase, voltageSignal Usignal, currentSignal Isignal)
{
    AnyPhase.UVoltage->setText(QString("%1").arg(Usignal.Voltage()));
    AnyPhase.UPhase->setText(QString("%1").arg(Usignal.phase_angle()));
    AnyPhase.UFreq->setText(QString("%1").arg(Usignal.Freq()));

    AnyPhase.ICurrent->setText(QString("%1").arg(Isignal.Current()));
    AnyPhase.IPhase->setText(QString("%1").arg(Isignal.phase_angle()));
}
