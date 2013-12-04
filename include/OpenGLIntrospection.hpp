#ifndef RPI_OPENGL_INTROSPECTION_HPP
#define RPI_OPENGL_INTROSPECTION_HPP

#include <string>

#include <EGLHeaders.hpp>

namespace RPi {

    class OpenGLIntrospection
    {
        public:

            static bool ShaderCompilationSuccess(GLint id);
            static std::string ShaderProgramInfoLog(GLint id);
            static bool ProgramLinkageSuccess(GLint id);
    };
}

#endif //RPI_OPENGL_INTROSPECTION_HPP
