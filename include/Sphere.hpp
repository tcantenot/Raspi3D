#ifndef RPI_SPHERE_HPP
#define RPI_SPHERE_HPP

#include <cstddef>

namespace RPi {

class Sphere
{
    public:
        Sphere(std::size_t radius);
        ~Sphere();

    private:
        std::size_t m_radius;
};

}

#endif //RPI_SPHERE_HPP
