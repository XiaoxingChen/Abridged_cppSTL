#ifndef _CHASSIS_KINEMATICS_H_
#define _CHASSIS_KINEMATICS_H_
#include "Chassis_base.h"

void forwardKinematicsTransDiff(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float wheelbase);
void forwardKinematicsTransTricycle(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float wheelbase);
void forwardKinematicsTransMecanum(const AxisVector& wheelLineDisp, PlanarVector& deltaPos, float wheelbase);
void forwardKinematicsTransCarLikeSteerWheelOdo(const AxisVector& wheelLineDisp, float steerAngle, PlanarVector& deltaPos, float wheelbase);
void forwardKinematicsTransCarLikeFixedWheelOdo(const AxisVector& wheelLineDisp, float steerAngle, PlanarVector& deltaPos, float wheelbase);

void inverseKinematicsTransDiff(const PlanarVector& planarVel, AxisVector& wheelLineVel, float wheelbase);
void inverseKinematicsTransTricycle(const PlanarVector& planarVel, AxisVector& wheelLineVel, float wheelbase);
void inverseKinematicsTransMecanum(const PlanarVector& planarVel, AxisVector& wheelLineVel, float wheelbase);
void inverseKinematicsTransCarLikeSteerWheelDrive(const PlanarVector& planarVel, float steerAngle, AxisVector& wheelLineVel, float wheelbase);
void inverseKinematicsTransCarLikeFixedWheelDrive(const PlanarVector& planarVel, float steerAngle, AxisVector& wheelLineVel, float wheelbase);

int motorAxisVelocitySaturLimit(AxisVector& motorAxisVel, uint8_t axisNum, float motorAxisVelLimit);

#endif // !_CHASSIS_KINEMATICS_H_
