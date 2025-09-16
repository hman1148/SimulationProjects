#include "grid.hpp"

engine::Grid::Grid(std::float_t size, int divisions)
{
    auto vertices = this->CreateGridVertices(size, divisions);
}

std::vector<std::float_t> engine::Grid::CreateGridVertices(std::float_t size, int divisions)
{
    std::vector<std::float_t> vertices;
    std::float_t half = size / 2.0f;
    std::float_t step = size / divisions;

    for (int i = 0; i <= divisions; ++i)
    {
        std::float_t pos = -half + i * step;

        vertices.insert(vertices.end(), {pos, 0.0f, -half, pos, 0.0f, half});
        vertices.insert(vertices.end(), {-half, 0.0f, pos, half, 0.0f, pos});
    }
    return vertices;
}
