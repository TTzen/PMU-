#include "currentSignal.h"
#include <string.h>

currentSignal::currentSignal()
{

}

currentSignal::currentSignal(unsigned char *data, size_t size)
{
    loadCurrentSignal(data, size);
}


currentSignal currentSignal::FormatCurrentSignal(const unsigned char *data, size_t size)
{
    currentSignal ISignal;
    ISignal.loadCurrentSignal(data, size);
    return ISignal;
}

//把弧度值用π表示
string currentSignal::phase_radPI()
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

unsigned int currentSignal::GCD(unsigned int a, unsigned int b)
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

bool currentSignal::loadCurrentSignal(const unsigned char *data, size_t size)
{
    if (size != sizeof(SourceIinfo)){
        return false;
    }
    SourceIinfo Iinfo;
    memset(&Iinfo, 0, sizeof(SourceIinfo));
    memcpy(&Iinfo, data, size);

    //解析电流
    m_Current =  (double)(ULONG32BASE
            | ((u32)Iinfo.Current[0] << 16)
            | ((u32)Iinfo.Current[1] << 8)
            | ((u32)Iinfo.Current[0])) / 10000;

    //解析相位(相位用原始数据)
    m_Phase   = ULONG32BASE | (u32)Iinfo.phase[0] << 16 | (u32)Iinfo.phase[1] << 8 | (u32)Iinfo.phase[2];

    //3次谐波
    m_HRU3  = (double)(ULONG32BASE
            | ((u32)Iinfo.HRU3[0] << 16)
            | ((u32)Iinfo.HRU3[1] << 8)
            | ((u32)Iinfo.HRU3[2])) / 10000;
    //5次谐波
    m_HRU5  = (double)(ULONG32BASE
            | ((u32)Iinfo.HRU5[0] << 16)
            | ((u32)Iinfo.HRU5[1] << 8)
            | ((u32)Iinfo.HRU5[2])) / 10000;
    //7次谐波
    m_HRU7  = (double)(ULONG32BASE
            | ((u32)Iinfo.HRU7[0] << 16)
            | ((u32)Iinfo.HRU7[1] << 8)
            | ((u32)Iinfo.HRU7[2])) / 10000;

    //11次谐波
    m_HRU11  = (double)(ULONG32BASE
            | ((u32)Iinfo.HRU11[0] << 16)
            | ((u32)Iinfo.HRU11[1] << 8)
            | ((u32)Iinfo.HRU11[2])) / 10000;

    //13次谐波
    m_HRU13  = (double)(ULONG32BASE
            | ((u32)Iinfo.HRU13[0] << 16)
            | ((u32)Iinfo.HRU13[1] << 8)
            | ((u32)Iinfo.HRU13[2])) / 10000;

    //电压总谐波畸变程度
    m_THD  = (double)(ULONG32BASE
            | ((u32)Iinfo.THD[0] << 16)
            | ((u32)Iinfo.THD[1] << 8)
            | ((u32)Iinfo.THD[2])) / 10000;
    return true;
}
