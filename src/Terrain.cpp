#include <Terrain.hpp>
#include <PerlinNoise.hpp>
#include <OpenGL.hpp>

#include <iostream>
#include <vector>

namespace RPi {

namespace {

inline double findnoise2(double x,double y)
{
    int n=(int)x+(int)y*57;
    n=(n<<13)^n;
    int nn=(n*(n*n*60493+19990303)+1376312589)&0x7fffffff;
    return 1.0-((double)nn/1073741824.0);
}

inline double interpolate(double a,double b,double x)
{
    double ft = x * 3.1415927;
    double f = (1.0 - std::cos(ft))* 0.5;
    return a*(1.0-f)+b*f;
}

inline double noise(double x, double y)
{
    double floorx = (double) ((int) x);
    double floory = (double) ((int) y);

    double s,t,u,v;//Integer declaration
    s=findnoise2(floorx,floory);
    t=findnoise2(floorx+1,floory);
    u=findnoise2(floorx,floory+1);//Get the surrounding pixels to calculate the transition.
    v=findnoise2(floorx+1,floory+1);
    double int1=interpolate(s,t,x-floorx);//Interpolate between the values.
    double int2=interpolate(u,v,x-floorx);//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
    return interpolate(int1,int2,y-floory);//Here we use y-floory, to get the 2nd dimension.
}

}

Terrain::Terrain(Size w, Size h):
    m_vbo(0), m_w(w), m_h(h), m_nbVertices(w * h)
{
    PerlinNoise pn(2.5, 30, 5, 8, 42);

    std::vector<float> vertices;

    bool p = false;

    float step = 0.1f;

    for(float i = 0.f; i < w; i += step)
    {
        p = !p;

        for(float j = 0.f; j < h; j += step)
        {
            auto idxJ = p ? j : h - j;
            auto nextJ = idxJ + (p ? step : -step);

            vertices.push_back(i)     ; vertices.push_back(noise(i,      idxJ) ); vertices.push_back(idxJ) ;
            vertices.push_back(i)     ; vertices.push_back(noise(i,      nextJ)); vertices.push_back(nextJ);
            vertices.push_back(i+step); vertices.push_back(noise(i+step, idxJ) ); vertices.push_back(idxJ) ;
            vertices.push_back(i+step); vertices.push_back(noise(i+step, nextJ)); vertices.push_back(nextJ);
        }
    }

    m_nbVertices = vertices.size() / 3;

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_nbVertices * 3 * sizeof(float),
        &vertices[0], GL_STATIC_DRAW);
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
        glDrawArrays(GL_LINE_STRIP, 0, m_nbVertices - 1);

        //glDrawArrays(GL_LINES, 0, 36);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);



        //glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    program.unbind();
}

}
