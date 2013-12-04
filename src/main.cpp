#include <iostream>
#include <stdlib.h>


#include <App.hpp>
#include <Context.hpp>
#include <EGLIntrospection.hpp>
#include <GLSLProgram.hpp>
#include <OpenGL.hpp>
#include <Window.hpp>


using namespace RPi;

void Draw(Context & context)
{
   //UserData *userData = esContext->userData;
   GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f, 
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };
      
   // Set the viewport
   glViewport(0, 0, context.width, context.height);
   
   // Clear the color buffer
   glClear(GL_COLOR_BUFFER_BIT);

   // Use the program object
   context.program->bind();

   // Load the vertex data
   glVertexAttribPointer(OpenGL::AttributeIndex[Enums::AttributeIndex_Position],
        3, GL_FLOAT, GL_FALSE, 0, vVertices);

   glEnableVertexAttribArray(0);

   glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char const ** argv)
{
    //EGLIntrospection::Initialize();

    //std::cout << "Version : " << EGLIntrospection::GetVersion() << std::endl;
    //std::cout << EGLIntrospection::GetConfig() << std::endl;

    //char const vShaderStr[] =  
        //"attribute vec4 VertexPosition;   \n"
        //"void main()                      \n"
        //"{                                \n"
        //"   gl_Position = VertexPosition; \n"
        //"}                                \n";

    //char const fShaderStr[] =  
        //"precision mediump float;\n"\
        //"void main()                                \n"
        //"{                                          \n"
        //"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
        //"}                                          \n";

    Context context;

    RPi::Window window(context, "First App", 640, 480);

    GLSLProgram program;
    context.program = &program;
    program.loadShaderFromFile(Enums::ShaderType_VertexShader, "./shaders/shader.vs");
    program.loadShaderFromFile(Enums::ShaderType_FragmentShader, "./shaders/shader.fs");
    std::cout << program.getLog() << std::endl;
    program.link();

    window.init();

    App app(window, argc, argv);

    app.registerDrawFunc(Draw);

    app.run();

    return 0;
}

