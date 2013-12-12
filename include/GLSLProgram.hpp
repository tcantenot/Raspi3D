#ifndef RPI_GLSL_PROGRAM_HPP
#define RPI_GLSL_PROGRAM_HPP

#include <string>

#include <glm/glm.hpp>

//#include <OpenGLHeaders.hpp>
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

            int getUniformLocation(std::string const & uniform) const;

            bool isLinked() const;

            bool link();

            bool loadShaderFromFile(Enums::ShaderType type, std::string const & filename);
            bool loadShader(Enums::ShaderType type, std::string const & source);

            void sendFloat(std::string const & uniform, float f) const;
            void sendMatrix(std::string const & uniform, glm::mat4 const & matrix) const;
            void unbind() const;

        private:
            GLint m_id;
            std::string m_log;
            bool m_linked;
    };
}

#endif //RPI_GLSL_PROGRAM_HPP
