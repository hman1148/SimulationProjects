#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cfloat>

namespace models::entities
{
    class Entity
    {
    public:
        /* Destructor */
        virtual ~Entity() = default;

        /*
         * Update the entity's state
         * deltaTime: time elapsed since last update (in seconds)
         */
        virtual void Update(std::float_t deltaTime) = 0;

        /*
         * Draw the entity
         * shaderProgram: OpenGL shader program ID
         */
        virtual void Draw(GLuint shaderProgram) = 0;

        glm::vec3 m_position{0.0f};
        glm::vec3 m_velocity{0.0f};

    protected:
        // Protected so derived classes can access
        GLuint VAO = 0;
        GLuint VBO = 0;
        size_t vertexCount = 0;

        /*
         * Helper function to create VBO and VAO
         * vertices: pointer to vertex data
         * vertexCount: number of vertices
         */
        void CreateVBOVAO(const std::float_t *vertices, size_t vertexCount)
        {
            this->vertexCount = vertexCount;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(std::float_t), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(std::float_t), (void *)0);
            glEnableVertexAttribArray(0);

            glBindVertexArray(0);
        }
    };
};