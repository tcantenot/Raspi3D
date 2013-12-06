#ifndef RPI_PERSPECTIVE_CAMERA
#define RPI_PERSPECTIVE_CAMERA

#include <glm/glm.hpp>

#include <Camera.hpp>

namespace RPi {

class PerspectiveCamera : public Camera
{
    public:
        static constexpr float FOVY_MIN = 0.f;
        static constexpr float FOVY_MAX = 90.f;
        static constexpr float RATIO_MIN = 0.1f;
        static constexpr float NEAR_MIN  = 0.1f;

    public:
        PerspectiveCamera(float fovy = 70.f, float ratio = 1.f,
            float near = 1.f, float far = 100.f);
        PerspectiveCamera(PerspectiveCamera const &) = default;
        PerspectiveCamera(PerspectiveCamera &&) = default;
        ~PerspectiveCamera() = default;

        PerspectiveCamera & operator=(PerspectiveCamera const &) = default;

        glm::mat4 const & projection();

        void move(Input const & input);

        float fovy() const;
        void fovy(float fovy);

        float ratio() const;
        void ratio(float ratio);

        float near() const;
        void near(float near);

        float far() const;
        void far(float far);

    private:
        void updateProjectionMatrix();

    private:
        float m_fovy;
        float m_ratio;
        float m_near;
        float m_far;

        glm::mat4 m_projection;

        bool m_needUpdateProj;

};

}

#endif //RPI_PERSPECTIVE_CAMERA
