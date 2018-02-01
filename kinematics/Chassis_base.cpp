#include "Chassis_base.h"
#include "Console.h"
#include <math.h>


CChassis_base::CChassis_base()
    :_wheelbase(0.5f),
    _reduceRatio(30),
    _encoderLines(1000),
    _motorAxisMaxSpeed(3000 * 2 * M_PI / 60),
    _type(DOUBLE_DIFF)
{
    float wheelRadius[2] = {0.01, 0.01};
    for (int i = 0; i < driveWheelNum(); i++)
    {
        if (0 == wheelRadius[i])
            _wheelRadius[i] = wheelRadius[0];
        else
            _wheelRadius[i] = wheelRadius[i];
    }
}

void CChassis_base::initializeParam(float wheelbase, float* wheelRadius, float reduceRatio, uint32_t encoderLines, float motorAxisMaxSpeedRpm, int chassisType)
{
    _wheelbase = wheelbase;
    _reduceRatio = reduceRatio;
    for (int i = 0; i < driveWheelNum(); i++)
    {
        if (0 == wheelRadius[i])
            _wheelRadius[i] = wheelRadius[0];
        else
            _wheelRadius[i] = wheelRadius[i];
    }
    _reduceRatio = reduceRatio;
    _encoderLines = encoderLines;
    _motorAxisMaxSpeed = motorAxisMaxSpeedRpm * 2 * M_PI / 60;
    _type = (chassisTypeEnum)chassisType;
}

CChassis_base::~CChassis_base()
{
}

void CChassis_base::setWheelRadius(float* radius)
{
    for (int i = 0; i < driveWheelNum(); i++)
    {
        _wheelRadius[i] = radius[i];
    }
}

uint8_t CChassis_base::driveWheelNum()
{
    uint8_t ret = 0;
    switch (_type)
    {
    case DOUBLE_DIFF:
    case QUAD_DIFF:
        ret = 2;
        break;

    case TRICYCLE:
        ret = 3;
        break;

    case QUAD_MACNUM:
        ret = 4;
        break;

    case CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO:
    case CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO:
        ret = 1;
        break;

    default:
        printf("Unsupport chassis type: %d\r\n", _type);
        break;
    }
    return ret;
}

float CChassis_base::wheelRadius(uint8_t idx)
{
    if (idx >= driveWheelNum())
    {
        printf("Invalid wheel index: %d, chassis type: %d\r\n", idx, _type);
        return 0.0f;
    }

    return _wheelRadius[idx];
    
}