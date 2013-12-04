#ifndef RPI_GLSL_PROGRAM_HPP
#define RPI_GLSL_PROGRAM_HPP

#include <string>

#include <EGLHeaders.hpp>
#include <Enums.hpp>

namespace RPi {

    class GLSLProgram
    {
        public:
            GLSLProgram();
            ~GLSLProgram();

            void bind() const;

            std::string const & getLog() const;

            bool isLinked() const;

            bool link();

            bool loadShaderFromFile(Enums::ShaderType type, std::string const & filename);
            bool loadShader(Enums::ShaderType type, std::string const & source);

            void unbind() const;

        private:
            GLint m_id;
            std::string m_log;
            bool m_linked;
    };
}

#endif //RPI_GLSL_PROGRAM_HPP
