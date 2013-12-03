#ifndef EGL_INTROSPECTION_HPP
#define EGL_INTROSPECTION_HPP

#include <string>

class EGLIntrospection
{
    public:

        static bool Initialize();

        static std::string GetVersion();

        static std::string GetConfig();

    private:
        static bool s_initialized;
};

#endif //EGL_INTROSPECTION_HPP
