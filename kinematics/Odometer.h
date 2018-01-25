#ifndef _ODOMETER_H_
#define _ODOMETER_H_

#include "Chassis_base.h"

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

    void forwardKinematicsTrans(const AxisVector& motorAxisRad, PlanarPos& planarPos);
    void forwardKinematicsTrans(const AxisVector& motorAxisRad, const float steer_angle, PlanarPos& planarPos);

    void inverseKinematicsTrans(const PlanarVel& planarVel, AxisVector& motorAxisVel);
    void inverseKinematicsTrans(const PlanarVel& planarVel, const float steer_angle, AxisVector& motorAxisVel);

    void updateGlobalCoord(const PlanarPos& deltaPos);

private:

    //Kinematics - Diff
    void forwardKinematicsTransDiff(const AxisVector& lineDisp, PlanarPos& planarPos);
    void inverseKinematicsTransDiff(const PlanarVel& planarVel, AxisVector& lineVel);

    //Tricycle
    void forwardKinematicsTransTricycle(const AxisVector& lineDisp, PlanarPos& planarPos);
    void inverseKinematicsTransTricycle(const PlanarVel& planarVel, AxisVector& lineVel);

    void forwardKinematicsTransMecanum(const AxisVector& lineDisp, PlanarPos& planarPos);
    void inverseKinematicsTransMecanum(const PlanarVel& planarVel, AxisVector& lineVel);

    void forwardKinematicsTransCarLikeSteerWheelOdo(const AxisVector& lineDisp, const float steer_angle, PlanarPos& planarPos);
    void forwardKinematicsTransCarLikeFixedWheelOdo(const AxisVector& lineDisp, const float steer_angle, PlanarPos& planarPos);

    void inverseKinematicsTransCarLikeSteerWheelDrive(const PlanarVel& planarVel, const float steer_angle, AxisVector& lineVel);
    void inverseKinematicsTransCarLikeFixedWheelDrive(const PlanarVel& planarVel, const float steer_angle, AxisVector& lineVel);

    void motorAxisRadToWheelLineDisplace(const AxisVector& axisRad, AxisVector& lineDisp);
    void wheelLineSpeedToMotorAxisSpeed(const AxisVector& lineSpeed, AxisVector& axisSpeed);
    
    CChassis_base* _pChassis;
    PlanarPos _globalOdometer;
    bool _isStopped;
};

#endif
//end of file
