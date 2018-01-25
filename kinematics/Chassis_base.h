#ifndef _CHASSIS_BASE_H_
#define _CHASSIS_BASE_H_
#include <stdint.h>

class CChassis_base
{
public:
    enum chassisTypeEnum
    {
        UNDEFINED = 0,
        DOUBLE_DIFF = 2,
        TRICYCLE = 3,
        QUAD_DIFF = 4,
        QUAD_MACNUM = 5,
        CAR_LIKE_WHEEL_STEER_DRIVE_STEER_ODO = 6,
        CAR_LIKE_WHEEL_FIXED_DRIVE_FIXED_ODO = 7
    };

    CChassis_base();
    ~CChassis_base();

    uint8_t driveWheelNum();

    float wheelbase() { return _wheelbase; }

    float reduceRatio() { return _reduceRatio; }

    uint32_t encoderLines() { return _encoderLines; }

    float wheelRadius(uint8_t idx);

    chassisTypeEnum type() { return _type; }

    enum
    {MAX_WHEEL_NUM = 4};

private:

    float _wheelbase;

    float _reduceRatio;

    uint32_t _encoderLines;

    float _motorAxisMaxSpeed;

    float _wheelRadius[MAX_WHEEL_NUM];

    chassisTypeEnum _type;

    
};

#endif // !_CHASSIS_BASE_H_
