#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "components.hpp"
#include "physics_system.hpp"
#include <optional>
#include <iostream>

class SimulationSystem {
    public:
        // Main method – finds the elevation angle needed to hit the target
        static std::optional<double> findElevationAngle(
            const glm::dvec3& shooterPos, 
            const glm::dvec3& targetPos, 
            double muzzleVelocity, 
            double projectileMass,
            double timeStep,
            double angleStep = 0.5,
            int maxSteps = 10000
        ) {
            // Calculate horizontal distance and direction
            glm::dvec3 direction = targetPos - shooterPos;
            glm::dvec2 horizontal(direction.x, direction.z);
            double horizontalDistance = glm::length(horizontal);
            
            // Calculate azimuth (horizontal angle)
            double azimuth = atan2(direction.z, direction.x);
            
            std::cout << "Finding elevation angle:" << std::endl;
            std::cout << "  Shooter position: [" << shooterPos.x << ", " << shooterPos.y << ", " << shooterPos.z << "]" << std::endl;
            std::cout << "  Target position: [" << targetPos.x << ", " << targetPos.y << ", " << targetPos.z << "]" << std::endl;
            std::cout << "  Horizontal distance: " << horizontalDistance << " m" << std::endl;
            std::cout << "  Azimuth: " << glm::degrees(azimuth) << " degrees" << std::endl;
            
            // Dynamic minimum angle based on height difference
            double heightDiff = shooterPos.y - targetPos.y;
            double minElevation = (heightDiff > 1.0) ? -90.0 : 0.0;

            // Try different elevation angles
            for (double elevation = minElevation; elevation <= 90.0; elevation += angleStep) {
                std::cout << "Trying elevation angle: " << elevation << " degrees" << std::endl;
                
                // Simulate the shot with the current angle
                bool hit = simulateShot(
                    shooterPos,
                    azimuth,
                    glm::radians(elevation),  // Convert degrees to radians
                    muzzleVelocity,
                    projectileMass,
                    timeStep,
                    maxSteps,
                    targetPos
                );
                
                if (hit) {
                    std::cout << "Target hit at elevation angle: " << elevation << " degrees" << std::endl;
                    return elevation;  // Found an angle that hits the target
                }
            }
            
            std::cout << "Unable to hit the target with given parameters" << std::endl;
            return std::nullopt;  // No solution found
        }
    
    private:
        // Helper method – simulates a single shot with a given angle
        static bool simulateShot(
            const glm::dvec3& shooterPos,
            double azimuth, 
            double elevation,
            double muzzleVelocity,
            double projectileMass,
            double timeStep,
            int maxSteps,
            const glm::dvec3& targetPos
        ) {
            // Create a registry for this simulation
            entt::registry registry;
            
            // Create a projectile entity
            auto projectile = registry.create();
            
            // Add position
            registry.emplace<PositionComponent>(projectile, shooterPos);
            
            // Calculate initial velocity vector
            glm::dvec3 initialVelocity(
                muzzleVelocity * cos(elevation) * cos(azimuth),
                muzzleVelocity * sin(elevation),
                muzzleVelocity * cos(elevation) * sin(azimuth)
            );
            
            // Add velocity
            registry.emplace<VelocityComponent>(projectile, initialVelocity);
            
            // Add mass
            registry.emplace<MassComponent>(projectile, projectileMass);
            
            // Create target entity
            auto target = registry.create();
            registry.emplace<PositionComponent>(target, targetPos);
            
            // Run simulation steps
            for (int step = 0; step < maxSteps; ++step) {
                // Get current position of the projectile
                auto& projectilePos = registry.get<PositionComponent>(projectile);
                auto& targetPos = registry.get<PositionComponent>(target);
                
                // Check if the target was hit
                if (PhysicsSystem::checkHit(projectilePos, targetPos)) {
                    return true;  // Target hit
                }
                
                // Check if it hit the ground
                if (projectilePos.vector.y <= 0) {
                    return false;  // Hit the ground, target not hit
                }
                
                // Update physics
                PhysicsSystem::update(registry, timeStep);
            }
            
            return false;  // Max steps reached without hitting the target
        }
};
