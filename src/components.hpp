#pragma once
#include <glm/glm.hpp>

struct PositionComponent {
    glm::dvec3 position;
};

struct VelocityComponent {
    glm::dvec3 velocity;
};

struct MassComponent {
    double mass;
};
