/*
* 电压信号
*/
#ifndef VOLTAGESIGNAL_H
#define VOLTAGESIGNAL_H

#include <stdlib.h>
#include <string>

using std::string;

#ifndef ULONG32BASE
    #define ULONG32BASE (unsigned long)0         //32位基准
#endif

#ifndef PI
    #define PI 3.1415926535
#endif


class voltageSignal
{

private:
    typedef unsigned char u8;
    typedef unsigned long u32;
    typedef struct{
        u8 voltage[3];  //电压值
        u8 phase[3];    //相位值
        u8 freq[3];     //频率
        u8 HRU3[3];     //3次谐波
        u8 HRU5[3];     //5次谐波
        u8 HRU7[3];     //7次谐波
        u8 HRU11[3];    //11次谐波
        u8 HRU13[3];    //13次谐波
        u8 THD[3];      //总谐波畸变程度
    } SourceUinfo;  //原始电压信息

public:
    voltageSignal();
    voltageSignal(const unsigned char* data, size_t size);
    ~voltageSignal(){}

public:
    static voltageSignal FormatVoltageSignal(const unsigned char* data, size_t size);

    //电压值
    inline double Voltage(){
        return m_Voltage;
    }

    //相位,角度值
    inline double phase_angle(){
        return (double)m_Phase / 1000000 * 180 / PI;
    }

    //相位,弧度值
    inline double phase_rad(){
        return (double)m_Phase / 1000000;
    }

    //相位,弧度制带PI
    string phase_radPI();

    inline double Freq(){
        return m_Freq;
    }

    inline double HRU3(){
        return m_HRU3;
    }

    inline double HRU5(){
        return m_HRU5;
    }

    inline double HRU7(){
        return m_HRU7;
    }

    inline double HRU11(){
        return m_HRU11;
    }

    inline double HRU13(){
        return m_HRU13;
    }

    inline double THD(){
        return m_THD;
    }
private:
    bool loadVoltageSignal(const unsigned char* data, size_t size);
    //求最大公约数
    unsigned int GCD(unsigned int a, unsigned int b);
private:
    bool            m_isValid;      //数据是否有效
    double          m_Voltage;      //电压值
    unsigned long   m_Phase;        //相位值,存储的是原始值(弧度，加π后乘以1000000,取正整)
    double          m_Freq;         //频率
    double          m_HRU3;         //3次谐波
    double          m_HRU5;         //5次谐波
    double          m_HRU7;         //7次谐波
    double          m_HRU11;        //11次谐波
    double          m_HRU13;        //13次谐波
    double          m_THD;          //总谐波畸变程度
};

#endif // VOLTAGESIGNAL_H
