#include "voltageSignal.h"
#include <string.h>

voltageSignal::voltageSignal():
    m_isValid(false)
{

}


voltageSignal::voltageSignal(const unsigned char *data, size_t size):
    m_isValid(false)
{
    loadVoltageSignal(data, size);
}


voltageSignal voltageSignal::FormatVoltageSignal(const unsigned char *data, size_t size)
{
    voltageSignal Usignal;
    Usignal.loadVoltageSignal(data, size);
    return Usignal;
}

//把弧度值用π表示
string voltageSignal::phase_radPI()
{
    int integer = m_Phase / 1000000;
    int mod = m_Phase % 1000000;

    //最大公约数
    int gcd = GCD(mod, 1000000);

    int numerator = integer * (1000000 / gcd) + mod / gcd;
    int denominator = 1000000 / gcd;

    char radPIbuffer[256];
    memset(radPIbuffer, 0, 256);
    snprintf(radPIbuffer, 256, "%d/%d * PI", numerator, denominator);

    return radPIbuffer;
}


//辗转相除法求两个数的最大公约数
unsigned int voltageSignal::GCD(unsigned int a, unsigned int b)
{
    unsigned int mod = 0;
        do{
            mod = a % b;
            if (mod != 0){
                a = b;
                b = mod;
            }
        }
        while (mod != 0);

    return b;
}

bool voltageSignal::loadVoltageSignal(const unsigned char *data, size_t size)
{
    //检测原始数据是否正确
    if (size != sizeof(SourceUinfo)){
        return false;
    }

    SourceUinfo Uinfo;
    memset(&Uinfo, 0, sizeof(SourceUinfo));
    memcpy(&Uinfo, data, size);

    //解析电流
    m_Voltage =  (double)(ULONG32BASE
            | ((u32)Uinfo.voltage[0] << 16)
            | ((u32)Uinfo.voltage[1] << 8)
            | ((u32)Uinfo.voltage[0])) / 10000;

    //解析相位(相位用原始数据)
    m_Phase   = ULONG32BASE | (u32)Uinfo.phase[0] << 16 | (u32)Uinfo.phase[1] << 8 | (u32)Uinfo.phase[2];

    //解析频率
    m_Freq    = (double)(ULONG32BASE
            | ((u32)Uinfo.freq[0] << 16)
            | ((u32)Uinfo.freq[1] << 8)
            | ((u32)Uinfo.freq[2])) / 10000;
    //3次谐波
    m_HRU3  = (double)(ULONG32BASE
            | ((u32)Uinfo.HRU3[0] << 16)
            | ((u32)Uinfo.HRU3[1] << 8)
            | ((u32)Uinfo.HRU3[2])) / 10000;
    //5次谐波
    m_HRU5  = (double)(ULONG32BASE
            | ((u32)Uinfo.HRU5[0] << 16)
            | ((u32)Uinfo.HRU5[1] << 8)
            | ((u32)Uinfo.HRU5[2])) / 10000;
    //7次谐波
    m_HRU7  = (double)(ULONG32BASE
            | ((u32)Uinfo.HRU7[0] << 16)
            | ((u32)Uinfo.HRU7[1] << 8)
            | ((u32)Uinfo.HRU7[2])) / 10000;

    //11次谐波
    m_HRU11  = (double)(ULONG32BASE
            | ((u32)Uinfo.HRU11[0] << 16)
            | ((u32)Uinfo.HRU11[1] << 8)
            | ((u32)Uinfo.HRU11[2])) / 10000;

    //13次谐波
    m_HRU13  = (double)(ULONG32BASE
            | ((u32)Uinfo.HRU13[0] << 16)
            | ((u32)Uinfo.HRU13[1] << 8)
            | ((u32)Uinfo.HRU13[2])) / 10000;

    //电压总谐波畸变程度
    m_THD  = (double)(ULONG32BASE
            | ((u32)Uinfo.THD[0] << 16)
            | ((u32)Uinfo.THD[1] << 8)
            | ((u32)Uinfo.THD[2])) / 10000;
    return true;
}
