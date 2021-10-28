cmake_minimum_required(VERSION 3.12)

project(SingleMotor)

# aris use c++ 17 standard
set(CMAKE_CXX_STANDARD 17)


include_directories("./lcm")
include_directories("./include")

# find aris
if(UNIX)
	add_definitions(-DUNIX)
        find_package(aris REQUIRED PATHS /usr/aris)
endif(UNIX)
IF(WIN32)
        find_package(aris REQUIRED PATHS C:/aris/aris-1.5.0)
endif(WIN32)
include_directories(${aris_INCLUDE_DIRS})


add_executable(single_motor src/main.cpp src/robot.cpp src/plan.cpp src/imu.cpp src/spline.cpp )

if(UNIX)
    target_link_libraries(single_motor ${aris_LIBRARIES} atomic)
endif(UNIX)
IF(WIN32)
    target_link_libraries(single_motor ${aris_LIBRARIES})
endif(WIN32)

target_link_libraries(single_motor lcm)
