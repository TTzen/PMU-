#include "PowerQuality.h"
#include <string.h>
#include <QDebug>
#include <time.h>

PowerQuality::PowerQuality(const char *buffer, size_t size)
{
    m_isValid = processSourceData(buffer, size);
}


bool PowerQuality::readSourceData(const char *buffer, size_t size)
{
    m_isValid = processSourceData(buffer, size);
    return m_isValid;
}


bool PowerQuality::processSourceData(const char *buffer, size_t size)
{
    if (size != 254 || (u8)buffer[1] != BEGING || (u8)buffer[253] != END){      //检测数据长度是否正确
        return false;
    }

    tagDataFrame DataFrame;
    memset(&DataFrame, 0, sizeof(tagDataFrame));
    memcpy(&DataFrame, buffer, size);

    /* 帧同步字
    第一字节: AAH
    第二字节: 帧类型和版本号
    Bit 7: 保留未来定义
    Bits 6-4:000: 数据帧011: 配置帧
    Bits 3-0:规约版本号，二进制表示（1－15）
    (因为在ARM板中的数据是大端存储,存储到一个int类型数中,发送到上位机的时候低字节在前,并且FrameHead的后两个字节是无效的) */

    switch ((DataFrame.FrameHead[0] & 0x70) >> 4){
    case 0x00:
        m_type = PowerQuality::data;        //数据格式
        break;
    case 0x11:
        m_type = PowerQuality::com;         //命令格式
        break;
    default:
        return false;                       //不合法
    }
    m_version   = DataFrame.FrameHead[0] & 0x0F;    //版本号
    m_frameSize = DataFrame.FrameSize;              //帧字节数

    /* 时间转换 */
    SetmkTime(DataFrame.RealTime);

    m_fracsec = DataFrame.FracSec;  //等分秒
    m_idCode  = (unsigned int)0 | DataFrame.IDCode[0] | DataFrame.IDCode[1] << 8;   //设备号

    /* 电压三项不平衡度 */
    m_Vnub = (double)((unsigned int)0
                      | ((unsigned int)DataFrame.Vnub[0] << 16)
                      | ((unsigned int)DataFrame.Vnub[1] << 8)
                      | ((unsigned int)DataFrame.Vnub[2])) / 10000;

    /* 电流三项不平衡度通道一 */
    m_Inub1 = (double)((unsigned int)0
                      | ((unsigned int)DataFrame.Inub1[0] << 16)
                      | ((unsigned int)DataFrame.Inub1[1] << 8)
                      | ((unsigned int)DataFrame.Inub1[2])) / 10000;

    /* 电流三项不平衡度通道二 */
    m_Inub2 = (double)((unsigned int)0
                       | ((unsigned int)DataFrame.Inub2[0] << 16)
                       | ((unsigned int)DataFrame.Inub2[1] << 8)
                       | ((unsigned int)DataFrame.Inub2[2])) / 10000;
    //电压信号
    m_AvoltageSignal = voltageSignal(DataFrame.U + 0, 27);
    m_BvoltageSignal = voltageSignal(DataFrame.U + 27, 27);
    m_CvoltageSignal = voltageSignal(DataFrame.U + 54, 27);

    //电流信号通道一
    m_AcurrentSignal_channel_1 = currentSignal(DataFrame.I1 + 0, 24);
    m_BcurrentSignal_channel_1 = currentSignal(DataFrame.I1 + 24, 24);
    m_CcurrentSignal_channel_1 = currentSignal(DataFrame.I1 + 48, 24);

    //电流信号通道二
    m_AcurrentSignal_channel_2 = currentSignal(DataFrame.I2 + 0, 24);
    m_BcurrentSignal_channel_2 = currentSignal(DataFrame.I2 + 24, 24);
    m_CcurrentSignal_channel_2 = currentSignal(DataFrame.I2 + 48, 24);

    return true;
}


time_t PowerQuality::SetmkTime(const u8 SouceTime[])
{
    unsigned long TimeData = (unsigned long)0
            | (unsigned long)SouceTime[0] << 16
            | (unsigned long)SouceTime[1] << 8
            |(unsigned long) SouceTime[2];

    unsigned long TimeTime = (unsigned long)0
            | (unsigned long)SouceTime[3] << 16
            | (unsigned long)SouceTime[4] << 8
            | (unsigned long)SouceTime[5];

    struct tm StructTm;
    memset(&StructTm, 0, sizeof(struct tm));
    StructTm.tm_year = (TimeData % 100) + 100;  //默认从2000年开始
    StructTm.tm_mon  = (TimeData / 100 % 100) - 1;
    StructTm.tm_mday = (TimeData / 10000);

    StructTm.tm_hour = TimeTime / 10000;
    StructTm.tm_min  = TimeTime / 100 % 100;
    StructTm.tm_sec  = TimeTime % 100;

    time_t tim = mktime(&StructTm);

    if (tim == -1){
        m_time = 0;
    } else{
        m_time = tim;
    }

    return m_time;
}
