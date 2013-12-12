#ifndef RPI_APP_HPP
#define RPI_APP_HPP

#include <Context.hpp>
#include <Window.hpp>

namespace RPi {

    class App
    {
        public:
            App(Window & window, int argc, char const ** argv);
            virtual ~App();

            App() = delete;

            // Method called by std::thread
            void operator()();

            void registerDrawFunc(Context::DrawFunc drawFunc);
            void registerUpdateFunc(Context::UpdateFunc updateFunc);
            void registerKeyFunc(Context::KeyFunc keyFunc);

            virtual void run();

        protected:
            Window & m_window;
    };
}

#endif //RPI_APP_HPP
