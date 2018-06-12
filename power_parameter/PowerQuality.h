#ifndef POWERQUALITY_H
#define POWERQUALITY_H

#include <time.h>
#include <currentSignal.h>
#include <voltageSignal.h>
#include <string>
#include <iostream>
#include <string.h>

#define BEGING 0xAA //UDP信息首字节标记
#define END    0x16 //UDP信息末字节标记

using std::string;

typedef unsigned char u8;


class PowerQuality
{

    /*
    * 电能质量的数据类型数据类型
    */
    typedef enum{
        data = 0,       //数据
        com  = !data    //命令
    }dataType;

    /*
    * 从UDP发送过来的数据格式
    */
    typedef struct
    {
        u8		FrameHead[4];
        u8	    FrameSize;
        u8      RealTime[6];
        u8      FracSec;
        u8      IDCode[4];
        u8		Channel1;
        u8      U[81];
        u8		Vnub[3];
        u8		Channel2;
        u8		I1[72];
        u8		Inub1[3];
        u8		Channel3;
        u8		I2[72];
        u8		Inub2[3];
        u8      FrameEnd;
    }tagDataFrame;

public:
    PowerQuality(){}

    PowerQuality(const char* buffer, size_t size);

    ~PowerQuality(){}


public:
    bool readSourceData(const char* buffer, size_t size);

    inline bool isValid() const{
        return m_isValid;
    }

    inline string ToLocalTime(const char* form) const{
        struct tm* _time = localtime(&m_time);

        char Timebuffer[256];
        memset(Timebuffer, 0, 256);
        strftime(Timebuffer, 256, form, _time);
        return Timebuffer;
    }

    inline double Vnub() const{
        return m_Vnub;
    }

    inline double Inub1() const{
        return m_Inub1;
    }

    inline double Inub2() const{
        return m_Inub2;
    }

    inline voltageSignal A_voltageSignal() const{
        return m_AvoltageSignal;
    }

    inline voltageSignal B_voltageSignal() const{
        return m_BvoltageSignal;
    }

    inline voltageSignal C_voltageSignal()const{
        return m_CvoltageSignal;
    }

    inline currentSignal A_voltageSignal_ch1() const{
        return m_AcurrentSignal_channel_1;
    }

    inline currentSignal B_voltageSignal_ch1() const{
        return m_BcurrentSignal_channel_1;
    }

    inline currentSignal C_voltageSignal_ch1() const{
        return m_CcurrentSignal_channel_1;
    }

    inline currentSignal A_voltageSignal_ch2() const{
        return m_AcurrentSignal_channel_2;
    }

    inline currentSignal B_voltageSignal_ch2() const{
        return m_BcurrentSignal_channel_2;
    }

    inline currentSignal C_voltageSignal_ch2() const{
        return m_CcurrentSignal_channel_2;
    }
private:
    bool processSourceData(const char* buffer, size_t size);

    time_t SetmkTime(const u8 SouceTime[6]);
private:
    /* 数据是否有效 */
    bool m_isValid;
    /* 帧类型  */
    dataType m_type;
    /* 版本号  */
    unsigned char m_version;
    /* 帧字节数 */
    unsigned char m_frameSize;
    /* 时间    */
    time_t m_time;
    /* 秒等分 */
    unsigned int m_fracsec;
    /* 设备编号 */
    unsigned int m_idCode;

    /* 电压三项不平衡度 */
    double m_Vnub;

    /* 电流三项不平衡度通道一 */
    double m_Inub1;

    /* 电流三项不平衡度通道二 */
    double m_Inub2;
//电压信号
    /* A相电压信号 */
    voltageSignal m_AvoltageSignal;
    /* B相电压信号 */
    voltageSignal m_BvoltageSignal;
    /* C相电压信号 */
    voltageSignal m_CvoltageSignal;

//电流信号_1通道
    /* A相电流信号_1通道 */
    currentSignal m_AcurrentSignal_channel_1;
    /* B相电流信号_1通道 */
    currentSignal m_BcurrentSignal_channel_1;
    /* C相电流信号_1通道 */
    currentSignal m_CcurrentSignal_channel_1;

//电压信号_2通道
    /* A相电流信号_2通道 */
    currentSignal m_AcurrentSignal_channel_2;
    /* B相电流信号_2通道 */
    currentSignal m_BcurrentSignal_channel_2;
    /* C相电流信号_2通道 */
    currentSignal m_CcurrentSignal_channel_2;
};

#endif // POWERQUALITY_H
