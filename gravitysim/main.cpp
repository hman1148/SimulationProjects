#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main()
{
    std::cout << "Gravity Simulation - CMake build successful!" << std::endl;

    // Test GLFW initialization
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    std::cout << "GLFW initialized successfully" << std::endl;
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;

    // Test GLM
    glm::vec3 testVec(1.0f, 2.0f, 3.0f);
    std::cout << "GLM test vector: (" << testVec.x << ", " << testVec.y << ", " << testVec.z << ")" << std::endl;

    glfwTerminate();
    return 0;
}
