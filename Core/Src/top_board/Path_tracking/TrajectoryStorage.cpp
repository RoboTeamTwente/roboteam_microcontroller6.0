#include "../top_board/Path_tracking/TrajectoryStorage.h"
#include <math.h>
#include "REM_RobotCommand.h"


namespace rtt::ai::control {

void TrajectoryStorage::calculateAndStoreTrajectory(int id, const REM_RobotCommand& robotCommand, double maxVel, double maxAcc, double maxJerk) {
    // Extract current and target positions
    Vector2 currentPos{robotCommand.current_x, robotCommand.current_y};
    Vector2 targetPos{robotCommand.target_x, robotCommand.target_y};

    // Extract current velocity and yaw
    Vector2 initialVel{std::cos(robotCommand.yaw), std::sin(robotCommand.yaw)};

    // Retrieve the last acceleration for continuity (using a default or reset method in Trajectory2D)
    Vector2 initialAcc = Trajectory2D::getLastAcceleration(id);

    // Create a Trajectory2D instance
    Trajectory2D trajectory(currentPos, initialVel, initialAcc, targetPos, Vector2(0, 0), maxVel, maxAcc, maxJerk);

    // Store the calculated trajectory
    trajectories[id] = trajectory;
}

const Trajectory2D* TrajectoryStorage::getStoredTrajectory(int id) const {
    // Check if the trajectory exists for the given robot ID
    auto it = trajectories.find(id);
    if (it != trajectories.end()) {
        return &(it->second);
    }
    return nullptr; // Return nullptr if no trajectory exists
}


}; //End of namespaces




