#include "Odometer.h"
#include "Chassis_base.h"
#include "Console.h"

void COdometer::motorAxisRadToWheelLineDisplace(const AxisVector& axisRad, AxisVector& lineDisp)
{
    for (int i = 0; i < _pChassis->driveWheelNum(); i++)
    {
        lineDisp[i] = axisRad[i] * _pChassis->wheelRadius(i) / _pChassis->reduceRatio();
    }
}

void COdometer::wheelLineSpeedToMotorAxisSpeed(const AxisVector& lineSpeed, AxisVector& axisSpeed)
{
    for (int i = 0; i < _pChassis->driveWheelNum(); i++)
    {
        axisSpeed[i] = lineSpeed[i] * _pChassis->reduceRatio() / _pChassis->wheelRadius(i);
    }
}

void COdometer::forwardKinematicsTrans(const AxisVector& motorAxisRad, const float steer_angle, PlanarPos& planarPos)
{
    AxisVector lineDisplacement;
    motorAxisRadToWheelLineDisplace(motorAxisRad, lineDisplacement);

    if (CChassis_base::CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO == _pChassis->type())
    {

    }
    else if (CChassis_base::CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO == _pChassis->type())
    {

    }
    else
    {

    }
}

void COdometer::forwardKinematicsTrans(const AxisVector& motorAxisRad, PlanarPos& planarPos)
{
    AxisVector lineDisplacement;
    motorAxisRadToWheelLineDisplace(motorAxisRad, lineDisplacement);

    if (CChassis_base::DOUBLE_DIFF == _pChassis->type())
    {

    }
    else if (CChassis_base::TRICYCLE == _pChassis->type())
    {

    }
    else if (CChassis_base::QUAD_MACNUM == _pChassis->type())
    {

    }
    else if (CChassis_base::QUAD_DIFF == _pChassis->type())
    {

    }
    else
    {

    }
}
//end of file
