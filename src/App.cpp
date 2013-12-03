#include <chrono>
#include <iostream>

#include <App.hpp>

namespace RPi {
    
App::App(Window & window, int, char const **): m_window(window)
{

}

App::~App()
{

}


void App::registerDrawFunc(DrawFunc drawFunc)
{
    m_drawFunc = drawFunc;
}

void App::registerUpdateFunc(UpdateFunc updateFunc)
{
    m_updateFunc = updateFunc;
}

void App::registerKeyFunc(KeyFunc keyFunc)
{
    m_keyFunc = keyFunc;
}

void App::run()
{
    double totalTime = 0.0;
    std::size_t nbFrames = 0;
    auto running = true;

    auto t1 = std::chrono::high_resolution_clock::now();

    while(running)
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration_cast<
            std::chrono::microseconds>(t2 - t1).count() / 1000.f;

        t1 = t2;

        if(m_updateFunc != nullptr)
        {
            m_updateFunc(m_window.getContext(), deltaTime);
        }

        if(m_drawFunc != nullptr)
        {
            m_drawFunc(m_window.getContext());
        }

        m_window.display();
    
        totalTime += deltaTime;
        ++nbFrames;

        if(totalTime > 1.0f)
        {
            std::cout << nbFrames << " frames rendered in " << totalTime << " ms -> FPS = "
                      << (nbFrames / totalTime / 1000.0) << std::endl;
            totalTime -= 1.0f;
            nbFrames = 0;
        }
    }
}

}
