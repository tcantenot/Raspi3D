#ifndef RPI_INPUT_HPP
#define RPI_INPUT_HPP

#include <array>

#include <SDL/SDL.h>

//cf http://stackoverflow.com/questions/3741055/inputs-in-sdl-on-key-pressed

namespace RPi {
    
class Input
{
    using SDLKey = decltype(SDL_Event::key.keysym.sym);

    public:

    Input();
    ~Input();

    void updateEvents();

    bool isKeyPressed(SDLKey key) const;
    bool isMouseBtnPressed(const Uint8 btn) const;
    bool mouseMoved() const;
    bool mouseWheelMoved() const;

    int getX() const;
    int getY() const;

    int getXRel() const;
    int getYRel() const;

    float getMouseWheel() const;

    private:

    SDL_Event m_events;
    std::array<bool, 322> m_keys;
    std::array<bool, 8> m_mouseBtns;

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;
    float m_wheel;
};

}

#endif //RPI_INPUT_HPP
