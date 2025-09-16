#include "satellite.hpp"
#include <cmath>
#include <memory>

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

    auto vertices = this->GenerateVertices();
    m_vertex_count = vertices.size();
    models::entities::Entity::CreateVBOVAO(vertices.data(), m_vertex_count * sizeof(float));
}

/*
 * Update the satellite's state
 * deltaTime: time elapsed since last update (in seconds)
 */
void models::satellites::Satellite::Update(float deltaTime)
{
    this->m_position += this->m_velocity * deltaTime;

    this->UpdateRadius();
    this->UpdateVertices();
}

/*
 * Draw the satellite
 * shaderProgram: OpenGL shader program ID
 */
void models::satellites::Satellite::Draw(GLuint &shaderProgram)
{
    glUniform4f(glGetUniformLocation(shaderProgram, "objectColor"), this->m_color.r, this->m_color.g, this->m_color.b, this->m_color.a);
    auto model = glm::translate(glm::mat4(1.0f), this->m_position);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount / 3);
}

/*
 * Update the satellite's radius based on its mass and density
 */
void models::satellites::Satellite::UpdateRadius()
{
    this->m_radius = std::pow((3.0f * this->m_mass / this->m_density) / (4.0f * 3.14159265359f), 1.0f / 3.0f) / 100000.0f;
}

/*
 * Generate vertices for the satellite's sphere representation
 * Returns a vector of vertex positions
 */
std::vector<std::float_t> &models::satellites::Satellite::GenerateVertices()
{
    auto vertices = std::make_shared<std::vector<std::float_t>>();
    int stacks = 10, sectors = 10;

    for (int i = 0; i <= stacks; ++i)
    {
        std::float_t theta1 = static_cast<std::float_t>((i / float(stacks)) * glm::pi<float>());
        std::float_t theta2 = static_cast<std::float_t>(((i + 1) / float(stacks)) * glm::pi<float>());

        for (int j = 0; j < sectors; ++j)
        {
            std::float_t phi1 = static_cast<std::float_t>((j / float(sectors)) * 2.0f * glm::pi<float>());
            std::float_t phi2 = static_cast<std::float_t>(((j + 1) / float(sectors)) * 2.0f * glm::pi<float>());

            glm::vec3 v1 = models::entities::Entity::sphericalToCartesian(this->m_radius, theta1, phi1);
            glm::vec3 v2 = models::entities::Entity::sphericalToCartesian(this->m_radius, theta1, phi2);
            glm::vec3 v3 = models::entities::Entity::sphericalToCartesian(this->m_radius, theta2, phi1);
            glm::vec3 v4 = models::entities::Entity::sphericalToCartesian(this->m_radius, theta2, phi2);

            vertices->insert(vertices->end(), {v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z});
            vertices->insert(vertices->end(), {v2.x, v2.y, v2.z, v4.x, v4.y, v4.z, v3.x, v3.y, v3.z});
        }
    }
    return *vertices;
}

/**
 * Update the vertex buffer with new vertices based on the current radius
 */
void models::satellites::Satellite::UpdateVertices()
{
    auto vertices = this->GenerateVertices();
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::float_t), vertices.data(), GL_STATIC_DRAW);
}