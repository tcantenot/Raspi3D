#ifndef RPI_INPUT_HPP
#define RPI_INPUT_HPP

#include <array>

#include <SDL2/SDL.h>

namespace RPi {
    
class Input
{
    public:

    Input();
    ~Input();

    void updateEvents();
    void showMousePointer(bool show) const;
    void grabMousePointer(bool grab) const;

    bool isKeyPressed(const SDL_Scancode key) const;
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
    std::array<bool, SDL_NUM_SCANCODES> m_keys;
    std::array<bool, 8> m_mouseBtns;

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;
    float m_wheel;
};

}

#endif //RPI_INPUT_HPP
