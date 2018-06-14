#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>
#include <QNetworkDatagram>
#include <QMutex>
#include <QLineEdit>
#include "voltageSignal.h"
#include "currentSignal.h"

namespace Ui {
class meaSure;
}

class meaSure : public QWidget
{
    Q_OBJECT
    typedef struct{
        QLineEdit* UVoltage;
        QLineEdit* UPhase;
        QLineEdit* UFreq;
        QLineEdit* ICurrent_ch1;
        QLineEdit* IPhase_ch1;
        QLineEdit* ICurrent_ch2;
        QLineEdit* IPhase_ch2;
    } AnyPhaseWindows;  //任意相位的显示窗口指针

public:
    explicit meaSure(QWidget *parent = 0);
    ~meaSure();

public slots:
    void getDatagram(QNetworkDatagram Datagram);
    void onClickStart();
    void onClickStop();

private:
    void processDatagram(QNetworkDatagram& Datagram);
    void SetAnyPhaseDisplayInfo(AnyPhaseWindows& AnyPhase, voltageSignal Usignal, currentSignal Isignal_CH1, currentSignal Isignal_CH2);

private:
    Ui::meaSure *ui;
    bool         m_runFlag;
    QString      m_IP;
    QMutex       m_mutex;
    AnyPhaseWindows m_A;
    AnyPhaseWindows m_B;
    AnyPhaseWindows m_C;
};

#endif // MEASURE_H
