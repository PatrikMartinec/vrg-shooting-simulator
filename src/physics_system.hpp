#pragma once

#include <iostream>
#include <entt/entt.hpp>
#include "components.hpp"

class PhysicsSystem {
private:
    // Gravitational acceleration constant
    static constexpr double GRAVITY = 9.81;  // m/s^2

public:
    static void update(entt::registry& registry, double deltaTime) {
        // Get a view of all entities with the required components
        auto view = registry.view<PositionComponent, VelocityComponent, MassComponent>();
        
        // Update each entity
        for (auto entity : view) {
            auto& position = view.get<PositionComponent>(entity);
            auto& velocity = view.get<VelocityComponent>(entity);
            
            // Print current state
            std::cout << "Entity " << static_cast<uint32_t>(entity) 
                      << " - Position: [" << position.vector.x << ", " 
                      << position.vector.y << ", " << position.vector.z << "]"
                      << " - Velocity: [" << velocity.vector.x << ", " 
                      << velocity.vector.y << ", " << velocity.vector.z << "]" << std::endl;

            // Apply gravity
            velocity.vector.y -= GRAVITY * deltaTime;
            
            // Update position
            position.vector += velocity.vector * deltaTime;
        }
    }
    
    // Check if projectile hit the target
    static bool checkHit(const PositionComponent& projectile, const PositionComponent& target, double hitThreshold = 0.5) {
        double distance = glm::distance(projectile.vector, target.vector);

        // Print hit check information
        std::cout << "Hit check - Distance: " << distance 
                  << " - Threshold: " << hitThreshold
                  << " - Result: " << (distance < hitThreshold ? "HIT" : "MISS") << std::endl;

        return distance < hitThreshold;
    }
};