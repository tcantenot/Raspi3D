#ifndef RPI_ENUMS_HPP
#define RPI_ENUMS_HPP

#include <cstdint>

#include <EGLHeaders.hpp>

namespace RPi {

namespace Enums {

    using AttribIndex = uint8_t;
    enum AttributeIndex : AttribIndex
    {
        AttributeIndex_Position,
        AttributeIndex_Normal,
        AttributeIndex_Tangent,
        AttributeIndex_TexCoord,
        AttributeIndex_UserData0,
        AttributeIndex_UserData1,
        AttributeIndex_UserData2,
        AttributeIndex_UserData3,
        AttributeIndex_UserData4,
        AttributeIndex_UserData5,
        AttributeIndex_InstanceData0,
        AttributeIndex_InstanceData1,
        AttributeIndex_InstanceData2,
        AttributeIndex_InstanceData3,
        AttributeIndex_InstanceData4,
        AttributeIndex_InstanceData5,

        AttributeIndex_Count = AttributeIndex_InstanceData5
    };

    enum ShaderType
    {
        ShaderType_VertexShader,   //GL_VERTEX_SHADER
        ShaderType_FragmentShader, //GL_FRAGMENT_SHADER

        ShaderType_Count = ShaderType_FragmentShader
    };
}

}

#endif //RPI_ENUMS_HPP
