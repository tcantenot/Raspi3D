#include <cassert>
#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

#include <glm/gtx/transform.hpp>


#include <TestApp.hpp>
#include <Cube.hpp>
#include <PerspectiveCamera.hpp>
#include <Input.hpp>


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

    auto t1 = std::chrono::high_resolution_clock::now();

    PerspectiveCamera camera(70.f, 
        static_cast<float>(m_window.getWidth()) / static_cast<float>(m_window.getHeight()),
        1.f, 100.f);

    camera.position(glm::vec3(3, 3, 3));
    camera.target(glm::vec3(0, 0, 0));
    camera.up(glm::vec3(0, 1, 0));

    Input input;
    input.showMousePointer(false);
    input.grabMousePointer(true);

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

        // Quit the app with escape
        if(input.isKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            break;
        }
    
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        modelview = camera.lookAt();

        //modelview = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        projection = camera.projection();

        // Render the cube
        cube.render(*m_window.getContext().program, projection, modelview);

        // Refresh the window
        m_window.display();

        // Get FPS
        totalTime += deltaTime;
        ++nbFrames;

        if(totalTime > 1000.0f)
        {
            std::cout << nbFrames << " frames rendered in " << totalTime 
                      << " ms -> FPS = " 
                      << (static_cast<float>(nbFrames) / (totalTime / 1000.f))
                      << std::endl;

            totalTime -= 1000.0f;
            nbFrames = 0;
        }
    }
}

}
