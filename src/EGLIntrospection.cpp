#include <EGLIntrospection.hpp>

#include <cassert>
#include <sstream>
#include <vector>

#include <EGL/egl.h>

namespace
{
    EGLDisplay s_display = EGL_NO_DISPLAY;
    int s_major = 0;
    int s_minor = 0;
    std::string s_version = "";
    std::string s_config  = "";

    // =========================================================================
    //   Initialization and introspection functions
    // =========================================================================
    
    // Get an EGL display connection
    void get_display()
    {
        s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        assert(s_display != EGL_NO_DISPLAY);
    }

    void init_egl_context()
    {
        // Get an EGL display connection
        get_display();

        // Initialize EGL and get version
        auto init = eglInitialize(s_display, &s_major, &s_minor);
        (void) init;
        assert(init != EGL_FALSE);

        // Set string version
        std::ostringstream version;
        version << s_major << "." << s_minor;
        s_version = version.str();
    }

    void get_config()
    {

        std::ostringstream info;

        EGLint nbConfigs;

        // Get the number of configs
        auto config = eglGetConfigs(s_display, nullptr, 0, &nbConfigs);
        assert(config != EGL_FALSE);

        std::vector<EGLConfig> configs;
        configs.resize(nbConfigs);

        config = eglGetConfigs(s_display, &configs[0], nbConfigs, &nbConfigs);
        assert(config != EGL_FALSE);

        EGLint value;

        for(auto i = 0; i < nbConfigs; ++i)
        {
            info << "============" << "\n";
            info << " Config #" << i << "\n";
            info << "============" << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_BUFFER_SIZE, &value);
            info << "Buffer Size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_RED_SIZE, &value);
            info << "Red Size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_GREEN_SIZE, &value);
            info << "Green Size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_BLUE_SIZE, &value);
            info << "Blue Size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_ALPHA_SIZE, &value);
            info << "Alpha Size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_CONFIG_CAVEAT, &value);
            switch(value)
            {
                case EGL_NONE :
                    info << "Config caveat  EGL_NONE\n";
                    break;
                case EGL_SLOW_CONFIG :
                    info << "Config caveat  EGL_SLOW_CONFIG\n";
                    break;

                default : break;
            }

            eglGetConfigAttrib(s_display, configs[i], EGL_CONFIG_ID, &value);
            info << "Config ID " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_DEPTH_SIZE, &value);
            info << "Depth size " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_MAX_PBUFFER_WIDTH, &value);
            info << "Max pbuffer width " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_MAX_PBUFFER_HEIGHT, &value);
            info << "Max pbuffer height " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_MAX_PBUFFER_PIXELS, &value);
            info << "Max pbuffer pixels " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_NATIVE_RENDERABLE, &value);
            info << "Native renderable " << (value ? "true" : "false") << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_NATIVE_VISUAL_ID, &value);
            info << "Native visual ID " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_NATIVE_VISUAL_TYPE, &value);
            info << "Native visual type " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_SAMPLE_BUFFERS, &value);
            info << "Sample Buffers " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_SAMPLES, &value);
            info << "Samples " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_SURFACE_TYPE, &value);
            info << "Surface type " << value << "\n";

            eglGetConfigAttrib(s_display, configs[i], EGL_TRANSPARENT_TYPE, &value);
            info << "Transparent type " << value << "\n";

            info << "\n";
        }

        s_config = info.str();
    }
}

bool EGLIntrospection::s_initialized = false;

bool EGLIntrospection::Initialize()
{
    if(!s_initialized)
    {   
        init_egl_context();

        get_config();

        s_initialized = true;

        return true;
    }
    return false;
}


std::string EGLIntrospection::GetVersion()
{
    // EGLInstropection module must be initialized
    assert(s_initialized);

    return s_version;
}


std::string EGLIntrospection::GetConfig()
{
    // EGLInstropection module must be initialized
    assert(s_initialized);

    return s_config;
}

