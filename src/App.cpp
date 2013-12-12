#include <chrono>
#include <iostream>

#include <App.hpp>

namespace RPi {
    
App::App(Window & window, int, char const **):
    m_window(window)
{

}

App::~App()
{

}

void App::operator()()
{
    std::cout << "App::()()" << std::endl;
    this->run();
    std::cout << "After App::()()" << std::endl;
}

void App::registerDrawFunc(Context::DrawFunc drawFunc)
{
    m_window.getContext().drawFunc = drawFunc;
}

void App::registerUpdateFunc(Context::UpdateFunc updateFunc)
{
    m_window.getContext().updateFunc = updateFunc;
}

void App::registerKeyFunc(Context::KeyFunc keyFunc)
{
    m_window.getContext().keyFunc = keyFunc;
}

void App::run()
{
    double totalTime = 0.0;
    std::size_t nbFrames = 0;
    auto quitting = false;

    auto t1 = std::chrono::high_resolution_clock::now();

    while(!m_window.userInterrupt() && !quitting)
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        auto deltaTime = static_cast<float>(std::chrono::duration_cast<
            std::chrono::microseconds>(t2 - t1).count()) / 1000.f;

        t1 = t2;

        if(m_window.getContext().updateFunc != nullptr)
        {
            m_window.getContext().updateFunc(m_window.getContext(), deltaTime);
        }

        if(m_window.getContext().drawFunc != nullptr)
        {
            m_window.getContext().drawFunc(m_window.getContext());
        }

        m_window.display();
    
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
