#ifndef RPI_OPENGL_HPP
#define RPI_OPENGL_HPP

#include <Enums.hpp>

namespace RPi {

    struct OpenGL
    {
        static Enums::AttribIndex const AttributeIndex[Enums::AttributeIndex_Count + 1];
        static GLenum const ShaderType[Enums::ShaderType_Count + 1];
    };
}

#endif //RPI_OPENGL_HPP
