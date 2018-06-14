#ifndef SYNC_H
#define SYNC_H

#include <QWidget>
#include <QNetworkDatagram>
#include <QMutex>
#include <QLineEdit>
#include "voltageSignal.h"
#include "currentSignal.h"

namespace Ui {
class Sync;
}

class Sync : public QWidget
{
    typedef struct AnyPhaseInfo{
        QLineEdit* UVoltageWindow;
        QLineEdit* UVoltageMaxWindow;
        QLineEdit* UVoltageMinWindow;

        QLineEdit* UPhaseWindow;
        QLineEdit* UPhaseMaxWindow;
        QLineEdit* UPhaseMinWindow;

        QLineEdit* UFreqWindow;
        QLineEdit* UFreqMaxWindow;
        QLineEdit* UFreqMinWindow;

        QLineEdit* ICurrent_ch1Window;
        QLineEdit* ICurrent_ch1MaxWindow;
        QLineEdit* ICurrent_ch1MinWindow;

        QLineEdit* IPhase_ch1Window;
        QLineEdit* IPhase_ch1MaxWindow;
        QLineEdit* IPhase_ch1MinWindow;

        QLineEdit* ICurrent_ch2Window;
        QLineEdit* ICurrent_ch2MaxWindow;
        QLineEdit* ICurrent_ch2MinWindow;

        QLineEdit* IPhase_ch2Window;
        QLineEdit* IPhase_ch2MaxWindow;
        QLineEdit* IPhase_ch2MinWindow;

        double  UvolatageMax;
        double  UvolatageMin;
        double  UPhaseMax;
        double  UPhaseMin;
        double  UFreqMax;
        double  UFreqMin;

        double  ICurrentMax_ch1;
        double  ICurrentMin_ch1;
        double  IPhaseMax_ch1;
        double  IPhaseMin_ch1;

        double  ICurrentMax_ch2;
        double  ICurrentMin_ch2;
        double  IPhaseMax_ch2;
        double  IPhaseMin_ch2;

        AnyPhaseInfo():
        UvolatageMax(0),
        UvolatageMin(9999.0),
        UPhaseMax(0),
        UPhaseMin(9999.0),
        UFreqMax(0),
        UFreqMin(9999.0),

        ICurrentMax_ch1(0),
        ICurrentMin_ch1(9999.0),
        IPhaseMax_ch1(0),
        IPhaseMin_ch1(9999.0),
        ICurrentMax_ch2(0),
        ICurrentMin_ch2(9999.0),
        IPhaseMax_ch2(0),
        IPhaseMin_ch2(9999.0){

        }
    } AnyPhaseInfo;  //任意相位的显示窗口指针

    Q_OBJECT
public:
    explicit Sync(QWidget *parent = 0);
    ~Sync();

public slots:
    void onStartButtonClick();
    void getDatagram(QNetworkDatagram Datagram);

private:
    void processDatagram(QNetworkDatagram& Datagram);
    void SetAnyPhaseDisplayInfo(AnyPhaseInfo& AnyPhase, voltageSignal Usignal, currentSignal Isignal_CH1, currentSignal Isignal_CH2);

private:
    Ui::Sync *ui;

    bool m_runFlag;
    QMutex    m_mutex;
    QString   m_dev1IP;
    QString   m_dev2IP;

    ///设备一的参数
    AnyPhaseInfo m_A_Dev1;
    AnyPhaseInfo m_B_Dev1;
    AnyPhaseInfo m_C_Dev1;

    ///设备二的参数
    AnyPhaseInfo m_A_Dev2;
    AnyPhaseInfo m_B_Dev2;
    AnyPhaseInfo m_C_Dev2;

};

#endif // SYNC_H
