#pragma once

#include "../entities/entity.hpp"

#include <vector>

namespace models::satellites
{
    class Satellite : public models::entities::Entity
    {
    public:
        GLuint VAO, VBO;
        std::size_t m_vertex_count;

        glm::vec4 m_color{1.0f, 0.0f, 0.0f, 1.0f};

        std::float_t m_mass;
        std::float_t m_density;
        std::float_t m_radius;

        bool m_initializing = false;
        bool m_launch = false;

        Satellite(glm::vec3 initPosition, glm::vec3 initVelocity, float mass, float density = 3344.0f);

        void Update(std::float_t deltaTime) override;
        void Draw(GLuint shaderProgram) override;

    private:
        void UpdateRadius();
        std::vector<std::float_t> GenerateVertices();
        void UpdateVertices();
    };
}