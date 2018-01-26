/**
******************************************************************************
* @file    Odometer.h
* @author  Chenxx
* @version V1.0
* @date    2018-1-25
* @brief   This file defines the chassis kinematics odometer.
******************************************************************************/
//release information:

#ifndef _ODOMETER_H_
#define _ODOMETER_H_

#include "Chassis_base.h"
#include "Singleton.h"

struct PlanarVel {
    float vx;
    float vy;
    float w;
};

struct PlanarPos {
    float x;
    float y;
    float theta;
};

typedef float AxisVector[CChassis_base::MAX_WHEEL_NUM];

class COdometer
{
public:

    COdometer() {}

    void updateGlobalPos(const AxisVector& motorAxisDeltaRad, float steerAngle);
    void decomposeVelocity(const PlanarVel& planarVel, AxisVector& motorAxisVel, float steerAngle);

private:
    void motorAxisRadToWheelLineDisplace(const AxisVector& axisRad, AxisVector& lineDisp);
    void wheelLineVelToMotorAxisVel(const AxisVector& lineSpeed, AxisVector& axisSpeed);

    static CChassis_base* _pChassis;
    static PlanarPos _globalOdom;
    static float _globalSteerAngle;
    static bool _isStopped;
};

typedef NormalSingleton<COdometer> Odometer;

#endif
//end of file
