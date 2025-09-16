#include "satellite.hpp"

/*
 * Constructor for the Satellite class
 * initPosition: initial position of the satellite
 * initVelocity: initial velocity of the satellite
 * mass: mass of the satellite
 * density: density of the satellite
 */
models::satellites::Satellite::Satellite(glm::vec3 initPosition, glm::vec3 initVelocity, float mass, float density)
    : Entity(), m_mass(mass), m_density(density)
{
    this->m_position = initPosition;
    this->m_velocity = initVelocity;
    this->m_mass = mass;
    this->m_density = density;
    UpdateRadius();

    std::vector<float> vertices = GenerateVertices();
    m_vertex_count = vertices.size();
    models::entities::Entity::CreateVBOVAO(vertices.data(), m_vertex_count * sizeof(float));
}