#include <iostream>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <string>

#include "src/MQTT/MQTT_Publish.h"
#include "src/MQTT/MQTT_Subscribe.h"
#include "src/Location/MyLocation.h"
#include "src/Location/OtherLocation.h"
#include "src/Config.h"
#include "src/N3/EnvironmentN3.h"
#include "src/MQTT/MQTT_Time.h"
#include "src/N3/FlightData.h"
#include "src/N3/FlightControl.h"
#include "src/Task/TaskScheduler.h"
#include "src/Command/KeyboardCmd.h"

using namespace std;


int main() {
    KeyboardCmd *cmd = new KeyboardCmd();
    TaskScheduler *taskScheduler = new TaskScheduler();
    while (1) {

    }
    //MyLocation *mylocation = new MyLocation(config);
    //OtherLocation *otherLocation = new OtherLocation(config);


//    FlightData *flightdata = new FlightData(vehicle);
//
//    FlightControl *flightcontrol = new FlightControl(vehicle, flightdata);
//    char key = 0;
//    for (;;) {
//        cout << "positionGPS:" << "x: " << flightdata->getGpsFused().longitude
//             << " | y: " << flightdata->getGpsFused().latitude
//             << " | z: " << flightdata->getGpsFused().altitude;

//        cout << "     GlobalPosition:" << "x: " << flightdata->getGlobalPosition().longitude
//             << " | y: " << flightdata->getGlobalPosition().latitude
//             << " | z: " << flightdata->getGlobalPosition().height;

//        cout << "     positionOV:" << "x: " << flightdata->getPositionOV().x
//             << " | y: " << flightdata->getPositionOV().y
//             << " | z: " << flightdata->getPositionOV().z << endl;

//       cout<<"Velocity:"<<"x: "<< flightdata.getVelocity().data.x
//            <<" | y: "<< flightdata.getVelocity().data.y
//            <<" | z: "<<flightdata.getVelocity().data.z<<endl;
//        key = getchar();
//        switch (key)
//        {
//            case 't':{
//                flightcontrol->takeOff();
//            }
//                break;
//            case 'l':{
//                flightcontrol->land();
//            }
//                break;
//            case 'm':{
//                while (1)
//                {
//                    flightcontrol->moveByPositionOffset(2.0f, 2.0f, 0.0f);
//                    usleep(20000);
//                }
//
//            }
//                break;
//        }
//        usleep(100000);
    //   }

    return 0;
}

