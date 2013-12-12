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

static struct Info
{
    std::string sched = "SCHED_NORMAL";
    int priority = 0;
    int x = 0;
    int y = 0;
    int w = 640;
    int h = 480;
} s_info;

void parse_args(int argc, char ** argv);

int main(int argc, char ** argv)
{
    parse_args(argc, argv);

    try {
        Scheduler::SetScheduler(getpid(), s_info.sched, s_info.priority);
    } catch(std::exception const & e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }

    std::cout << "Scheduler : " << s_info.sched << std::endl;
    std::cout << "Priority  : " << s_info.priority << std::endl;
    std::cout << "X  : " << s_info.x << std::endl;
    std::cout << "Y  : " << s_info.y << std::endl;
    std::cout << "W  : " << s_info.w << std::endl;
    std::cout << "H  : " << s_info.h << std::endl;

    //Scheduler::SetScheduler(getpid(), SchedulerType::RoundRobin, 85);

    std::cout << Scheduler::GetSchedulerName(getpid()) << std::endl;

    //EGLIntrospection::Initialize();

    //std::cout << "Version : " << EGLIntrospection::GetVersion() << std::endl;
    //std::cout << EGLIntrospection::GetConfig() << std::endl;

    Context context;

    RPi::Window window(context, "First App", s_info.x, s_info.y, s_info.w, s_info.h);

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

    while((c = getopt(argc, argv, "s:p:x:y:w:h:")) != -1)
    {
        switch(c)
        {
            case 's':
                s_info.sched = optarg;
                break;
            case 'p':
                s_info.priority = Utils::Number<decltype(s_info.priority)>(optarg);
                break;
            case 'x': 
                s_info.x = Utils::Number<decltype(s_info.x)>(optarg);
                break;
            case 'y': 
                s_info.y = Utils::Number<decltype(s_info.y)>(optarg);
                break;
            case 'w': 
                s_info.w = Utils::Number<decltype(s_info.w)>(optarg);
                break;
            case 'h': 
                s_info.h = Utils::Number<decltype(s_info.h)>(optarg);
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
