#include "measure.h"
#include "ui_measure.h"
#include <QThread>
#include <QNetworkDatagram>
#include "PowerQuality.h"
#include "voltageSignal.h"
#include "currentSignal.h"
#include <QMessageBox>
#include <QMutex>
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
    m_A.ICurrent_ch1 = ui->IaCurrentEdit_CH1;
    m_A.IPhase_ch1   = ui->IaPhaseEdit_CH1;
    m_A.ICurrent_ch2 = ui->IaCurrentEdit_CH2;
    m_A.IPhase_ch2   = ui->IaPhaseEdit_CH2;

    //B相的电压电流显示窗口
    m_B.UVoltage = ui->UbVoltageEdit;
    m_B.UPhase   = ui->UbPhaseEdit;
    m_B.UFreq    = ui->UbFreqEdit;
    m_B.ICurrent_ch1 = ui->IbCurrentEdit_CH1;
    m_B.IPhase_ch1   = ui->IbPhaseEdit_CH1;
    m_B.ICurrent_ch2 = ui->IbCurrentEdit_CH2;
    m_B.IPhase_ch2   = ui->IbPhaseEdit_CH2;

    //C相的电压电流显示窗口
    m_C.UVoltage = ui->UcVoltageEdit;
    m_C.UPhase   = ui->UcPhaseEdit;
    m_C.UFreq    = ui->UcFreqEdit;
    m_C.ICurrent_ch1 = ui->IcCurrentEdit_CH1;
    m_C.IPhase_ch1   = ui->IcPhaseEdit_CH1;
    m_C.ICurrent_ch2 = ui->IcCurrentEdit_CH2;
    m_C.IPhase_ch2   = ui->IcPhaseEdit_CH2;

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
    m_mutex.lock();
    processDatagram(Datagram);
    m_mutex.unlock();
}

void meaSure::onClickStart()
{
    //防止重复点击
    if (m_runFlag == true){
        return;
    }
    m_IP = ui->EditSetIP->text();

    if (QHostAddress().setAddress(m_IP) != true){
        QMessageBox::warning(this, "worning", "请输入正确的设备IP");
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
    if (m_runFlag != true || Datagram.senderAddress() != QHostAddress(m_IP)){
        return;
    }
    //解析电能参数
    PowerQuality PQ = PowerQuality(Datagram.data().data(), Datagram.data().size());
    if (PQ.isValid() != true){
        return;
    }

    ui->GPSInfoEdit->setText(PQ.ToLocalTime("%Y-%m-%d %H:%M:%S").data());
    SetAnyPhaseDisplayInfo(m_A, PQ.A_voltageSignal(), PQ.A_currentSignal_ch1(), PQ.A_currentSignal_ch2());
    SetAnyPhaseDisplayInfo(m_B, PQ.B_voltageSignal(), PQ.B_currentSignal_ch1(), PQ.B_currentSignal_ch2());
    SetAnyPhaseDisplayInfo(m_C, PQ.C_voltageSignal(), PQ.C_currentSignal_ch1(), PQ.C_currentSignal_ch2());
    ui->SourceDataEdit->setText(Datagram.data().toHex());
}


void meaSure::SetAnyPhaseDisplayInfo(AnyPhaseWindows &AnyPhase, voltageSignal Usignal, currentSignal Isignal_CH1, currentSignal Isignal_CH2)
{
    AnyPhase.UVoltage->setText(QString("%1").arg(Usignal.Voltage()));
    AnyPhase.UPhase->setText(QString("%1").arg(Usignal.phase_angle()));
    AnyPhase.UFreq->setText(QString("%1").arg(Usignal.Freq()));

    AnyPhase.ICurrent_ch1->setText(QString("%1").arg(Isignal_CH1.Current()));
    AnyPhase.IPhase_ch1->setText(QString("%1").arg(Isignal_CH1.phase_angle()));

    AnyPhase.ICurrent_ch2->setText(QString("%1").arg(Isignal_CH2.Current()));
    AnyPhase.IPhase_ch2->setText(QString("%1").arg(Isignal_CH2.phase_angle()));
}
