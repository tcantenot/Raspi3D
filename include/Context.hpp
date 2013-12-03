#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <EGLHeaders.hpp>

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
    };
}

#endif //CONTEXT_HPP
