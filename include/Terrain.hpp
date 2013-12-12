#ifndef RPI_TERRAIN_HPP
#define RPI_TERRAIN_HPP

#include <cstddef>

#include <glm/glm.hpp>

#include <EGLHeaders.hpp>
#include <GLSLProgram.hpp>

namespace RPi {

class Terrain
{
    using Size = std::size_t;

    public:
        Terrain() = delete;
        Terrain(Size w, Size h);
        ~Terrain();

        float getMaxHeight() const;

        void render(GLSLProgram const & program, glm::mat4 & projection,
            glm::mat4 & modelView);

    private:
        GLuint m_vbo;
        Size m_w;
        Size m_h;
        Size m_nbVertices;
        float m_minHeight;
        float m_maxHeight;
};

}

#endif //RPI_TERRAIN_HPP
