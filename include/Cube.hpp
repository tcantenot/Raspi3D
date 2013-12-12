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

        void rotate(float angle, glm::vec3 const & axis);

        void translate(glm::vec3 const & axis);

    protected:
        float m_vertices[108];
        float m_colors[108];
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_vboIndices;
        glm::mat4 m_transform;    
};

}

#endif //RPI_CUBE_HPP
