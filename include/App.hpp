#ifndef RPI_APP_HPP
#define RPI_APP_HPP

#include <Context.hpp>
#include <Window.hpp>

namespace RPi {

    class App
    {
        using DrawFunc   = void(*)(Context &);
        using UpdateFunc = void(*)(Context &, float);
        using KeyFunc    = void(*)(Context &, unsigned char, int, int);

        public:
            App(Window & window, int argc, char const ** argv);
            virtual ~App();

            App(App const &) = delete;
            App(App &&) = delete;

            App & operator=(App const &) = delete;
            App & operator=(App &&) = delete;

            void registerDrawFunc(DrawFunc drawFunc);
            void registerUpdateFunc(UpdateFunc updateFunc);
            void registerKeyFunc(KeyFunc keyFunc);

            virtual void run();

        protected:
            Window & m_window;
            DrawFunc m_drawFunc;
            UpdateFunc m_updateFunc;
            KeyFunc m_keyFunc;
    };
}

#endif //RPI_APP_HPP
