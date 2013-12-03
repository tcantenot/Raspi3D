#ifndef EGL_INTROSPECTION_HPP
#define EGL_INTROSPECTION_HPP

#include <EGLHeaders.hpp>

#include <string>

namespace RPi {

    class EGLIntrospection
    {
        public:

            static bool Initialize();

            static std::string GetVersion();
            
            static EGLint GetMajorVersion();

            static EGLint GetMinorVersion();

            static std::string GetConfig();

        private:
            static bool s_initialized;
    };
}

#endif //EGL_INTROSPECTION_HPP
