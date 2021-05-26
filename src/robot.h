#ifndef ROBOT_H_
#define ROBOT_H_

#include <memory>
#include <aris.hpp>

namespace robot
{

    // 正弦曲线 //
    class MoveJS : public aris::core::CloneObject<MoveJS, aris::plan::Plan>
    {
    public:
        auto virtual prepareNrt()->void;
        auto virtual executeRT()->int;
        auto virtual collectNrt()->void;

        explicit MoveJS(const std::string& name = "MoveJS_plan");

    };
    
    //
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



    auto createControllerQuadruped()->std::unique_ptr<aris::control::Controller>;
    auto createPlanQuadruped()->std::unique_ptr<aris::plan::PlanRoot>;
}

#endif
