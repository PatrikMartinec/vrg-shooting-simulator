#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>
#include "components.hpp"
#include "physics_system.hpp"
#include "simulation_system.hpp"

TEST_CASE("Basic trajectory calculation", "[physics]") {
    // Test 1: Simple target hit
    SECTION("Standard target hit") {
        glm::dvec3 shooterPos(0.0, 1.8, 0.0);
        glm::dvec3 targetPos(100.0, 2.0, 20.0);
        double muzzleVelocity = 100.0;
        double projectileMass = 0.01;
        double timeStep = 0.01;
        
        auto elevationAngle = SimulationSystem::findElevationAngle(
            shooterPos, targetPos, muzzleVelocity, projectileMass, timeStep);
        
        REQUIRE(elevationAngle.has_value());
        CHECK(*elevationAngle >= 2.5);
        CHECK(*elevationAngle <= 3.5);
    }
    
    // Test 2: Unreachable target
    SECTION("Unreachable target") {
        glm::dvec3 shooterPos(0.0, 1.8, 0.0);
        glm::dvec3 targetPos(1000.0, 2.0, 200.0);
        double muzzleVelocity = 50.0;
        double projectileMass = 0.01;
        double timeStep = 0.01;
        
        auto elevationAngle = SimulationSystem::findElevationAngle(
            shooterPos, targetPos, muzzleVelocity, projectileMass, timeStep);
        
        REQUIRE_FALSE(elevationAngle.has_value());
    }
    
    // Test 3: Target below shooter
    SECTION("Target below shooter") {
        glm::dvec3 shooterPos(0.0, 20.0, 0.0);
        glm::dvec3 targetPos(50.0, 1.0, 10.0);
        double muzzleVelocity = 100.0;
        double projectileMass = 0.01;
        double timeStep = 0.01;
        
        auto elevationAngle = SimulationSystem::findElevationAngle(
            shooterPos, targetPos, muzzleVelocity, projectileMass, timeStep);
        
        REQUIRE(elevationAngle.has_value());
        CHECK(*elevationAngle < 0.0);
    }
}

TEST_CASE("Physics system validation", "[physics]") {
    SECTION("Gravity affects velocity") {
        entt::registry registry;
        auto entity = registry.create();
        
        registry.emplace<PositionComponent>(entity, glm::dvec3(0.0, 10.0, 0.0));
        registry.emplace<VelocityComponent>(entity, glm::dvec3(0.0, 0.0, 0.0));
        registry.emplace<MassComponent>(entity, 1.0);
        
        // Apply gravity through the physics system
        PhysicsSystem::update(registry, 1.0);
        
        auto& velocity = registry.get<VelocityComponent>(entity);
        CHECK(velocity.vector.y == Catch::Approx(-9.81).epsilon(0.01));
    }
    
    SECTION("Position updates based on velocity") {
        entt::registry registry;
        auto entity = registry.create();
        
        registry.emplace<PositionComponent>(entity, glm::dvec3(0.0, 0.0, 0.0));
        registry.emplace<VelocityComponent>(entity, glm::dvec3(10.0, 20.0, 30.0));
        registry.emplace<MassComponent>(entity, 1.0);
        
        // Apply physics
        PhysicsSystem::update(registry, 0.5);
        
        auto& position = registry.get<PositionComponent>(entity);
        CHECK(position.vector.x == Catch::Approx(5.0).epsilon(0.01));
        CHECK(position.vector.y == Catch::Approx(10.0 - 0.5 * 9.81 * 0.5).epsilon(0.01));  // with gravity
        CHECK(position.vector.z == Catch::Approx(15.0).epsilon(0.01));
    }
}
