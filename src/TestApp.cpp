#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <glm/gtx/transform.hpp>


#include <TestApp.hpp>
#include <Cube.hpp>
#include <PerspectiveCamera.hpp>
#include <Input.hpp>
#include <Terrain.hpp>
#include <Scheduler.hpp>


namespace RPi {

TestApp::TestApp(Window & window, int argc, char const ** argv): App(window, argc, argv)
{

}
        
TestApp::~TestApp()
{

}

void TestApp::run()
{
    double totalTime = 0.0;
    std::size_t nbFrames = 0;
    auto quitting = false;

    Cube cube(5);

    std::vector<Cube> cubes;

    for(int i = 0; i < 150; ++i)
    {
        cubes.emplace_back(i);                        
    }

    //std::cout << "Cube size : "

    Terrain terrain(500, 500);

    Terrain terrain2(500, 500);

    auto t1 = std::chrono::high_resolution_clock::now();

    PerspectiveCamera camera(70.f, 
        static_cast<float>(m_window.getWidth()) / static_cast<float>(m_window.getHeight()),
        1.f, 100.f);

    camera.position(glm::vec3(30, 30, 30));
    camera.target(glm::vec3(0, 0, 0));
    camera.up(glm::vec3(0, 1, 0));

    Input input;

    m_window.showMousePointer(false);
    m_window.grabMousePointer(true);

    glm::mat4 projection;
    glm::mat4 modelview;

    assert(m_window.getWidth() != 0);
    assert(m_window.getHeight() != 0);

    projection = glm::perspective(70.0, (double) m_window.getWidth() / m_window.getHeight(), 1.0, 100.0);
    modelview  = glm::mat4(1.0);

    while(!m_window.userInterrupt() && !quitting)
    {
        // Reset timer
        auto t2 = std::chrono::high_resolution_clock::now();
        auto deltaTime = static_cast<float>(std::chrono::duration_cast<
            std::chrono::microseconds>(t2 - t1).count()) / 1000.f;

        t1 = t2;

        // Get the events
        input.updateEvents();

        // Move camera
        camera.move(input);

        // Quit the app with escape
        if(input.isKeyPressed(SDLK_ESCAPE))
        {
            std::cout << "Escape key pressed" << std::endl;
            break;
        }
    
        // Clear the screen
        m_window.clear();

        modelview = camera.lookAt();

        projection = camera.projection();

        // Render the cube
        //cube.render(*m_window.getContext().program, projection, modelview);

        //for(auto & c : cubes)
        //{
            //c.render(*m_window.getContext().program, projection, modelview);
        //}

        //glViewport(0, 0, m_window.getWidth() / 2, m_window.getHeight());
        terrain.render(*m_window.getContext().program, projection, modelview);
        //glViewport(m_window.getWidth() / 2, 0, m_window.getWidth() / 2, m_window.getHeight());
        //terrain2.render(*m_window.getContext().program, projection, modelview);


        // Get FPS
        totalTime += deltaTime;
        ++nbFrames;

        if(totalTime > 1000.0f)
        {
            std::ostringstream fpsText;
            fpsText << nbFrames << " frames rendered in " << totalTime 
                      << " ms -> FPS = " 
                      << (static_cast<float>(nbFrames) / (totalTime / 1000.f));
            
            std::cout << fpsText.str() << std::endl;

            m_window.displayText("Scheduler " + Scheduler::GetSchedulerName(getpid()) + " : " + fpsText.str());

            totalTime -= 1000.0f;
            nbFrames = 0;
        }

        // Refresh the window
        m_window.display();
    }

    std::cout << "END OF LOOP" << std::endl;
}

}
