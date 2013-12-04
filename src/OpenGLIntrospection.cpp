#include <vector>

#include <OpenGLIntrospection.hpp>

namespace RPi {

bool OpenGLIntrospection::ShaderCompilationSuccess(GLint id)
{
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    return success == GL_TRUE;
}


std::string OpenGLIntrospection::ShaderProgramInfoLog(GLint id)
{
    std::vector<char> buffer;
    std::string log = "";

    GLint length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    if(length > 1)
    {
        buffer.resize(length);
        glGetShaderInfoLog(id, length, nullptr, &buffer[0]);
        log.resize(length);
        std::copy(buffer.begin(), buffer.end(), log.begin());
    }

    return log;
}

bool OpenGLIntrospection::ProgramLinkageSuccess(GLint id)
{
    GLint success;
    glGetShaderiv(id, GL_LINK_STATUS, &success);
    return success == GL_TRUE;
}


}
