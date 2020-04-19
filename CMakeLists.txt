cmake_minimum_required(VERSION 3.10.2)
project(GalaxyZ_cpp)

set(CMAKE_CXX_STANDARD 17)

set(INC_DIR include/djiosdk/)
set(LINK_DIR library)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(djiosdk-core)

set(INC_DIR include)
set(LINK_DIR library)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

link_libraries(paho-mqtt3a)
link_libraries(paho-mqtt3as)
link_libraries(paho-mqttpp3)


add_executable(GalaxyZ_cpp main.cpp src/MQTT/MQTT_Publish.h src/MQTT/MQTT_Publish.cpp src/MQTT/MQTT_Subscribe.h src/MQTT/MQTT_Subscribe.cpp
        src/Location/OtherLocation.h src/Config.h src/Config.cpp
        src/N3/EnvironmentN3.cpp src/N3/EnvironmentN3.h src/Location/OtherLocation.cpp src/Location/MyLocation.cpp src/Location/Location.cpp src/Location/Location.h src/N3/FlightData.cpp src/N3/FlightData.h src/MQTT/MQTT_Time.cpp src/MQTT/MQTT_Time.h src/N3/FlightControl.cpp src/N3/FlightControl.h src/Controller/PID.cpp src/Controller/PID.h src/Controller/MoveController.cpp src/Controller/MoveController.h src/Status.cpp src/Status.h src/Task/TaskScheduler.cpp src/Task/TaskScheduler.h src/Base/PointGroup.cpp src/Base/PointGroup.h src/Strategy/LoadPointFile.cpp src/Strategy/LoadPointFile.h src/Task/Point2PointTask.cpp src/Task/Point2PointTask.h src/Task/Task.cpp src/Task/Task.h src/Base/Point.cpp src/Base/Point.h src/N3/CreatVehicle.cpp src/N3/CreatVehicle.h src/Base/File2Json.cpp src/Base/File2Json.h src/Command/Commands.cpp src/Command/Commands.h src/Command/KeyboardCmd.cpp src/Command/KeyboardCmd.h)

target_link_libraries(GalaxyZ_cpp paho-mqttpp3 paho-mqtt3as paho-mqtt3a djiosdk-core.a pthread)