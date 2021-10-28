#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "imu.h"

namespace imu{

Data getCurrentData()
{
    tcflush(fd,TCIOFLUSH);
    while (1)
    {
        if(packerflag)
        {
            if(check != rxbuf[data_length-1])
            {
                std::cout<<"check error"<<(uint16_t)check<<"  "<<(uint16_t)(rxbuf[data_length-1])<<std::endl;
                recstatus = 0;
                ccnt = 0;
                packerflag = 0;
                check = 0;
                tcflush(fd, TCIOFLUSH);
                continue;
            }

            check = 0;
            recstatus = 0;
            ccnt = 0;
            packerflag = 0;
//            for(int i = 0;i<data_length;++i)
//            {
//                std::cout  << std::hex << +rxbuf[i] << "  ";
//            }
//            std::cout<<std::endl;
            //the scalar of yaw roll and pitch is 0.1degree
            int16_t yaw = rxbuf[1];
            yaw = yaw<<8|rxbuf[2];
            int16_t pitch = rxbuf[3];
            pitch = pitch<<8|rxbuf[4];
            int16_t roll = rxbuf[5];
            roll = roll<<8|rxbuf[6];
            //after divided by 16384, the scalar of x y z accelaration are g
            int16_t x_acc = rxbuf[7];
            x_acc = x_acc<<8|rxbuf[8];
            int16_t y_acc = rxbuf[9];
            y_acc = y_acc<<8|rxbuf[10];
            int16_t z_acc = rxbuf[11];
            z_acc = z_acc<<8|rxbuf[12];
            //after divided by 32.8 the scalar of x y z gyro data are degreee/second
            int16_t x_gyro = rxbuf[13];
            x_gyro = x_gyro<<8| rxbuf[14];
            int16_t y_gyro = rxbuf[15];
            y_gyro = y_gyro <<8|rxbuf[16];
            int16_t z_gyro = rxbuf[17];
            z_gyro = z_gyro<<8 |rxbuf[18];

            data.yaw = 0.1*yaw;
            data.pitch = 0.1*pitch;
            data.roll = 0.1*roll;
            data.x_acc = x_acc/16384.0;
            data.y_acc = y_acc/16384.0;
            data.z_acc = z_acc/16384.0;
            data.x_gyro = x_gyro/32.8;
            data.y_gyro = y_gyro/32.8;
            data.z_gyro = z_gyro/32.8;

            return imu::data;
        }
        uint8_t tmpch[1] ;
        read(fd,tmpch,sizeof(uint8_t));
        if(*tmpch == 0xa5&&!recstatus)
        {
            prerecstatus = 1;
            recstatus = 0;
            ccnt = 0;
            packerflag = 0 ;
           // std::cout<<"prerecstatus"<<std::endl;
            continue;
        }else if(*tmpch == 0x5a && prerecstatus){
            prerecstatus = 0;
            recstatus = 1;
            ccnt = 0;
            check = 0;
           // std::cout<<"recstatus"<<std::endl;
            continue;
        }
        else if(prerecstatus)
        {
            prerecstatus = 0;
            continue;
        }
        else if(ccnt ==0&&recstatus)
        {
            check += (*tmpch);
            data_length= *tmpch;
            rxbuf[ccnt++] = *tmpch;
         //   std::cout<<"data length = "<<(uint16_t)(data_length)<<std::endl;
            continue;
        }
        else if(ccnt == data_length && *tmpch == 0xaa)
        {
            recstatus = 0;
            packerflag = 1;
        //    std::cout<<"package at "<<(uint16_t)ccnt<<std::endl;
            ccnt = 0;
            continue;
        }
        else if(ccnt == data_length-1)
        {
            rxbuf[ccnt++] = *tmpch;
            continue;
        }
        else if(ccnt==data_length)
        {
            recstatus = 0;
            packerflag = 0;
            ccnt = 0;
        //    std::cout<<"recv end unexpecttedly "<<std::endl;
            continue;
        }
        else if(recstatus == 1)
        {
            rxbuf[ccnt++] = *tmpch;
            check += *tmpch;
            continue;
        }
    }
}
int initIMU()
{
    char *path;

    //获取串口设备描述符
    path = (char *)default_path;
    fd = open(path, O_RDWR | O_NOCTTY);//noctty,not influenced by terminal,
    if(fd<0)
    {
        printf("Fail to Open %s device\n", path);
        return 1;
    }
    struct termios opt;//BASIC SETTING
    //设置串口输出波特率
    cfsetospeed(&opt, B115200);
    //设置串口输入波特率
    cfsetispeed(&opt, B115200);
    //设置数据位数 8位数据位
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    //校验位 无校验位
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    //设置停止位  1位停止位
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag |= CLOCAL | CREAD;
    opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opt.c_oflag &= ~OPOST;
    opt.c_iflag &= ~(BRKINT | ICRNL | ISTRIP | IXON);
    //设置停止time
    opt.c_cc[VTIME]=20;
    opt.c_cc[VMIN]=0;
    //更新配置
    tcsetattr(fd, TCSANOW, &opt);
    std::cout << "Device ttyUSB0 is set to 115200bps,8N1\n" << std::endl;
    tcflush(fd,TCIOFLUSH);
    write(fd,start,6);
    tcflush(fd,TCIOFLUSH);
    return 0;
}
int closeIMU()
{
     write(fd,stop,6);
     tcflush(fd,TCIOFLUSH);
     return 0;
}
int startIMU()
{
     write(fd,start,6);
     tcflush(fd,TCIOFLUSH);
     return 0;
}



}
