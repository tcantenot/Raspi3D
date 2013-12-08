#include <iostream>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <glm/gtx/transform.hpp>

#include <App.hpp>
#include <TestApp.hpp>
#include <Context.hpp>
#include <EGLIntrospection.hpp>
#include <GLSLProgram.hpp>
#include <OpenGL.hpp>
#include <Window.hpp>

#include <PerlinNoise.hpp>

using namespace RPi;



void Draw(Context & context)
{
   //UserData *userData = esContext->userData;
   GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f, 
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };
    
    glm::mat4 projection;
    glm::mat4 modelview;

    assert(context.width != 0);
    assert(context.height != 0);

    projection = glm::perspective(70.0, (double) context.width / context.height, 1.0, 100.0);
    modelview  = glm::mat4(1.0);


   GLuint m_vbo;

    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
     
   // Set the viewport
   glViewport(0, 0, context.width, context.height);
   
   // Clear the color buffer
   glClear(GL_COLOR_BUFFER_BIT);

   // Use the program object
   context.program->bind();
        context.program->sendMatrix("MatProjection", projection);
        context.program->sendMatrix("MatModelView", modelview);

   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
   // Load the vertex data
   glVertexAttribPointer(OpenGL::AttributeIndex[Enums::AttributeIndex_Position],
        3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char const ** argv)
{
    //EGLIntrospection::Initialize();

    //std::cout << "Version : " << EGLIntrospection::GetVersion() << std::endl;
    //std::cout << EGLIntrospection::GetConfig() << std::endl;

    Context context;

    RPi::Window window(context, "First App", 640, 480);

    std::cout << "Window created" << std::endl;

    GLSLProgram program;
    context.program = &program;
    program.loadShaderFromFile(Enums::ShaderType_VertexShader, "./shaders/shader.vs");
    program.loadShaderFromFile(Enums::ShaderType_FragmentShader, "./shaders/shader.fs");
    std::cout << program.getLog() << std::endl;
    program.link();

    window.init();

    TestApp app(window, argc, argv);

    app.registerDrawFunc(Draw);

    app.run();

    std::cout << "After run" << std::endl;

    PerlinNoise pn(2.5, 3.5, 10.5, 8, 42);

    for(int i = 0; i < 43; ++i)
    {
        std::cout << pn.GetHeight(i, i+1) << std::endl;
    }

    return 0;
}

//int main(int argc, char *argv[])
//{
    //SDL_Surface* drawContext;
    //Uint32 flags;

    //if(SDL_Init(SDL_INIT_VIDEO) != 0)
    //{
        //std::cerr << "SDL_Init failed" << std::endl;
    //}

    //if(SDL_SetVideoMode(0, 0, 0, SDL_SWSURFACE | SDL_FULLSCREEN) == nullptr)
    //{
        //std::cerr << "SDL_SetVideoMode failed" << std::endl;
    //}

    //SDL_GL_SwapBuffers();

    //for(;;);

    //[> Clear our buffer with a red background <]
    //glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    //glClear ( GL_COLOR_BUFFER_BIT );
    //[> Swap our back buffer to the front <]
    //SDL_GL_SwapWindow(mainwindow);
    //[> Wait 2 seconds <]
    //SDL_Delay(2000);
 
    //[> Same as above, but green <]
    //glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    //glClear ( GL_COLOR_BUFFER_BIT );
    //SDL_GL_SwapWindow(mainwindow);
    //SDL_Delay(2000);
 
    //[> Same as above, but blue <]
    //glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    //glClear ( GL_COLOR_BUFFER_BIT );
    //SDL_GL_SwapWindow(mainwindow);
    //SDL_Delay(2000);
 
    //[> Delete our opengl context, destroy our window, and shutdown SDL <]
    //SDL_GL_DeleteContext(maincontext);
    //SDL_DestroyWindow(mainwindow);
    //SDL_Quit();
 
    //return 0;
//}


