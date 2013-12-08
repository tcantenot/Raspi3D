#include <Terrain.hpp>
#include <PerlinNoise.hpp>
#include <OpenGL.hpp>

#include <iostream>

namespace RPi {

Terrain::Terrain(Size w, Size h):
    m_vbo(0), m_w(w), m_h(h), m_nbVertices(w * h)
{
    PerlinNoise pn(2.5, 3.5, 5, 8, 42);

    float * vertices = new float[m_nbVertices * 3];

    for(Size j = 0; j < h; ++j)
    {
        for(Size i = 0; i < w; ++i)
        {
            std::cout << (vertices[(j * w + i) * 3 + 0] = i) << std::endl;
            std::cout << (vertices[(j * w + i) * 3 + 1] = j) << std::endl;
            std::cout << (vertices[(j * w + i) * 3 + 2] = pn.GetHeight(i, j)) << std::endl;
        }
    }

    for(Size j = 0; j < w * h * 3; ++j)
        std::cout << vertices[j] << std::endl;

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_nbVertices * 3 * sizeof(float),
        vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Terrain::~Terrain()
{

}


void Terrain::render(GLSLProgram const & program, glm::mat4 & projection, glm::mat4 & modelView)
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
        glDrawArrays(GL_LINES, 0, m_nbVertices - 1);

        //glDrawArrays(GL_LINES, 0, 36);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);



        //glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    program.unbind();
}

}
