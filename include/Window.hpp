#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <Context.hpp>

namespace RPi {

using WindowFlags = unsigned int;
enum WindowFlag : WindowFlags
{
    WINDOW_NONE        = 0,
    WINDOW_ALPHA       = 1 << 0,
    WINDOW_DEPTH       = 1 << 1,
    WINDOW_STENCIL     = 1 << 2,
    WINDOW_MULTISAMPLE = 1 << 3
};

class Window
{
    public:
        Window(Context & context, char const * title,
            int width, int height, WindowFlags flags = 0);

        ~Window();

        Context & getContext() const;
        int getWidth() const;
        int getHeight() const;

        void display() const;

        void grabMousePointer(bool grab) const;
        void showMousePointer(bool show) const;

        void init() const;

        bool userInterrupt();

    private:
        int m_width;
        int m_height;
        Context & m_context;
};

}

#endif //WINDOW_HPP
