#ifndef IMU
#define IMU

#include <stdint.h>
#include <cstdint>
namespace imu{

//imu instruction
static const uint8_t start[6] = {0xA5,0x5A,0x04,0x01,0x05,0xAA};
static const uint8_t stop[6] = {0xA5,0x5A,0x04,0x02,0x06,0xAA};
static int data_length = 40;

//the imu path and handle
static char default_path[] = "/dev/ttyUSB0";
static int fd = -1;

static unsigned char prerecstatus;
static unsigned char recstatus;
static unsigned char ccnt = 0;
static unsigned char packerflag = 0;
static uint8_t check = 0;
static unsigned char rxbuf[100];

struct Data
{
    double yaw;
    double roll;
    double pitch;

    double x_acc;
    double y_acc;
    double z_acc;

    double x_gyro;
    double y_gyro;
    double z_gyro;
};

struct Orientation
{
    double yaw;
    double roll;
    double pitch;
};

struct Acc
{
    double x_acc;
    double y_acc;
    double z_acc;
};

struct Gravity
{
    double num;
    double quaternion[4];
};

void inline data2acc(const Data* data, Acc * acc)
{
    acc->x_acc = data->x_acc;
    acc->y_acc = data->y_acc;
    acc->z_acc = data->z_acc;
}

void inline data2ori(const Data* data, Orientation* ori)
{
    ori->yaw = data->yaw;
    ori->roll = data->roll;
    ori->pitch = data->pitch;
}


static Data data;

Data getCurrentData();

int initIMU();

int closeIMU();

int startIMU();

using MsgSize = std::uint32_t;
using MsgID = std::uint32_t;
using MsgType = std::uint64_t;


/** @brief exclude the effect of gravity
 * @param acc
 * @param g
 * 
 * 
 */
//void gravity_calib(const Gravity& g, const Acc& acc, const Ori* ori, Acc*result );
//void gravity_calib(const Data* data);
///** @brief
// * @param
// * @param
// */
//void cal_pos(const Acc* acc, const Orientation* ori, double* )



}



#endif //IMU
