#include <iostream>
#include "Odometer.h"
#include <fstream>

using namespace std;
void simulate();
int main()
{
    cout << "start" << endl;
    simulate();
    cout << "finish..." << endl;
    cin.get();
    return 0;
}

//input sin wave
void simulate()
{
    float simTime = 10;
    float timeStep = 0.001;
    float t = 0.0;

    float wheelradius[2] = {0.15, -0.1};
    CChassis_base diffchassis;
    diffchassis.initializeParam(0.5f, wheelradius, 30, 1000, 3000, CChassis_base::DOUBLE_DIFF);

    Odometer::Instance()->setChassis(&diffchassis);

    ofstream simlog;
    simlog.open("simlog.log",'w');

    PlanarVector vcmd;
    AxisVector actualresult;
    PlanarVector predresult;

    predresult.reset();

    vcmd.reset();
    float cmdSteerAngle = 0;
    float simOmega = 5;


    for (; t < simTime; t += timeStep)
    {
        //vcmd.y = 1;
        vcmd.x = 0.2 * t;
        //vcmd.x = sin(simOmega * t) * 0.4;
        vcmd.theta = 0.2*t;
        //vcmd.y = cos(0.5 * simOmega * t) * 0.4;
        Odometer::Instance()->decomposeVelocity(vcmd, actualresult, cmdSteerAngle);
        for (int i = 0; i < diffchassis.driveWheelNum(); i++)
        {
            actualresult[i] *= timeStep;
        }

        predresult.x += (vcmd.x * timeStep) * cos(predresult.theta) - (vcmd.y * timeStep) * sin(predresult.theta);
        predresult.y += (vcmd.x * timeStep) * sin(predresult.theta) + (vcmd.y * timeStep) * cos(predresult.theta);
        predresult.theta += vcmd.theta * timeStep;

        Odometer::Instance()->updateGlobalPos(actualresult, cmdSteerAngle);
        simlog << "t: " << t << ", vx: " << vcmd.x 
            << ", predodom ["
            << predresult.x << ", "
            << predresult.y << ", "
            << predresult.theta << "]"
            << ", odom [" 
            << Odometer::Instance()->globalPos().x << ", "
            << Odometer::Instance()->globalPos().y << ", "
            << Odometer::Instance()->globalPos().theta << "]" << endl;
            
    }
    simlog.close();
}