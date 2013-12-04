#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <EGLHeaders.hpp>
#include <GLSLProgram.hpp>

namespace RPi {

    struct Context
    {
        Context();
        ~Context() = default;

        EGLint width;
        EGLint height;
        EGLContext eglContext;
        EGLDisplay eglDisplay;
        EGLSurface eglSurface;
        EGLNativeWindowType eglWindow;
        GLSLProgram * program;
    };
}

#endif //CONTEXT_HPP
