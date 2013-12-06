#ifndef RPI_CUBE_HPP
#define RPI_CUBE_HPP

#include <glm/glm.hpp>
//#include <
//#include <EGLHeaders.hpp>
#include <GLSLProgram.hpp>

namespace RPi {

class Cube
{
    public:
        Cube(float size);
        virtual ~Cube();

        void render(GLSLProgram const & program, glm::mat4 & projection, glm::mat4 & modelView);

    protected:
        float m_vertices[108];
        float m_colors[108];
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_vboIndices;
};

}

#endif //RPI_CUBE_HPP
