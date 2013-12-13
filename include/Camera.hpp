#ifndef RPI_CAMERA_HPP
#define RPI_CAMERA_HPP

#include <glm/glm.hpp>

#include <Input.hpp>

namespace RPi {
    class Camera
    {
        typedef float Angle;

        static constexpr Angle PHI_MAX = static_cast<Angle>(89.0);

        public:
        Camera(glm::vec3 const & position = glm::vec3(3.0, 3.0, 3.0),
            glm::vec3 const & target = glm::vec3(0, 0, 0), 
            glm::vec3 const & up = glm::vec3(0, 1.0, 0),
            float sensibility = 0.5, float speed = 0.5);
        Camera(Camera const &) = default;
        Camera(Camera &&) = default;
        virtual ~Camera();

        Camera & operator=(Camera const &) = default;

        glm::mat4 const & lookAt();

        virtual glm::mat4 const & projection() = 0;

        virtual void move(Input const & input);

        void position(glm::vec3 const & position);
        glm::vec3 const & position();

        void target(glm::vec3 const & target);
        glm::vec3 const & target();

        void up(glm::vec3 const & up);
        glm::vec3 const & up();

        void sensibility(float sensibility);
        float sensibility();

        void speed(float speed);
        float speed();

        void enableMouse(bool mouse);
        bool isMouseEnabled() const;

    private:
        void orient(float xRel, float yRel);
        void updateMV();

    protected:
        Angle m_phi;
        Angle m_theta;
        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up;
        glm::vec3 m_orientation;
        glm::vec3 m_sideShift;
        glm::mat4 m_modelview;

        float m_sensibility;
        float m_speed;

        bool m_mouseEnabled;

        bool m_needUpdateMV;
};

}

#endif //RPI_CAMERA_HPP
