#include <iostream>
#include <cstdlib>
#include <thread>

#include <SDL/SDL.h>
#include <glm/gtx/transform.hpp>

#include <App.hpp>
#include <TestApp.hpp>
#include <Context.hpp>
#include <EGLIntrospection.hpp>
#include <GLSLProgram.hpp>
#include <OpenGL.hpp>
#include <Window.hpp>
#include <Utils.hpp>

#include <PerlinNoise.hpp>
#include <Scheduler.hpp>

#include <sys/types.h>
#include <unistd.h>

using namespace RPi;


void Draw(Context & context);

/*int main(int argc, char*argv[])*/
//{
        //// initing the SDL stuff
        //SDL_Surface *screen;

    //if((SDL_Init(SDL_INIT_VIDEO)==-1)) { 
        //printf("Could not initialize SDL: %s.\n", SDL_GetError());
        //exit(-1);
    //}
        //atexit(SDL_Quit);

    //SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
        //SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    //SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //screen = SDL_SetVideoMode(800, 800, 8, SDL_HWSURFACE);
    //if ( screen == NULL ) {
        //fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        //exit(1);
    //}

    ////auto context = SDL_GL_CreateContext(screen);

    ////if(context == nullptr)
    ////{
        ////std::cerr << SDL_GetError() << std::endl;
        ////SDL_Quit();
        ////return false;
    ////}

    //GLSLProgram program;
    //program.loadShaderFromFile(Enums::ShaderType_VertexShader, "./shaders/shader.vs");
    //program.loadShaderFromFile(Enums::ShaderType_FragmentShader, "./shaders/shader.fs");
    //std::cout << program.getLog() << std::endl;
    //program.link();

        ////initOGL();
        ////texture1 = LoadTexture("plasma2.bmp");        

        //while(1)
        //{
                //SDL_Event event;
                //while (SDL_PollEvent(&event)) {
                        //switch(event.type){
                                //case SDL_QUIT:
                                        //SDL_Quit();
                                        //exit(0);
                                        //break;
                        //}
                //}
                
                ////render();
                //SDL_GL_SwapBuffers();
        //}

        //return 0;
/*}*/

void parse_args(int argc, char ** argv);

int main(int argc, char ** argv)
{
    parse_args(argc, argv);

    //Scheduler::SetScheduler(getpid(), SchedulerType::RoundRobin, 85);

    std::cout << Scheduler::GetSchedulerName(getpid()) << std::endl;

    //EGLIntrospection::Initialize();

    //std::cout << "Version : " << EGLIntrospection::GetVersion() << std::endl;
    //std::cout << EGLIntrospection::GetConfig() << std::endl;

    Context context;

    RPi::Window window(context, "First App", 640, 480);

    std::cout << "Window created" << std::endl;

    GLSLProgram program;
    context.program = &program;
    program.loadShaderFromFile(Enums::ShaderType_VertexShader, "./shaders/shader.vs");
    std::cout << program.getLog() << std::endl;
    program.loadShaderFromFile(Enums::ShaderType_FragmentShader, "./shaders/shader.fs");
    std::cout << program.getLog() << std::endl;
    program.link();
    std::cout << program.getLog() << std::endl;

    window.init();

    TestApp app(window, argc, argv);

    app.registerDrawFunc(Draw);

    app.run();

    //std::cout << "Creating thread" << std::endl;
    //std::thread t(app);
    //std::cout << "Thread created" << std::endl;
    //t.join();

    std::cout << "THIS IS THE END" << std::endl;

    return 0;
}

void parse_args(int argc, char ** argv)
{
    int c;
    std::string scheduler = "default";
    int priority = -1;

    while((c = getopt(argc, argv, "s:p:")) != -1)
    {
        switch(c)
        {
            case 's':
                scheduler = optarg;
                break;
            case 'p':
                priority = Utils::Number<decltype(priority)>(optarg);
                break;
            case '?':
                if(optopt == 's')
                    fprintf (stderr, "Option -%c requires a scheduler name.\n", optopt);
                else if(optopt == 'p')
                    fprintf (stderr, "Option -%c requires a priority.\n", optopt);
                else if(isprint(optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                exit(1);
            default:
                exit(2);
        }
    }

    try {
        Scheduler::SetScheduler(getpid(), scheduler, priority);
    } catch(std::exception const & e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }

    std::cout << "Scheduler : " << scheduler << std::endl;
    std::cout << "Priority  : " << priority << std::endl;
}


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
