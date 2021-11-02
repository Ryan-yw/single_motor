#include <aris.hpp>
#include <thread>
#include <iostream>

#include "./include/robot.h"
#include <./include/imu.h>
#include "./include/spline.h"
#include "./include/mainwindow.h"
#include <QApplication>
#include <QDebug>

extern std::atomic<double> imu_angle[3];

int main(int argc, char *argv[])
{

    // imu thread //
    auto imu_thread = std::thread([&]()
    {
        bool start = false;
        imu::Data data;
        try
        {
            auto ret = imu::initIMU();
            imu::startIMU();
            while(true)
            {
                data = imu::getCurrentData();
                imu_angle[0] = data.pitch;
                imu_angle[1] = data.roll;
                imu_angle[2] = data.yaw;
            }
        }
        catch(std::exception &e)
        {
            std::cout<<"imu not connected: "<<e.what()<<std::endl;
        }
    });

    // plot thread //
    auto airs_th = std::thread([&]()
    {

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();

    });

while (true)
{
    /* code */
}


    // auto&cs = aris::server::ControlServer::instance();

    // cs.resetController(robot::createControllerQuadruped().release());
    // cs.resetPlanRoot(robot::createPlanQuadruped().release());

    // cs.init();

    // //开启WebSocket/socket服务器//
    // cs.open();
    // cs.start();
    // //等待终端输入函数，本函数不能去掉，否则实时线程和主线程都会结束//
    // cs.runCmdLine();


    return 0;
}
