#include "BBTrajectory2D.h"
#include <unordered_map>
#include <optional>

class TrajectoryStorage {
public:
    // Struct to store detailed trajectory results
    struct TrajectoryResult {
        float rho;                    // Magnitude of movement (m/s)
        float theta;                  // Direction of movement (radians)
        float yaw;                    // Absolute facing angle (rad)
        float angularVelocity;        // Angular velocity (rad/s)
        float cameraYaw;              // Angle as seen by camera (rad)
        float acceleration_magnitude; // Magnitude of acceleration (m/s^2)
        float acceleration_angle;     // Angle of acceleration (rad)
    };

    // Method to calculate and store a trajectory result at time `t`
    void calculateAndStoreTrajectory(int id, const Vector2& initialPos, const Vector2& initialVel, const Vector2& finalPos, 
                                     double maxVel, double maxAcc, double cameraYaw, double t) 
    {
        // Initialize BBTrajectory2D to calculate the trajectory
        rtt::ai::control::BBTrajectory2D trajectory(initialPos, initialVel, finalPos, maxVel, maxAcc);

        // Calculate the trajectory result at time `t`
        TrajectoryResult result = trajectory.calculateTrajectoryResult(t, cameraYaw);

        // Store the trajectory result using the unique ID
        trajectories[id] = result;
    }

    // Method to retrieve a stored trajectory by ID
    std::optional<TrajectoryResult> getStoredTrajectory(int id) const {
        auto it = trajectories.find(id);
        if (it != trajectories.end()) {
            return it->second;
        }
        return std::nullopt; // Return empty if not found
    }

private:
    std::unordered_map<int, TrajectoryResult> trajectories; // Stores trajectory results by ID
};
