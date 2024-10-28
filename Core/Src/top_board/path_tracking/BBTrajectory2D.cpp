#include "BBTrajectory2D.h"


//include "utilities/Constants.h"

namespace rtt::ai::control {






BBTrajectory2D::BBTrajectory2D(const Vector2 &initialPos, const Vector2 &initialVel, const Vector2 &finalPos, double maxVel, double maxAcc) {
    generateSyncedTrajectory(initialPos, initialVel, finalPos, maxVel, maxAcc);
}
void BBTrajectory2D::generateTrajectory(const Vector2 &initialPos, const Vector2 &initialVel, const Vector2 &finalPos, double maxVel, double maxAcc, double alpha) {
    x = BBTrajectory1D(initialPos.x, initialVel.x, finalPos.x, maxVel * cos(alpha), maxAcc * cos(alpha));
    y = BBTrajectory1D(initialPos.y, initialVel.y, finalPos.y, maxVel * sin(alpha), maxAcc * sin(alpha));
}

void BBTrajectory2D::generateSyncedTrajectory(const Vector2 &initialPos, const Vector2 &initialVel, const Vector2 &finalPos, double maxVel, double maxAcc) {
    // The idea is to do a binary search over alpha to find a trajectory in x and y direction (which is minimal time)
    double inc = M_PI_4 * 0.5;
    double alpha = M_PI_4;
    constexpr double iterationLimit = 1e-7;
    constexpr double timeDiffLimit = 1e-3;
    while (inc > iterationLimit) {
        generateTrajectory(initialPos, initialVel, finalPos, maxVel, maxAcc, alpha);
        double diff = abs(x.getTotalTime() - y.getTotalTime());
        // If the trajectories match enough we stop earlier
        if (diff < timeDiffLimit) {
            return;
        }
        if (x.getTotalTime() > y.getTotalTime()) {
            alpha -= inc;
        } else {
            alpha += inc;
        }
        inc *= 0.5;
    }
}

Vector2 BBTrajectory2D::getPosition(double t) const { return Vector2(x.getPosition(t), y.getPosition(t)); }

Vector2 BBTrajectory2D::getVelocity(double t) const { return Vector2(x.getVelocity(t), y.getVelocity(t)); }

Vector2 BBTrajectory2D::getAcceleration(double t) const { return Vector2(x.getAcceleration(t), y.getAcceleration(t)); }

[[maybe_unused]] double BBTrajectory2D::getTotalTime() const { return std::max(x.getTotalTime(), y.getTotalTime()); }

std::pair<std::vector<rtt::ai::control::BBTrajectoryPart>, std::vector<rtt::ai::control::BBTrajectoryPart>> BBTrajectory2D::getParts() {
    return std::make_pair(x.getParts(), y.getParts());
}

    TrajectoryResult BBTrajectory2D::calculateTrajectoryResult(double t, double cameraYawAngle) const {
    // Get position, velocity, and acceleration at time 't'
    Vector2 position = getPosition(t);
    Vector2 velocity = getVelocity(t);
    Vector2 acceleration = getAcceleration(t);

    // Calculate magnitude of velocity (rho) and angle of movement (theta)
    float rho = velocity.length();          // Magnitude of movement
    float theta = velocity.angle();         // Direction of movement (radians)

    // Calculate absolute facing angle (yaw) based on position
    float yaw = atan2(position.y, position.x);  // Assuming yaw is derived from the position direction

    // Approximate angular velocity (rate of change of yaw)
    float angularVelocity = yaw / t;        // Simplified as yaw change over time

    // Camera yaw (input from external system)
    float cameraYaw = cameraYawAngle;

    // Calculate magnitude and angle of acceleration
    float acceleration_magnitude = acceleration.length();
    float acceleration_angle = acceleration.angle();

    // Return the calculated result as a struct
    return {rho, theta, yaw, angularVelocity, cameraYaw, acceleration_magnitude, acceleration_angle};
}



}  // namespace rtt::ai::control