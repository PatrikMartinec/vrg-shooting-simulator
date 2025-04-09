#include <iostream>
#include <entt/entt.hpp>
#include "components.hpp"
#include "physics_system.hpp"
#include "simulation_system.hpp"

int main() {
    std::cout << "VRG Shooting Simulator started!" << std::endl;
    
    // Input parameters for the simulation
    glm::dvec3 shooterPos;
    glm::dvec3 targetPos;
    double muzzleVelocity;
    double projectileMass;
    double timeStep;
    
    // Get input parameters from the user
    std::cout << "Enter shooter position (x y z): ";
    std::cin >> shooterPos.x >> shooterPos.y >> shooterPos.z;
    
    std::cout << "Enter target position (x y z): ";
    std::cin >> targetPos.x >> targetPos.y >> targetPos.z;
    
    std::cout << "Enter muzzle velocity (m/s): ";
    std::cin >> muzzleVelocity;
    
    std::cout << "Enter projectile mass (kg): ";
    std::cin >> projectileMass;
    
    std::cout << "Enter simulation time step (s): ";
    std::cin >> timeStep;
    
    // Display input parameters
    std::cout << "\nSimulation parameters:" << std::endl;
    std::cout << "  Shooter position: [" << shooterPos.x << ", " << shooterPos.y << ", " << shooterPos.z << "]" << std::endl;
    std::cout << "  Target position: [" << targetPos.x << ", " << targetPos.y << ", " << targetPos.z << "]" << std::endl;
    std::cout << "  Muzzle velocity: " << muzzleVelocity << " m/s" << std::endl;
    std::cout << "  Projectile mass: " << projectileMass << " kg" << std::endl;
    std::cout << "  Time step: " << timeStep << " s" << std::endl;
    std::cout << "\nCalculating..." << std::endl;
    
    // Find the correct elevation angle
    auto elevationAngle = SimulationSystem::findElevationAngle(
        shooterPos,
        targetPos,
        muzzleVelocity,
        projectileMass,
        timeStep
    );
    
    // Output the result
    if (elevationAngle) {
        std::cout << "\nResult: Target can be hit with elevation angle of " << *elevationAngle << " degrees" << std::endl;
    } else {
        std::cout << "\nResult: Target cannot be hit with the given parameters." << std::endl;
    }
    
    return 0;
}
