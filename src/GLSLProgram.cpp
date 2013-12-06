#include <array>
#include <iostream>
#include <fstream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include <GLSLProgram.hpp>
#include <OpenGL.hpp>
#include <OpenGLIntrospection.hpp>


namespace RPi {

namespace {

    using namespace Enums;

    std::string get_file_content(std::string const & filename)
    {
        std::ifstream file(filename, std::ifstream::in);

        if(!file)
        {
            std::cerr << "Failed to open file \""
                      << filename << "\"" << std::endl;
            return "";
        }

        // Get file length
        file.seekg(0, std::ifstream::end);
        std::size_t length = file.tellg(); 
        file.seekg(0, std::ifstream::beg);

        // Put the content of the file in a buffer
        std::vector<char> buffer;
        buffer.resize(length);
        file.read(&buffer[0], length);


        // Copy the buffer into a std::string
        std::string content;
        content.resize(length);
        std::copy(buffer.begin(), buffer.end(), content.begin());

        return content;
    }

    struct LocationBinding
    {
        LocationBinding(GLint index, GLchar const * name):
            index(index), name(name)
        {

        }

        GLuint index;
        GLchar const * name;
    };

    std::array<LocationBinding, AttributeIndex_Count+1> s_locationBindings =
    {{
        {OpenGL::AttributeIndex[AttributeIndex_Position],  "VertexPosition"},
        {OpenGL::AttributeIndex[AttributeIndex_Normal],    "VertexNormal"  },
        {OpenGL::AttributeIndex[AttributeIndex_Tangent],   "VertexTangent" },
        {OpenGL::AttributeIndex[AttributeIndex_TexCoord],  "VertexTexCoord"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData0], "VertexUserData0"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData1], "VertexUserData1"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData2], "VertexUserData2"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData3], "VertexUserData3"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData4], "VertexUserData4"},
        {OpenGL::AttributeIndex[AttributeIndex_UserData5], "VertexUserData5"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData0], "InstanceData0"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData1], "InstanceData1"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData2], "InstanceData2"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData3], "InstanceData3"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData4], "InstanceData4"},
        {OpenGL::AttributeIndex[AttributeIndex_InstanceData5], "InstanceData5"}
     }};
}


GLSLProgram::GLSLProgram(): m_id(0), m_log(""), m_linked(false)
{
    m_id = glCreateProgram();

    if(m_id == 0)
    {
        std::cerr << "GLSLProgram::GLSLProgram : Failed to create program" << std::endl;
        return;
    }

    // Force the association of the generic vertex attribute indices
    // with a named attribute variable
    for(auto const & lb : s_locationBindings)
    {
        glBindAttribLocation(m_id, lb.index, lb.name);
    }
}

GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(m_id);    
}

void GLSLProgram::bind() const
{
    glUseProgram(m_id);
}


std::string const & GLSLProgram::getLog() const
{
    return m_log;
}

int GLSLProgram::getUniformLocation(std::string const & uniform) const
{
    return glGetUniformLocation(m_id, uniform.c_str());
}


bool GLSLProgram::isLinked() const
{
    return m_linked;
}

bool GLSLProgram::link()
{
    glLinkProgram(m_id);

    GLenum glError = glGetError();
    if(glError != GL_NO_ERROR) 
    {
        fprintf(stderr, "glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__);
        exit(1);
    }

    return true;

    //if(OpenGLIntrospection::ProgramLinkageSuccess(m_id))
    //{
        //m_log = "Linkage successful";
        //return true;
    //}
    //else
    //{
        //m_log = OpenGLIntrospection::ShaderProgramInfoLog(m_id);

        //if(m_log.length() > 1)
        //{
            //m_log = "Linkage error : " + m_log;
        //}
        //else
        //{
            //m_log = "Linkage failed and no info log found";
        //}

        //std::cerr << "GLSLProgram::link : " + m_log << std::endl;

        //glDeleteProgram(m_id);

        //return false;
    //}
}

bool GLSLProgram::loadShaderFromFile(Enums::ShaderType type, std::string const & filename)
{
    return this->loadShader(type, get_file_content(filename));
}

bool GLSLProgram::loadShader(Enums::ShaderType type, std::string const & source)
{
    GLuint shader = glCreateShader(OpenGL::ShaderType[type]);

    if(shader == 0)
    {
        std::cerr << "GLSLProgram::loadShader : Failed to create shader" << std::endl;
        return false;
    }

    auto buffer = source.c_str();
    auto const length = static_cast<GLint>(source.length());

    glShaderSource(shader, 1, &buffer, &length);

    glCompileShader(shader);

    bool success = false;

    if(OpenGLIntrospection::ShaderCompilationSuccess(shader))
    {
        //Attach the new shader to the program
        glAttachShader(m_id, shader);

        //Flag the new shader for deletion
        //(when program is destroyed -> glDeleteProgram)
        //glDeleteShader(shader);

        m_log = "Compilation successful";

        success = true;
    }
    else
    {
        m_log = OpenGLIntrospection::ShaderProgramInfoLog(shader);

        if(m_log.length() > 1)
        {
            m_log = "Compilation error : " + m_log;
        }
        else
        {
            m_log = "Compilation failed and no info log found";
        }

        std::cerr << "GLSLProgram::loadShader : " + m_log << std::endl;

        glDeleteShader(shader);

        success = false;
    }

    return success;
}

void GLSLProgram::sendMatrix(std::string const & uniform, glm::mat4 const & matrix) const
{
    this->bind();
    auto location = this->getUniformLocation(uniform);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}



void GLSLProgram::unbind() const
{
    glUseProgram(0);
}

}
