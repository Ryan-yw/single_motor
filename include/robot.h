#ifndef ROBOT_H_
#define ROBOT_H_

#include <memory>
#include<thread>
#include <aris.hpp>
#include<lcm/lcm-cpp.hpp>
#include<lcm/lcm.h>
#include<../lcm/state_estimator_lcmt.hpp>
namespace robot
{


class SetMaxToq : public aris::core::CloneObject<SetMaxToq, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;
    auto virtual collectNrt()->void;

    virtual ~SetMaxToq();
    explicit SetMaxToq(const std::string &name = "set_max_toq");
};

class ReadJoint :public aris::core::CloneObject<ReadJoint, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;

    virtual ~ReadJoint();
    explicit ReadJoint(const std::string &name = "dog_read_joint");
};

// 正弦曲线 //
class MoveJS : public aris::core::CloneObject<MoveJS, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;
    auto virtual collectNrt()->void;

    explicit MoveJS(const std::string& name = "MoveJS_plan");

};

//move joint pos
class MoveJoint : public aris::core::CloneObject<MoveJoint, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;
    auto virtual collectNrt()->void;

    explicit MoveJoint(const std::string &name = "MoveJiont");
private:
    double dir_;
};

//torque control
class MoveTorque :public aris::core::CloneObject<MoveTorque, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;

    virtual ~MoveTorque();
    explicit MoveTorque(const std::string &name = "move_torque");
private:
    double dir_;
};

class RobotDataProcess
{
public:

    RobotDataProcess();
    ~RobotDataProcess() = default;

    auto dataProcess(const lcm::ReceiveBuffer *rbuf,const std::string &chan,const state_estimator_lcmt *msg)->void;

private:
    lcm::LCM lcm_robot_estimator_;
    std::thread estimator_data_robot_thread_;

};

// test thread
class TestThread :public aris::core::CloneObject<TestThread, aris::plan::Plan>
{
public:
    auto virtual prepareNrt()->void;
    auto virtual executeRT()->int;

    virtual ~TestThread();
    explicit TestThread(const std::string &name = "test_thread");
private:
    double dir_;

};

auto createControllerQuadruped()->std::unique_ptr<aris::control::Controller>;
auto createPlanQuadruped()->std::unique_ptr<aris::plan::PlanRoot>;
}

#endif
