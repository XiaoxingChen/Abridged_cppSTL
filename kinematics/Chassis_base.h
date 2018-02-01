#ifndef _CHASSIS_BASE_H_
#define _CHASSIS_BASE_H_
#include <stdint.h>

struct PlanarVector {
    float x;
    float y;
    float theta;
    float& at(uint8_t idx)
    {
        if (0 == idx)
            return x;
        else if (1 == idx)
            return y;
        else if (2 == idx)
            return theta;
        else
            return x;//TODO
    }

    const float& at(uint8_t idx) const
    {
        if (0 == idx)
            return x;
        else if (1 == idx)
            return y;
        else if (2 == idx)
            return theta;
        else
            return 0.0f;
    }

    void reset()
    {
        for (int i = 0; i < 3; i++)
            at(i) = 0;
    }
};

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

    void initializeParam(float wheelbase, float* wheelRadius, float reduceRatio, uint32_t encoderLines, float motorAxisMaxSpeedRpm, int chassisType);

    void initializeParam(uint8_t* msg, uint16_t len);

    uint8_t driveWheelNum();

    float wheelbase() { return _wheelbase; }

    float reduceRatio() { return _reduceRatio; }

    uint32_t encoderLines() { return _encoderLines; }

    float wheelRadius(uint8_t idx);

    chassisTypeEnum type() { return _type; }

    void setWheelRadius(float* radius);

    void setAccLimit(const PlanarVector& accLimit) { _accLimit = accLimit; }

    const PlanarVector& accLimit() { return _accLimit; }

    enum { MAX_WHEEL_NUM = 4 };

    float motorAxisMaxSpeed() { return _motorAxisMaxSpeed; }

private:

    float _wheelbase;

    float _reduceRatio;

    uint32_t _encoderLines;

    float _motorAxisMaxSpeed;

    float _wheelRadius[MAX_WHEEL_NUM];

    chassisTypeEnum _type;

    PlanarVector _accLimit;
};

typedef float AxisVector[CChassis_base::MAX_WHEEL_NUM];

#endif // !_CHASSIS_BASE_H_
