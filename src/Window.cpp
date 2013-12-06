#include <cassert>
#include <cstring>
#include <iostream>

#include <Window.hpp>
#include <EGLHeaders.hpp>

#ifdef RPI_NO_X
    #include "bcm_host.h"
#else
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
    #include <X11/Xutil.h>
#endif

#ifndef RPI_NO_X
// X11 related local variables
static Display * x_display = nullptr;
#endif

namespace {


#ifdef RPI_NO_X
///
//  create_window() - RaspberryPi, direct surface(No X, Xlib)
//
//      This function initialized the display and window for EGL
//
EGLBoolean create_window(RPi::Context & context, const char *)
{
    static EGL_DISPMANX_WINDOW_T nativewindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;


    int display_width;
    int display_height;

    // create an EGL window surface, passing context width/height
    auto success = graphics_get_display_size(0 /* LCD */, 
        &display_width, &display_height);

    if(success < 0)
    {
      return EGL_FALSE;
    }

    display_width  = context.width;
    display_height = context.height;

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = display_width;
    dst_rect.height = display_height;
      
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = display_width << 16;
    src_rect.height = display_height << 16;   

    dispman_display = vc_dispmanx_display_open(0 /* LCD */);
    dispman_update  = vc_dispmanx_update_start(0);
         
    dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display,
      0/*layer*/, &dst_rect, 0/*src*/,
      &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, 0/*transform*/);
      
    nativewindow.element = dispman_element;
    nativewindow.width = display_width;
    nativewindow.height = display_height;
    vc_dispmanx_update_submit_sync(dispman_update);

    context.eglWindow = &nativewindow;

        return EGL_TRUE;
}
///
//  user_interrupt()
//
//      Reads from X11 event loop and interrupt program if there is a keypress, or
//      window close action.
//
GLboolean user_interrupt(RPi::Context &)
{
    //GLboolean userinterrupt = GL_FALSE;
    //return userinterrupt;
    
    // Ctrl-C for now to stop
    
    return GL_FALSE;
}

#else
///
//  create_window()
//
//      This function initialized the native X11 display and window for EGL
//
EGLBoolean create_window(RPi::Context & context, const char *title)
{
    // Get an handle of the display of the X server
    x_display = XOpenDisplay(nullptr);

    if(x_display == nullptr)
    {
        return EGL_FALSE;
    }

    // Get the default root window
    Window root = DefaultRootWindow(x_display);

    // Set the event mask of the window
    XSetWindowAttributes swa;
    swa.event_mask = ExposureMask | PointerMotionMask | KeyPressMask;

    // Create the new window
    Window window = XCreateWindow(
                x_display, root,
                0, 0, context.width, context.height, 0,
                CopyFromParent, InputOutput,
                CopyFromParent, CWEventMask,
                &swa);

    // Set window's attributes
    XSetWindowAttributes xattr;
    xattr.override_redirect = false;
    XChangeWindowAttributes(x_display, window, CWOverrideRedirect, &xattr);

    // Set window manager hints
    // -> the app relies on the WM to get keyboard input
    XWMHints hints;
    hints.input = true;
    hints.flags = InputHint;
    XSetWMHints(x_display, window, &hints);

    // Set window's title
    XStoreName(x_display, window, title);

    // Make the window visible on the screen
    XMapWindow(x_display, window);

    // Get identifiers for the provided atom name strings
    Atom wm_state;
    wm_state = XInternAtom(x_display, "_NET_WM_STATE", false);

    XEvent xev;
    std::memset(&xev, 0, sizeof(xev));
    xev.type                 = ClientMessage;
    xev.xclient.window       = window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = false;
    XSendEvent(x_display, DefaultRootWindow(x_display), false, 
        SubstructureNotifyMask, &xev);

    // Set the eglWindow attribute of the current context to
    // the newly created window
    context.eglWindow = static_cast<EGLNativeWindowType>(window);

    return EGL_TRUE;
}


///
//  user_interrupt()
//
//      Reads from X11 event loop and interrupt program if there is a keypress, or
//      window close action.
//
GLboolean user_interrupt(RPi::Context & context)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = EGL_FALSE;
    char text;

     //Pump all messages from X server. Keypresses are directed to keyfunc(if defined)
    while(XPending(x_display))
    {
        XNextEvent(x_display, &xev);
        if(xev.type == KeyPress)
        {
            if(XLookupString(&xev.xkey, &text, 1, &key, 0) == 1)
            {
                if(context.keyFunc != nullptr)
                    context.keyFunc(context, text, 0, 0);
            }
        }
        if(xev.type == DestroyNotify)
            userinterrupt = EGL_TRUE;
    }
    return userinterrupt;
}
#endif


    EGLBoolean create_egl_context(RPi::Context & rpiContext, EGLint const attribList[])
    {
        // Obtains the EGL display connection for the given native display 
        EGLDisplay display;

        #ifdef RPI_NO_X
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        #else
        display = eglGetDisplay(static_cast<EGLNativeDisplayType>(x_display));
        #endif

        if(display == EGL_NO_DISPLAY)
        {
            std::cerr << "Failed to get display" << std::endl;
            return EGL_FALSE;
        }

        // Initialize EGL
        if(eglInitialize(display, nullptr, nullptr) == EGL_FALSE)
        {
            std::cerr << "Failed to initialize EGL" << std::endl;
            return EGL_FALSE;
        }

        // Get configs
        EGLint nbConfigs;
        if(eglGetConfigs(display, nullptr, 0, &nbConfigs) == EGL_FALSE)
        {
            std::cerr << "Failed to get configs" << std::endl;
            return EGL_FALSE;
        }

        // Choose config
         EGLConfig config;
        if(eglChooseConfig(display, attribList, &config, 1, &nbConfigs) == EGL_FALSE)
        {
            std::cerr << "Failed to choose configs" << std::endl;
            return EGL_FALSE;
        }

        // Create a surface
        #ifdef RPI_NO_X
        EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
        #else
        EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
        #endif

        EGLSurface surface = eglCreateWindowSurface(display, config,
            static_cast<EGLNativeWindowType>(rpiContext.eglWindow), nullptr);

        if(surface == EGL_NO_SURFACE)
        {
            std::cerr << "Failed to create surface" << std::endl;
            return EGL_FALSE;
        }

        // Create an EGL context
         EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);
         if(context == EGL_NO_CONTEXT)
         {
            std::cerr << "Failed to create context" << std::endl;
             return EGL_FALSE;
         }

         // Make the context current
         if(eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
         {
            std::cerr << "Failed to make context current" << std::endl;
             return EGL_FALSE;
         }

         rpiContext.eglDisplay = display;
         rpiContext.eglSurface = surface;
         rpiContext.eglContext = context;

         return EGL_TRUE;
    }
}

namespace RPi {

Window::Window(Context & context, char const * title,
    int width, int height, WindowFlags flags):
    m_width(width), m_height(height), m_context(context)
{
    context.width  = width;
    context.height = height;

    // Creates the window
    if(create_window(context, title) == EGL_FALSE)
    {
        //throw EGLException("Cannot create window");
        std::cerr << "Failed to create window" << std::endl;
    }

    // EGL context attributes
    EGLint const attribList[] =
    {
       EGL_RED_SIZE,       5,
       EGL_GREEN_SIZE,     6,
       EGL_BLUE_SIZE,      5,
       EGL_ALPHA_SIZE,     (flags & WINDOW_ALPHA)   ? 8 : EGL_DONT_CARE,
       EGL_DEPTH_SIZE,     (flags & WINDOW_DEPTH)   ? 8 : EGL_DONT_CARE,
       EGL_STENCIL_SIZE,   (flags & WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
       EGL_SAMPLE_BUFFERS, (flags & WINDOW_ALPHA)   ? 1 : 0,
       EGL_NONE
    };

    // Creates EGL context
    if(create_egl_context(context, attribList) == EGL_FALSE)
    {
        //throw EGLException("Cannot create window");
        std::cerr << "Failed to create egl context" << std::endl;
    }
}

Window::~Window()
{
    #ifdef __arm__
    bcm_host_deinit();
    #endif
}

Context & Window::getContext() const
{
    return m_context;
}

int Window::getWidth() const
{
    return m_width;
}

int Window::getHeight() const
{
    return m_height;
}

void Window::display() const
{
    eglSwapBuffers(m_context.eglDisplay, m_context.eglSurface);
}

void Window::init() const
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

bool Window::userInterrupt()
{
    return user_interrupt(m_context) == EGL_TRUE;
}

}

