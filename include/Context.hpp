#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <EGLHeaders.hpp>
#include <GLSLProgram.hpp>

namespace RPi {

    struct Context
    {
        using DrawFunc   = void(*)(Context &);
        using UpdateFunc = void(*)(Context &, float);
        using KeyFunc    = void(*)(Context &, unsigned char, int, int);

        Context();
        Context(Context const &) = delete;
        ~Context();

        Context & operator=(Context const &) = delete;

        EGLint width  = 0;
        EGLint height = 0;
        EGLContext eglContext = EGL_NO_CONTEXT;
        EGLDisplay eglDisplay = EGL_NO_DISPLAY;
        EGLSurface eglSurface = EGL_NO_SURFACE;;
        EGLNativeWindowType eglWindow = 0;
        GLSLProgram * program = nullptr;
        DrawFunc drawFunc     = nullptr;
        UpdateFunc updateFunc = nullptr;
        KeyFunc keyFunc       = nullptr;
    };
}

#endif //CONTEXT_HPP
