#include <OpenGL.hpp>

namespace RPi {

Enums::AttribIndex const OpenGL::AttributeIndex[Enums::AttributeIndex_Count + 1] =
{
    0,  //AttributeIndex_Position
    1,  //AttributeIndex_Normal
    2,  //AttributeIndex_Tangent
    3,  //AttributeIndex_TexCoord
    4,  //AttributeIndex_UserData0
    5,  //AttributeIndex_UserData1
    6,  //AttributeIndex_UserData2
    7,  //AttributeIndex_UserData3
    8,  //AttributeIndex_UserData4
    9,  //AttributeIndex_UserData5
    10, //AttributeIndex_InstanceData0
    11, //AttributeIndex_InstanceData1
    12, //AttributeIndex_InstanceData2
    13, //AttributeIndex_InstanceData3
    14, //AttributeIndex_InstanceData4
    15  //AttributeIndex_InstanceData5
};


GLenum const OpenGL::ShaderType[Enums::ShaderType_Count + 1] =
{
    GL_VERTEX_SHADER,   //ShaderType_VertexShader
    GL_FRAGMENT_SHADER //ShaderType_FragmentShader
};


}
