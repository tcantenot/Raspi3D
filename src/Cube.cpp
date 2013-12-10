#include <iostream>

#include <Cube.hpp>
#include <OpenGL.hpp>
//#include <OpenGLHeaders.hpp>

namespace RPi {

Cube::Cube(float size): m_vao(0), m_vbo(0), m_vboIndices(0)
{
    size /= 2;

    //float verticesTmp[] = { 1.0f,  1.0f,  1.0f, // Vertex 0 (X, Y, Z)
        //-1.0f,  1.0f,  1.0f, // Vertex 1 (X, Y, Z)
        //-1.0f, -1.0f,  1.0f, // Vertex 2 (X, Y, Z)
         //1.0f, -1.0f,  1.0f, // Vertex 3 (X, Y, Z)
         //1.0f,  1.0f, -1.0f, // Vertex 4 (X, Y, Z)
        //-1.0f,  1.0f, -1.0f, // Vertex 5 (X, Y, Z)
        //-1.0f, -1.0f, -1.0f, // Vertex 6 (X, Y, Z)
         //1.0f, -1.0f, -1.0f  // Vertex 7 (X, Y, Z)
    //};


    float verticesTmp[] = {-size, -size, -size,    size, -size, -size,   size, size, -size,     // Face 1
                       -size, -size, -size,   -size, size, -size,    size, size, -size,     // Face 1

                        size, -size, size,     size, -size, -size,   size, size, -size,     // Face 2
                        size, -size, size,     size, size, size,     size, size, -size,     // Face 2

                       -size, -size, size,     size, -size, size,    size, -size, -size,    // Face 3
                       -size, -size, size,    -size, -size, -size,   size, -size, -size,    // Face 3

                       -size, -size, size,     size, -size, size,    size, size, size,      // Face 4
                       -size, -size, size,    -size, size, size,     size, size, size,      // Face 4

                       -size, -size, -size,   -size, -size, size,   -size, size, size,      // Face 5
                       -size, -size, -size,   -size, size, -size,   -size, size, size,      // Face 5

                       -size, size, size,      size, size, size,     size, size, -size,     // Face 6
                       -size, size, size,     -size, size, -size,    size, size, -size};    // Face 6 */
//float verticesTmp[] = {-1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1
                   //-1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0,     // Face 1

                   //1.0, -1.0, 1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,       // Face 2
                   //1.0, -1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 2

                   //-1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, -1.0, -1.0,      // Face 3
                   //-1.0, -1.0, 1.0,   -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,    // Face 3

                    //-1.0, -1.0, 1.0,   1.0, -1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4
                    //-1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,   1.0, 1.0, 1.0,        // Face 4

                    //-1.0, -1.0, -1.0,   -1.0, -1.0, 1.0,   -1.0, 1.0, 1.0,     // Face 5
                    //-1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   -1.0, 1.0, 1.0,     // Face 5

                    //-1.0, 1.0, 1.0,   1.0, 1.0, 1.0,   1.0, 1.0, -1.0,         // Face 6
                    //-1.0, 1.0, 1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0};      // Face 6

    float colorsTmp[] = {1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,     // Face 1
                     1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,     // Face 1

                     0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,     // Face 2
                     0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,     // Face 2

                     0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,     // Face 3
                     0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,     // Face 3

                     1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,     // Face 4
                     1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,     // Face 4

                     0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,     // Face 5
                     0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,     // Face 5

                     0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,     // Face 6
                     0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0};    // Face 6

    for(int i = 0; i < 108; ++i)
    {
        m_vertices[i] = verticesTmp[i];
        m_colors[i]   = colorsTmp[i];
    }
    // Create Vertex Array Object
    //GLuint vao;
    //glGenVertexArrays(1, &m_vao);
    //glBindVertexArray(m_vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    //GLuint vbo;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void *>(nullptr));

    //glBindVertexArray(0);
    

    GLuint indices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };


    
    glGenBuffers(1, &m_vboIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 24 * sizeof(unsigned int), indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Cube::~Cube()
{
    //glDeleteBuffers(GL_ARRAY_BUFFER, &m_vbo);
    //glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_vboIndices);
    //glDeleteVertexArrays(1, &m_vao);
}

void Cube::render(GLSLProgram const & program, glm::mat4 & projection, glm::mat4 & modelView)
{
    program.bind();

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);

        glVertexAttribPointer(OpenGL::AttributeIndex[Enums::AttributeIndex_Position],
            3, GL_FLOAT, GL_FALSE, 0, 0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);

        program.sendMatrix("MatProjection", projection);
        program.sendMatrix("MatModelView", modelView);


        //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, static_cast<void *>(nullptr));


        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
        //glEnableVertexAttribArray(1);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        glDrawArrays(GL_LINE_STRIP, 0, 108);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);



        //glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    program.unbind();
}

}
