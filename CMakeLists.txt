cmake_minimum_required(VERSION 3.12)

project(SingleMotor)


# use c++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



if (WIN32)
set(Qt5Core_DIR C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5Core)
set(Qt5Widgets_DIR C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5Widgets)
set(Qt5Gamepad_DIR C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5Gui)
set(Qt5PrintSupport_DIR C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5PrintSupport)
endif(WIN32)
if (UNIX)
set(Qt5Core_DIR /opt/Qt5.11.2/5.11.2/gcc_64/lib/cmake/Qt5Core)
set(Qt5Widgets_DIR /opt/Qt5.11.2/5.11.2/gcc_64/lib/cmake/Qt5Widgets)
set(Qt5Gamepad_DIR /opt/Qt5.11.2/5.11.2/gcc_64/lib/cmake/Qt5Gui)
set(Qt5Gamepad_DIR /opt/Qt5.11.2/5.11.HEADER2/gcc_64/lib/cmake/Qt5Gamepad)
set(Qt5PrintSupport_DIR /opt/Qt5.11.2/5.11.2/gcc_64/lib/cmake/Qt5PrintSupport)
endif(UNIX)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

# find aris
if(UNIX)
        add_definitions(-DUNIX)
        find_package(aris REQUIRED PATHS /usr/aris)
endif(UNIX)
IF(WIN32)
        find_package(aris REQUIRED PATHS C:/aris/aris-1.5.0)
endif(WIN32)


include_directories(${aris_INCLUDE_DIRS})
include_directories("./lcm")
include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_UI
    src/mainwindow.ui
)
set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/qcustomplot.cpp
        src/axistag.cpp
        src/robot.cpp
        src/plan.cpp
        src/imu.cpp
        src/spline.cpp
        ${PROJECT_UI}
)
set(PROJECT_HEADER
    include/qcustomplot.h
    include/mainwindow.h
    include/axistag.h
    include/robot.h
    include/plan.h
    include/imu.h
    include/spline.h
)




add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADER})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::PrintSupport)
target_link_libraries(${PROJECT_NAME} lcm)
if(UNIX)
    target_link_libraries(${PROJECT_NAME} ${aris_LIBRARIES} atomic)
endif(UNIX)
IF(WIN32)
    target_link_libraries(${PROJECT_NAME} ${aris_LIBRARIES})
endif(WIN32)











