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
        ~Context() = default;

        EGLint width;
        EGLint height;
        EGLContext eglContext;
        EGLDisplay eglDisplay;
        EGLSurface eglSurface;
        EGLNativeWindowType eglWindow;
        GLSLProgram * program = nullptr;
        DrawFunc drawFunc = nullptr;
        UpdateFunc updateFunc = nullptr;
        KeyFunc keyFunc = nullptr;
    };
}

#endif //CONTEXT_HPP
