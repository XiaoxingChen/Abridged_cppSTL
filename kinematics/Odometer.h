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
#include <math.h>

class COdometer
{
public:

    COdometer() 
    {
        _globalOdom.reset();
        _prevVelCmd.reset();
    }

    void updateGlobalPos(const AxisVector& motorAxisDeltaRad, float steerAngle = NAN);
    void decomposeVelocity(const PlanarVector& planarVel, AxisVector& motorAxisVel, float steerAngle = NAN);
    void setChassis(CChassis_base* pChassis);
    const PlanarVector& globalPos() const { return _globalOdom; }

private:

    void motorAxisRadToWheelLineDisplace(const AxisVector& axisRad, AxisVector& lineDisp);
    void wheelLineVelToMotorAxisVel(const AxisVector& lineSpeed, AxisVector& axisSpeed);

    CChassis_base* _pChassis;
    
    //chassis status
    PlanarVector _globalOdom;
    float _globalSteerAngle;
    bool _isStopped;

    PlanarVector _prevVelCmd;
    uint32_t _prevVelTimestamp;

};

typedef NormalSingleton<COdometer> Odometer;

#endif
//end of file
