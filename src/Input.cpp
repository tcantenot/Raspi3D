#include <Input.hpp>

namespace RPi {

Input::Input() : m_x(0), m_y(0), m_xRel(0), m_yRel(0)
{
    for(auto & k : m_keys)
        k = false;

    for(auto & b : m_mouseBtns)
        b = false;
}


Input::~Input()
{

}


void Input::updateEvents()
{
    m_xRel  = 0;
    m_yRel  = 0;
    m_wheel = 0;

    while(SDL_PollEvent(&m_events))
    {
        switch(m_events.type)
        {
            case SDL_KEYDOWN:
                m_keys[m_events.key.keysym.scancode] = true;
            break;


            case SDL_KEYUP:
                m_keys[m_events.key.keysym.scancode] = false;
            break;


            case SDL_MOUSEBUTTONDOWN:
                m_mouseBtns[m_events.button.button] = true;
            break;

            case SDL_MOUSEBUTTONUP:
                m_mouseBtns[m_events.button.button] = false;
            break;


            case SDL_MOUSEMOTION:

                m_x = m_events.motion.x;
                m_y = m_events.motion.y;

                m_xRel = m_events.motion.xrel;
                m_yRel = m_events.motion.yrel;

            break;

            case SDL_MOUSEWHEEL:
                m_wheel = static_cast<float>(m_events.wheel.y);
            break;

            default: break;
        }
    }
}


void Input::showMousePointer(bool show) const
{
    if(show)
        SDL_ShowCursor(SDL_ENABLE);

    else
        SDL_ShowCursor(SDL_DISABLE);
}


void Input::grabMousePointer(bool grab) const
{
    if(grab)
        SDL_SetRelativeMouseMode(SDL_TRUE);

    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}



bool Input::isKeyPressed(const SDL_Scancode key) const
{
    return m_keys[key];
}


bool Input::isMouseBtnPressed(const Uint8 btn) const
{
    return m_mouseBtns[btn];
}


bool Input::mouseMoved() const
{
    return m_xRel != 0 || m_yRel != 0;
}

bool Input::mouseWheelMoved() const
{
    return m_wheel != 0;
}

int Input::getX() const
{
    return m_x;
}

int Input::getY() const
{
    return m_y;
}

int Input::getXRel() const
{
    return m_xRel;
}

int Input::getYRel() const
{
    return m_yRel;
}

float Input::getMouseWheel() const
{
    return m_wheel;
}

}
