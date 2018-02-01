#include "Odometer.h"
#include "Console.h"
#include "ChassisKinematics.h"

void COdometer::motorAxisRadToWheelLineDisplace(const AxisVector& axisRad, AxisVector& lineDisp)
{
    for (int i = 0; i < _pChassis->driveWheelNum(); i++)
    {
        lineDisp[i] = axisRad[i] * _pChassis->wheelRadius(i) / _pChassis->reduceRatio();
    }
}

void COdometer::wheelLineVelToMotorAxisVel(const AxisVector& lineSpeed, AxisVector& axisSpeed)
{
    for (int i = 0; i < _pChassis->driveWheelNum(); i++)
    {
        axisSpeed[i] = lineSpeed[i] * _pChassis->reduceRatio() / _pChassis->wheelRadius(i);
    }
}

void COdometer::updateGlobalPos(const AxisVector& motorAxisDeltaRad, float steerAngle)
{
    auto chassisType = _pChassis->type();
    
    if (CChassis_base::CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO == chassisType
        || CChassis_base::CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO == chassisType)
    {
        if (steerAngle != steerAngle)
        {
            printf("No steer angle input for car-like chassis\r\n");
            return;
        }
    }

    AxisVector wheelLineDisp;
    motorAxisRadToWheelLineDisplace(motorAxisDeltaRad, wheelLineDisp);

    PlanarVector deltaPos;
    
    if (CChassis_base::DOUBLE_DIFF == chassisType)
    {
        forwardKinematicsTransDiff(wheelLineDisp, deltaPos, _pChassis->wheelbase());
    }
    else if (CChassis_base::TRICYCLE == chassisType)
    {
        forwardKinematicsTransTricycle(wheelLineDisp, deltaPos, _pChassis->wheelbase());
    }
    else if (CChassis_base::QUAD_MACNUM == chassisType)
    {
        forwardKinematicsTransMecanum(wheelLineDisp, deltaPos, _pChassis->wheelbase());
    }
    else if (CChassis_base::QUAD_DIFF == chassisType)
    {
        forwardKinematicsTransDiff(wheelLineDisp, deltaPos, _pChassis->wheelbase());
    }
    else if (CChassis_base::CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO == chassisType)
    {
        forwardKinematicsTransCarLikeSteerWheelOdo(wheelLineDisp, steerAngle,deltaPos, _pChassis->wheelbase());
    }
    else if (CChassis_base::CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO == chassisType)
    {
        forwardKinematicsTransCarLikeFixedWheelOdo(wheelLineDisp, steerAngle, deltaPos, _pChassis->wheelbase());
    }
    else
    {
        printf("Unsupported chassis type: %d\r\n", chassisType);
    }
    
    
    float tmp_dx = deltaPos.x * cos(_globalOdom.theta) - deltaPos.y * sin(_globalOdom.theta);
    float tmp_dy = deltaPos.x * sin(_globalOdom.theta) + deltaPos.y * cos(_globalOdom.theta);
    float tmp_dtheta = deltaPos.theta;

#if 0
    static int cnt = 0;
    if (++cnt > 100)
    {
        cnt = 0;
        printf("delta: x = %f m, y = %f m, theta = %f rad, stopped: %d\r\n",
            tmp_dx, tmp_dy, tmp_dtheta, m_stopped);
    }
#endif
    _globalOdom.x += tmp_dx;
    _globalOdom.y += tmp_dy;
    _globalOdom.theta += tmp_dtheta;
    

    while (_globalOdom.theta <= -M_PI) {
        _globalOdom.theta += 2 * M_PI;
    }
    while (_globalOdom.theta > M_PI) {
        _globalOdom.theta -= 2 * M_PI;
    }

    return ;
}

void COdometer::decomposeVelocity(const PlanarVector& planarVel, AxisVector& motorAxisVel, float steerAngle)
{
    auto chassisType = _pChassis->type();

    if (CChassis_base::CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO == chassisType
        || CChassis_base::CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO == chassisType)
    {
        if (steerAngle != steerAngle)
        {
            printf("No steer angle input for car-like chassis\r\n");
            return;
        }
    }

    AxisVector wheelLineVel;

    if (CChassis_base::DOUBLE_DIFF == chassisType)
    {
        inverseKinematicsTransDiff(planarVel, wheelLineVel, _pChassis->wheelbase());
    }
    else if (CChassis_base::TRICYCLE == chassisType)
    {
        inverseKinematicsTransTricycle(planarVel, wheelLineVel, _pChassis->wheelbase());
    }
    else if (CChassis_base::QUAD_MACNUM == chassisType)
    {
        inverseKinematicsTransMecanum(planarVel, wheelLineVel, _pChassis->wheelbase());
    }
    else if (CChassis_base::QUAD_DIFF == chassisType)
    {
        inverseKinematicsTransDiff(planarVel, wheelLineVel, _pChassis->wheelbase());
    }
    else if (CChassis_base::CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO == chassisType)
    {
        inverseKinematicsTransCarLikeSteerWheelDrive(planarVel, steerAngle, wheelLineVel, _pChassis->wheelbase());
    }
    else if (CChassis_base::CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO == chassisType)
    {
        inverseKinematicsTransCarLikeFixedWheelDrive(planarVel, steerAngle, wheelLineVel, _pChassis->wheelbase());
    }
    else
    {
        printf("Unsupported chassis type: %d\r\n", chassisType);
    }

    wheelLineVelToMotorAxisVel(wheelLineVel, motorAxisVel);
    motorAxisVelocitySaturLimit(motorAxisVel, _pChassis->driveWheelNum(), _pChassis->motorAxisMaxSpeed());
}

void COdometer::setChassis(CChassis_base* pChassis)
{
    if (NULL == pChassis)
        return;
    else
    {
        _pChassis = pChassis;
    }
}

//end of file

