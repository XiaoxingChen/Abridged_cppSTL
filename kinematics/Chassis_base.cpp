#include "Chassis_base.h"
#include "Console.h"

CChassis_base::CChassis_base()
{
}

CChassis_base::~CChassis_base()
{
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
}