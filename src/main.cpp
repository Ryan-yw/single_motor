#include <aris.hpp>
#include "robot.h"
#include <thread>
#include <imu.h>
#include "spline.h"

int main(int argc, char *argv[])
{



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
                //std::cout << data.roll << "\t" << data.pitch << "\t" << data.yaw << std::endl;
                //std::cout << data.x_acc << "\t" << data.y_acc << "\t" << data.z_acc << std::endl;
                //std::cout << data.x_gyro << "\t" << data.y_gyro << "\t" << data.z_gyro << std::endl;


            }
        }
        catch(std::exception &e)
        {
            std::cout<<"imu not connected: "<<e.what()<<std::endl;
        }
    });


    while (true)
    {

        //spline::quintic();

    }




//    auto&cs = aris::server::ControlServer::instance();
	
//    cs.resetController(robot::createControllerQuadruped().release());
//    cs.resetPlanRoot(robot::createPlanQuadruped().release());

//    cs.init();

//	//开启WebSocket/socket服务器//
//    cs.open();
//    cs.start();
//	//等待终端输入函数，本函数不能去掉，否则实时线程和主线程都会结束//
//    cs.runCmdLine();

	return 0;
}
