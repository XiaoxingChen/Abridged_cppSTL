#include "ChassisKinematics.h"
#include <math.h>
#include "Console.h"

void forwardKinematicsTransDiff(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float weheelbase)
{
    deltaPos.x = (wheelLineDisp[0] + wheelLineDisp[1]) * 0.5f;
    deltaPos.y = 0.0f;
    deltaPos.theta = (wheelLineDisp[1] - wheelLineDisp[0]) / weheelbase;

    return;
}

void forwardKinematicsTransTricycle(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float wheelbase)
{

}

void forwardKinematicsTransMecanum(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float wheelbase)
{
    float param_AplusB = wheelbase / 2.0f;

    const uint8_t wheelnum = 4;

    deltaPos.x = (wheelLineDisp[0] + wheelLineDisp[1] + wheelLineDisp[2] + wheelLineDisp[3]) / 4;
    deltaPos.y = (wheelLineDisp[0] - wheelLineDisp[1] + wheelLineDisp[2] - wheelLineDisp[3]) / 4;
    deltaPos.theta = (wheelLineDisp[0] - wheelLineDisp[1] - wheelLineDisp[2] + wheelLineDisp[3]) / (4 * param_AplusB);

    return;

}

void forwardKinematicsTransCarLikeSteerWheelOdo(const AxisVector& wheelLineDisp, float steerAngle, PlanarVector& deltaPos, float wheelbase)
{
    deltaPos.x = wheelLineDisp[0] * cos(steerAngle);
    deltaPos.y = 0;
    deltaPos.theta = wheelLineDisp[0] / wheelbase * sin(steerAngle);
#if 0
    static int cnt = 0;
    if (++cnt > 100)
    {
        cnt = 0;
        printf("delta: vsdt = %fm, x = %f m, theta = %f rad\r\n",
            deltaOdoAbsAngle.carLikeDriveWheel(), planarPos.x, planarPos.theta);
    }
#endif
}

void forwardKinematicsTransCarLikeFixedWheelOdo(const AxisVector& wheelLineDisp, float steerAngle, PlanarVector& deltaPos, float wheelbase)
{

}

void inverseKinematicsTransDiff(const PlanarVector& planarVel, AxisVector& wheelLineVel, float weheelbase)
{

    const float transtionalSpeed = planarVel.x;	// m/s
    const float rotationalSpeed = planarVel.theta; // rad/s

    wheelLineVel[0] = (2 * transtionalSpeed - weheelbase * rotationalSpeed) * 0.5f;	// m/s
    wheelLineVel[1] = (2 * transtionalSpeed + weheelbase * rotationalSpeed) * 0.5f;	// m/s

    return;
}

void inverseKinematicsTransTricycle(const PlanarVector& planarVel, AxisVector& wheelLineVel, float wheelbase)
{

}

void inverseKinematicsTransMecanum(const PlanarVector& planarVel, AxisVector& wheelLineVel, float wheelbase)
{
    float param_AplusB = wheelbase / 2.0f;

    float param_w_multipled_aplusb = planarVel.theta * param_AplusB;

    //calc the line velocity of wheel
    wheelLineVel[0] = planarVel.x + planarVel.y + param_w_multipled_aplusb;
    wheelLineVel[1] = planarVel.x - planarVel.y - param_w_multipled_aplusb;
    wheelLineVel[2] = planarVel.x + planarVel.y - param_w_multipled_aplusb;
    wheelLineVel[3] = planarVel.x - planarVel.y + param_w_multipled_aplusb;
}

void inverseKinematicsTransCarLikeSteerWheelDrive(const PlanarVector& planarVel, float steerAngle, AxisVector& wheelLineVel, float wheelbase)
{
#define CMD_CHECK 1

    if (steerAngle < (M_PI / 3) && steerAngle >(M_PI / -3))
    {
        wheelLineVel[0] = planarVel.x / cos(steerAngle);
#if CMD_CHECK
        float predictOmega = wheelLineVel[0] / wheelbase * sin(steerAngle);
        if (fabs(predictOmega - planarVel.theta) > 0.1f)
        {
            printf("Dangerous! cmd: vx = %f, sa = %f, w = %f, predw = %f\r\n",
                planarVel.x, steerAngle, planarVel.theta, predictOmega);
            wheelLineVel[0] = 0;
        }

#endif
    }
    else
    {
        wheelLineVel[0] = planarVel.theta * wheelbase / sin(steerAngle);
#if CMD_CHECK
        float predictVx = wheelLineVel[0] * cos(steerAngle);
        if (fabs(predictVx - planarVel.x) > 0.1f)
        {
            printf("Dangerous! cmd: vx = %f, sa = %f, w = %f, predvx = %f\r\n",
                planarVel.x, steerAngle, planarVel.theta, predictVx);
            wheelLineVel[0] = 0;
        }
#endif
    }
}

void inverseKinematicsTransCarLikeFixedWheelDrive(const PlanarVector& planarVel, float steerAngle, AxisVector& wheelLineVel, float wheelbase)
{
    
}


int motorAxisVelocitySaturLimit(AxisVector& motorAxisVel, uint8_t axisNum, float motorAxisVelLimit)
{
    float maxAxisVel = 0;
    int axisIndex = -1;
    for (int i = 0; i < axisNum; i++)
    {
        if (fabs(motorAxisVel[i]) > motorAxisVelLimit)
        {
            maxAxisVel = motorAxisVel[i];
            axisIndex = i;
        }
    }
    if (-1 == axisIndex)
        return axisIndex;

    printf("Motor[%d] overspeed: %frad/s\r\n", axisIndex, maxAxisVel);
    float K = motorAxisVelLimit / maxAxisVel;

    for (int i = 0; i < axisNum; i++)
    {
        motorAxisVel[i] *= K;
    }
}
//end of file
