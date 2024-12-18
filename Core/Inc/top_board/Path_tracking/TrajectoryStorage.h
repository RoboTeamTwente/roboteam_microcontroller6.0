#ifndef TRAJECTORY_STORAGE_H
#define TRAJECTORY_STORAGE_H

#include "Trajectory2D.h"
#include "REM_RobotCommand.h"
#include "Vector2.h"
#include <unordered_map>
#include <optional>



namespace rtt::ai::control {

struct some_const {

        double currentVel = 0.0;   /**< Current velocity of the robot */
        double targetVel = 1.5;    /**< Target velocity of the robot */
        double maxVel = 5.0;       /**< Maximum allowed velocity */
        double maxAcc = 2.0;       /**< Maximum allowed acceleration */
        double maxJerk = 2.0;  

};



/**
 * @brief Class that manages and stores trajectories for multiple robots
 */
class TrajectoryStorage {
   public:
    /**
     * @brief Calculates and stores a trajectory for a specific robot
     * @param id Unique robot identifier
     * @param robotCommand Robot command containing current and target positions, velocity, etc.
     * @param maxVel Maximum velocity
     * @param maxAcc Maximum acceleration
     * @param maxJerk Maximum jerk
     */
    void calculateAndStoreTrajectory(int id, const REM_RobotCommand& robotCommand, double maxVel, double maxAcc, double maxJerk);

    /**
     * @brief Retrieves a stored trajectory for a specific robot
     * @param id Unique robot identifier
     * @return Pointer to the stored trajectory, or nullptr if not found
     */
    [[nodiscard]] const Trajectory2D* getStoredTrajectory(int id) const;

   private:
    std::unordered_map<int, Trajectory2D> trajectories; /**< Map of stored trajectories by robot ID */
};

}  // namespace rtt::ai::control

#endif  // RTT_TRAJECTORYSTORAGE_H
