#pragma once
#include <glm/glm.hpp>

struct PositionComponent {
    glm::dvec3 vector;
};

struct VelocityComponent {
    glm::dvec3 vector;
};

struct MassComponent {
    double mass;
};
