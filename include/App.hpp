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
            App(App const &) = delete;
            App(App &&) = delete;

            App & operator=(App const &) = delete;
            App & operator=(App &&) = delete;

            void registerDrawFunc(Context::DrawFunc drawFunc);
            void registerUpdateFunc(Context::UpdateFunc updateFunc);
            void registerKeyFunc(Context::KeyFunc keyFunc);

            virtual void run();

        protected:
            Window & m_window;
    };
}

#endif //RPI_APP_HPP
