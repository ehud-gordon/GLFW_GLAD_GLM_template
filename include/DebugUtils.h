#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iomanip>
#include <limits>




// Inline debugging function
inline void printMatrix(const glm::mat4& m) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "mat4\n";
    glm::mat4 m_t = glm::transpose(m);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << std::setw(5) << m_t[i][j] << " ";
        }
        std::cout << std::setw(5) << m_t[i][3] << std::endl;
        // std::cout << m_t[i][0] << " " << m_t[i][1] << " " << m_t[i][2] << " " << m_t[i][3] << std::endl;
    }

    // Reset cout to default formatting
    std::cout.unsetf(std::ios_base::fixed);
    std::cout.precision(std::numeric_limits<std::streamsize>::max());
    // std::cout << glm::to_string(m) << std::endl;
    // std::cout << glm::to_string(glm::transpose(m)) << std::endl;
}

inline void printVec(const glm::vec3& v) {
    std::cout << glm::to_string(v) << std::endl;
}

inline void printVec(const glm::vec4& v) {
    std::cout << glm::to_string(v) << std::endl;
}
