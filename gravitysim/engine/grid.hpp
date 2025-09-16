#include "../models/entities/entity.hpp"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
    class Grid : public models::entities::Entity
    {
    public:
        GLuint VAO, VBO;
        std::size_t m_vertex_count;

        Grid(std::float_t size, int divisions);
        virtual ~Grid() noexcept = default;

        void Update(std::float_t deltaTime) override;
        void Draw(GLuint &shaderProgram) override;

        std::vector<std::float_t> CreateGridVertices(std::float_t size, int divisions);
    }
}