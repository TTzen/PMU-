#include "sync.h"
#include "ui_sync.h"
#include <QHostAddress>
#include <QMessageBox>
#include "PowerQuality.h"
#include "voltageSignal.h"
#include "currentSignal.h"
#include "QTime"

Sync::Sync(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sync),
    m_runFlag(false)
{
    ui->setupUi(this);

    /////设备一的信息
    ///设备一的A相信息
    m_A_Dev1.UVoltageWindow    = ui->Dev1UaVolatageEdit;
    m_A_Dev1.UVoltageMaxWindow = ui->Dev1UaVolatageMaxEdit;
    m_A_Dev1.UVoltageMinWindow = ui->Dev1UaVolatageMinEdit;

    m_A_Dev1.UPhaseWindow    = ui->Dev1UaPhaseEdit;
    m_A_Dev1.UPhaseMaxWindow = ui->Dev1UaPhaseMaxEdit;
    m_A_Dev1.UPhaseMinWindow = ui->Dev1UaPhaseMinEdit;

    m_A_Dev1.UFreqWindow    = ui->Dev1UaFreqEdit;
    m_A_Dev1.UFreqMaxWindow = ui->Dev1UaFreqMaxEdit;
    m_A_Dev1.UFreqMinWindow = ui->Dev1UaFreqMinEdit;


    m_A_Dev1.ICurrent_ch1Window    = ui->Dev1IaCurrentEdit;
    m_A_Dev1.ICurrent_ch1MaxWindow = ui->Dev1IaCurrentMaxEdit;
    m_A_Dev1.ICurrent_ch1MinWindow = ui->Dev1IaCurrentMinEdit;

    m_A_Dev1.IPhase_ch1Window    = ui->Dev1IaPaseEdit;
    m_A_Dev1.IPhase_ch1MaxWindow = ui->Dev1IaPaseMaxEdit;
    m_A_Dev1.IPhase_ch1MinWindow = ui->Dev1IaPaseMinEdit;

    m_A_Dev1.ICurrent_ch2Window     = ui->Dev1IaCurrentEdit_CH2;
    m_A_Dev1.ICurrent_ch2MaxWindow  = ui->Dev1IaCurrentMaxEdit_CH2;
    m_A_Dev1.ICurrent_ch2MinWindow  = ui->Dev1IaCurrentMinEdit_CH2;

    m_A_Dev1.IPhase_ch2Window    = ui->Dev1IaPhaseEdit_CH2;
    m_A_Dev1.IPhase_ch2MaxWindow = ui->Dev1IaPhaseMaxEdit_CH2;
    m_A_Dev1.IPhase_ch2MinWindow = ui->Dev1IaPhaseMinEdit_CH2;

    ///设备一的B相信息
    m_B_Dev1.UVoltageWindow    = ui->Dev1UbVolatageEdit;
    m_B_Dev1.UVoltageMaxWindow = ui->Dev1UbVolatageMaxEdit;
    m_B_Dev1.UVoltageMinWindow = ui->Dev1UbVolatageMinEdit;

    m_B_Dev1.UPhaseWindow    = ui->Dev1UbPhaseEdit;
    m_B_Dev1.UPhaseMaxWindow = ui->Dev1UbPhaseMaxEdit;
    m_B_Dev1.UPhaseMinWindow = ui->Dev1UbPhaseMinEdit;

    m_B_Dev1.UFreqWindow    = ui->Dev1UbFreqEdit;
    m_B_Dev1.UFreqMaxWindow = ui->Dev1UbFreqMaxEdit;
    m_B_Dev1.UFreqMinWindow = ui->Dev1UbFreqMinEdit;


    m_B_Dev1.ICurrent_ch1Window    = ui->Dev1IbCurrentEdit;
    m_B_Dev1.ICurrent_ch1MaxWindow = ui->Dev1IbCurrentMaxEdit;
    m_B_Dev1.ICurrent_ch1MinWindow = ui->Dev1IbCurrentMinEdit;

    m_B_Dev1.IPhase_ch1Window    = ui->Dev1IbPaseEdit;
    m_B_Dev1.IPhase_ch1MaxWindow = ui->Dev1IbPaseMaxEdit;
    m_B_Dev1.IPhase_ch1MinWindow = ui->Dev1IbPaseMinEdit;

    m_B_Dev1.ICurrent_ch2Window     = ui->Dev1IbCurrentEdit_CH2;
    m_B_Dev1.ICurrent_ch2MaxWindow  = ui->Dev1IbCurrentMaxEdit_CH2;
    m_B_Dev1.ICurrent_ch2MinWindow  = ui->Dev1IbCurrentMinEdit_CH2;

    m_B_Dev1.IPhase_ch2Window    = ui->Dev1IbPhaseEdit_CH2;
    m_B_Dev1.IPhase_ch2MaxWindow = ui->Dev1IbPhaseMaxEdit_CH2;
    m_B_Dev1.IPhase_ch2MinWindow = ui->Dev1IbPhaseMinEdit_CH2;

    ///设备一的C相信息
    m_C_Dev1.UVoltageWindow    = ui->Dev1UcVolatageEdit;
    m_C_Dev1.UVoltageMaxWindow = ui->Dev1UcVolatageMaxEdit;
    m_C_Dev1.UVoltageMinWindow = ui->Dev1UcVolatageMinEdit;

    m_C_Dev1.UPhaseWindow    = ui->Dev1UcPhaseEdit;
    m_C_Dev1.UPhaseMaxWindow = ui->Dev1UcPhaseMaxEdit;
    m_C_Dev1.UPhaseMinWindow = ui->Dev1UcPhaseMinEdit;

    m_C_Dev1.UFreqWindow    = ui->Dev1UcFreqEdit;
    m_C_Dev1.UFreqMaxWindow = ui->Dev1UcFreqMaxEdit;
    m_C_Dev1.UFreqMinWindow = ui->Dev1UcFreqMinEdit;


    m_C_Dev1.ICurrent_ch1Window    = ui->Dev1IcCurrentEdit;
    m_C_Dev1.ICurrent_ch1MaxWindow = ui->Dev1IcCurrentMaxEdit;
    m_C_Dev1.ICurrent_ch1MinWindow = ui->Dev1IcCurrentMinEdit;

    m_C_Dev1.IPhase_ch1Window    = ui->Dev1IcPaseEdit;
    m_C_Dev1.IPhase_ch1MaxWindow = ui->Dev1IcPaseMaxEdit;
    m_C_Dev1.IPhase_ch1MinWindow = ui->Dev1IcPaseMinEdit;

    m_C_Dev1.ICurrent_ch2Window     = ui->Dev1IcCurrentEdit_CH2;
    m_C_Dev1.ICurrent_ch2MaxWindow  = ui->Dev1IcCurrentMaxEdit_CH2;
    m_C_Dev1.ICurrent_ch2MinWindow  = ui->Dev1IcCurrentMinEdit_CH2;

    m_C_Dev1.IPhase_ch2Window    = ui->Dev1IcPhaseEdit_CH2;
    m_C_Dev1.IPhase_ch2MaxWindow = ui->Dev1IcPhaseMaxEdit_CH2;
    m_C_Dev1.IPhase_ch2MinWindow = ui->Dev1IcPhaseMinEdit_CH2;

    /////设备二的信息
    ///设备二的A相信息
    m_A_Dev2.UVoltageWindow    = ui->Dev2UaVolatageEdit;
    m_A_Dev2.UVoltageMaxWindow = ui->Dev2UaVolatageMaxEdit;
    m_A_Dev2.UVoltageMinWindow = ui->Dev2UaVolatageMinEdit;

    m_A_Dev2.UPhaseWindow    = ui->Dev2UaPhaseEdit;
    m_A_Dev2.UPhaseMaxWindow = ui->Dev2UaPhaseMaxEdit;
    m_A_Dev2.UPhaseMinWindow = ui->Dev2UaPhaseMinEdit;

    m_A_Dev2.UFreqWindow    = ui->Dev2UaFreqEdit;
    m_A_Dev2.UFreqMaxWindow = ui->Dev2UaFreqMaxEdit;
    m_A_Dev2.UFreqMinWindow = ui->Dev2UaFreqMinEdit;


    m_A_Dev2.ICurrent_ch1Window    = ui->Dev2IaCurrentEdit;
    m_A_Dev2.ICurrent_ch1MaxWindow = ui->Dev2IaCurrentMaxEdit;
    m_A_Dev2.ICurrent_ch1MinWindow = ui->Dev2IaCurrentMinEdit;

    m_A_Dev2.IPhase_ch1Window    = ui->Dev2IaPaseEdit;
    m_A_Dev2.IPhase_ch1MaxWindow = ui->Dev2IaPaseMaxEdit;
    m_A_Dev2.IPhase_ch1MinWindow = ui->Dev2IaPaseMinEdit;

    m_A_Dev2.ICurrent_ch2Window     = ui->Dev2IaCurrentEdit_CH2;
    m_A_Dev2.ICurrent_ch2MaxWindow  = ui->Dev2IaCurrentMaxEdit_CH2;
    m_A_Dev2.ICurrent_ch2MinWindow  = ui->Dev2IaCurrentMinEdit_CH2;

    m_A_Dev2.IPhase_ch2Window    = ui->Dev2IaPhaseEdit_CH2;
    m_A_Dev2.IPhase_ch2MaxWindow = ui->Dev2IaPhaseMaxEdit_CH2;
    m_A_Dev2.IPhase_ch2MinWindow = ui->Dev2IaPhaseMinEdit_CH2;

    ///设备二的B相信息
    m_B_Dev2.UVoltageWindow    = ui->Dev2UbVolatageEdit;
    m_B_Dev2.UVoltageMaxWindow = ui->Dev2UbVolatageMaxEdit;
    m_B_Dev2.UVoltageMinWindow = ui->Dev2UbVolatageMinEdit;

    m_B_Dev2.UPhaseWindow    = ui->Dev2UbPhaseEdit;
    m_B_Dev2.UPhaseMaxWindow = ui->Dev2UbPhaseMaxEdit;
    m_B_Dev2.UPhaseMinWindow = ui->Dev2UbPhaseMinEdit;

    m_B_Dev2.UFreqWindow    = ui->Dev2UbFreqEdit;
    m_B_Dev2.UFreqMaxWindow = ui->Dev2UbFreqMaxEdit;
    m_B_Dev2.UFreqMinWindow = ui->Dev2UbFreqMinEdit;


    m_B_Dev2.ICurrent_ch1Window    = ui->Dev2IbCurrentEdit;
    m_B_Dev2.ICurrent_ch1MaxWindow = ui->Dev2IbCurrentMaxEdit;
    m_B_Dev2.ICurrent_ch1MinWindow = ui->Dev2IbCurrentMinEdit;

    m_B_Dev2.IPhase_ch1Window    = ui->Dev2IbPaseEdit;
    m_B_Dev2.IPhase_ch1MaxWindow = ui->Dev2IbPaseMaxEdit;
    m_B_Dev2.IPhase_ch1MinWindow = ui->Dev2IbPaseMinEdit;

    m_B_Dev2.ICurrent_ch2Window     = ui->Dev2IbCurrentEdit_CH2;
    m_B_Dev2.ICurrent_ch2MaxWindow  = ui->Dev2IbCurrentMaxEdit_CH2;
    m_B_Dev2.ICurrent_ch2MinWindow  = ui->Dev2IbCurrentMinEdit_CH2;

    m_B_Dev2.IPhase_ch2Window    = ui->Dev2IbPhaseEdit_CH2;
    m_B_Dev2.IPhase_ch2MaxWindow = ui->Dev2IbPhaseMaxEdit_CH2;
    m_B_Dev2.IPhase_ch2MinWindow = ui->Dev2IbPhaseMinEdit_CH2;

    ///设备二的C相信息
    m_C_Dev2.UVoltageWindow    = ui->Dev2UcVolatageEdit;
    m_C_Dev2.UVoltageMaxWindow = ui->Dev2UcVolatageMaxEdit;
    m_C_Dev2.UVoltageMinWindow = ui->Dev2UcVolatageMinEdit;

    m_C_Dev2.UPhaseWindow    = ui->Dev2UcPhaseEdit;
    m_C_Dev2.UPhaseMaxWindow = ui->Dev2UcPhaseMaxEdit;
    m_C_Dev2.UPhaseMinWindow = ui->Dev2UcPhaseMinEdit;

    m_C_Dev2.UFreqWindow    = ui->Dev2UcFreqEdit;
    m_C_Dev2.UFreqMaxWindow = ui->Dev2UcFreqMaxEdit;
    m_C_Dev2.UFreqMinWindow = ui->Dev2UcFreqMinEdit;


    m_C_Dev2.ICurrent_ch1Window    = ui->Dev2IcCurrentEdit;
    m_C_Dev2.ICurrent_ch1MaxWindow = ui->Dev2IcCurrentMaxEdit;
    m_C_Dev2.ICurrent_ch1MinWindow = ui->Dev2IcCurrentMinEdit;

    m_C_Dev2.IPhase_ch1Window    = ui->Dev2IcPaseEdit;
    m_C_Dev2.IPhase_ch1MaxWindow = ui->Dev2IcPaseMaxEdit;
    m_C_Dev2.IPhase_ch1MinWindow = ui->Dev2IcPaseMinEdit;

    m_C_Dev2.ICurrent_ch2Window     = ui->Dev2IcCurrentEdit_CH2;
    m_C_Dev2.ICurrent_ch2MaxWindow  = ui->Dev2IcCurrentMaxEdit_CH2;
    m_C_Dev2.ICurrent_ch2MinWindow  = ui->Dev2IcCurrentMinEdit_CH2;

    m_C_Dev2.IPhase_ch2Window    = ui->Dev2IcPhaseEdit_CH2;
    m_C_Dev2.IPhase_ch2MaxWindow = ui->Dev2IcPhaseMaxEdit_CH2;
    m_C_Dev2.IPhase_ch2MinWindow = ui->Dev2IcPhaseMinEdit_CH2;

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onStartButtonClick()));
}

Sync::~Sync()
{
    delete ui;
}


void Sync::onStartButtonClick()
{
    if (m_runFlag == false){
        //当前处于关闭状态,点击开启
        m_dev1IP = ui->Dev1IPEdit->text();
        m_dev2IP = ui->Dev2IPEdit->text();
        if (m_dev1IP == m_dev2IP){
            QMessageBox::warning(this, "warning", "地址重复");
            return;
        }
        if ((QHostAddress().setAddress(m_dev1IP) != true)
                || (QHostAddress().setAddress(m_dev2IP) != true)){
            QMessageBox::warning(this, "warning", "请输入正确的IP地址");
            return;
        }
        //切换图标
        ui->pushButton->setIcon(QIcon(":/config/image/Sync_start.png"));
        ui->pushButton->setIconSize(QSize(20, 20));
    } else if (m_runFlag == true){
        //当前属于开启状态点击关闭

        //切换图标
        ui->pushButton->setIcon(QIcon(":/config/image/Sync_stop.png"));
        ui->pushButton->setIconSize(QSize(20, 20));
    }

    m_runFlag = !m_runFlag;
}

void Sync::getDatagram(QNetworkDatagram Datagram)
{
    qDebug() << QTime::currentTime() << "begin";
    m_mutex.lock();
    processDatagram(Datagram);
    m_mutex.unlock();
    qDebug() << QTime::currentTime() << "end";
}


void Sync::processDatagram(QNetworkDatagram &Datagram)
{
    if (m_runFlag != true
            || (Datagram.senderAddress() != QHostAddress(m_dev1IP)
            && Datagram.senderAddress() != QHostAddress(m_dev2IP))){
        return;
    }

    //解析电能参数
    PowerQuality PQ = PowerQuality(Datagram.data().data(), Datagram.data().size());
    if (PQ.isValid() != true){
        return;
    }

    if (Datagram.senderAddress() == QHostAddress(m_dev1IP)){
        //显示到第一个IP地址上
        SetAnyPhaseDisplayInfo(m_A_Dev1, PQ.A_voltageSignal(), PQ.A_currentSignal_ch1(), PQ.A_currentSignal_ch2());
        SetAnyPhaseDisplayInfo(m_B_Dev1, PQ.B_voltageSignal(), PQ.B_currentSignal_ch1(), PQ.B_currentSignal_ch2());
        SetAnyPhaseDisplayInfo(m_C_Dev1, PQ.C_voltageSignal(), PQ.C_currentSignal_ch1(), PQ.C_currentSignal_ch2());
    }  if(Datagram.senderAddress() == QHostAddress(m_dev2IP)){
        //显示到第二个IP地址上
        SetAnyPhaseDisplayInfo(m_A_Dev2, PQ.A_voltageSignal(), PQ.A_currentSignal_ch1(), PQ.A_currentSignal_ch2());
        SetAnyPhaseDisplayInfo(m_B_Dev2, PQ.B_voltageSignal(), PQ.B_currentSignal_ch1(), PQ.B_currentSignal_ch2());
        SetAnyPhaseDisplayInfo(m_C_Dev2, PQ.C_voltageSignal(), PQ.C_currentSignal_ch1(), PQ.C_currentSignal_ch2());
    }
}


void Sync::SetAnyPhaseDisplayInfo(AnyPhaseInfo &AnyPhase
                                  , voltageSignal Usignal
                                  , currentSignal Isignal_CH1
                                  , currentSignal Isignal_CH2)
{
    //求电压的最大值和最小值
    if (AnyPhase.UvolatageMax < Usignal.Voltage()){
        AnyPhase.UvolatageMax = Usignal.Voltage();
    }
    if (AnyPhase.UvolatageMin > Usignal.Voltage()){
        AnyPhase.UvolatageMin = Usignal.Voltage();
    }

    //求相位的最大值和最小值
    if (AnyPhase.UPhaseMax < Usignal.phase_angle()){
        AnyPhase.UPhaseMax = Usignal.phase_angle();
    }
    if (AnyPhase.UPhaseMin > Usignal.phase_angle()){
        AnyPhase.UPhaseMin = Usignal.phase_angle();//角度值
    }

    //求频率的最大值和最小值
    if (AnyPhase.UFreqMax < Usignal.Freq()){
        AnyPhase.UFreqMax = Usignal.Freq();
    }
    if (AnyPhase.UFreqMin > Usignal.Freq()){
        AnyPhase.UFreqMin = Usignal.Freq();
    }

    //求第一通道电流幅值的最大值和最小值
    if  (AnyPhase.ICurrentMax_ch1 < Isignal_CH1.Current()){
        AnyPhase.ICurrentMax_ch1 = Isignal_CH1.Current();
    }
    if (AnyPhase.ICurrentMin_ch1 < Isignal_CH1.Current()){
       AnyPhase.ICurrentMin_ch1 = Isignal_CH1.Current();
    }

    //求第一通道的电流相位的最大值和最小值
    if (AnyPhase.IPhaseMax_ch1 < Isignal_CH1.phase_angle()){
        AnyPhase.IPhaseMax_ch1 = Isignal_CH1.phase_angle();
    }
    if (AnyPhase.IPhaseMin_ch1 < Isignal_CH1.phase_angle()){
        AnyPhase.IPhaseMin_ch1 = Isignal_CH1.phase_angle();
    }

    //求第二通道电流幅值的最大值和最小值
    if  (AnyPhase.ICurrentMax_ch2 < Isignal_CH2.Current()){
        AnyPhase.ICurrentMax_ch2 = Isignal_CH2.Current();
    }
    if (AnyPhase.ICurrentMin_ch2 < Isignal_CH2.Current()){
       AnyPhase.ICurrentMin_ch2 = Isignal_CH2.Current();
    }

    //求第二通道的电流相位的最大值和最小值
    if (AnyPhase.IPhaseMax_ch2 < Isignal_CH2.phase_angle()){
        AnyPhase.IPhaseMax_ch2 = Isignal_CH2.phase_angle();
    }
    if (AnyPhase.IPhaseMin_ch2 < Isignal_CH2.phase_angle()){
        AnyPhase.IPhaseMin_ch2 = Isignal_CH2.phase_angle();
    }

    //电压幅值显示
    AnyPhase.UVoltageWindow->setText(QString("%1").arg(Usignal.Voltage()));
    AnyPhase.UVoltageMaxWindow->setText(QString("%1").arg(AnyPhase.UvolatageMax));
    AnyPhase.UVoltageMinWindow->setText(QString("%1").arg(AnyPhase.UvolatageMin));
    //电压相位显示
    AnyPhase.UPhaseWindow->setText(QString("%1").arg(Usignal.phase_angle()));
    AnyPhase.UPhaseMaxWindow->setText(QString("%1").arg(AnyPhase.UPhaseMax));
    AnyPhase.UPhaseMinWindow->setText(QString("%1").arg(AnyPhase.UPhaseMin));
    //电压频率显示
    AnyPhase.UFreqWindow->setText(QString("%1").arg(Usignal.Freq()));
    AnyPhase.UFreqMaxWindow->setText(QString("%1").arg(AnyPhase.UFreqMax));
    AnyPhase.UFreqMinWindow->setText(QString("%1").arg(AnyPhase.UFreqMin));

    //电压幅值显示CH1
    AnyPhase.ICurrent_ch1Window->setText(QString("%1").arg(Isignal_CH1.Current()));
    AnyPhase.ICurrent_ch1MaxWindow->setText(QString("%1").arg(AnyPhase.ICurrentMax_ch1));
    AnyPhase.ICurrent_ch1MinWindow->setText(QString("%1").arg(AnyPhase.ICurrentMin_ch1));

    //电压相位显示CH1
    AnyPhase.IPhase_ch1Window->setText(QString("%1").arg(Isignal_CH1.phase_angle()));
    AnyPhase.IPhase_ch1MaxWindow->setText(QString("%1").arg(AnyPhase.IPhaseMax_ch1));
    AnyPhase.IPhase_ch1MinWindow->setText(QString("%1").arg(AnyPhase.IPhaseMin_ch1));

    AnyPhase.ICurrent_ch2Window->setText(QString("%1").arg(Isignal_CH2.Current()));
    AnyPhase.ICurrent_ch2MaxWindow->setText(QString("%1").arg(AnyPhase.ICurrentMax_ch2));
    AnyPhase.ICurrent_ch2MinWindow->setText(QString("%1").arg(AnyPhase.ICurrentMin_ch2));

    AnyPhase.IPhase_ch2Window->setText(QString("%1").arg(Isignal_CH2.phase_angle()));
    AnyPhase.IPhase_ch2MaxWindow->setText(QString("%1").arg(AnyPhase.IPhaseMax_ch2));
    AnyPhase.IPhase_ch2MinWindow->setText(QString("%1").arg(AnyPhase.IPhaseMin_ch2));
}
