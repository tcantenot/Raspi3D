#include <glm/gtx/transform.hpp>

#include <PerspectiveCamera.hpp>

namespace RPi {

PerspectiveCamera::PerspectiveCamera(float fov, float r,
    float n, float f):
    Camera(),
    m_fovy(0), m_ratio(0), m_near(0), m_far(0),
    m_projection(), m_needUpdateProj(true)
{
    fovy(fov);
    ratio(r);
    near(n);
    far(f);
    updateProjectionMatrix();
}

glm::mat4 const & PerspectiveCamera::projection()
{
    updateProjectionMatrix();
    return m_projection;
}

void PerspectiveCamera::move(Input const & input)
{
    Camera::move(input);

    if(input.mouseWheelMoved())
    {
        this->fovy(m_fovy - (input.getMouseWheel() * 2));
        m_needUpdateProj = true;
    }
}

float PerspectiveCamera::fovy() const
{
    return m_fovy;
}

void PerspectiveCamera::fovy(float fovy)
{
    if(fovy > FOVY_MAX) m_fovy = FOVY_MAX;
    else if(fovy < FOVY_MIN) m_fovy = FOVY_MIN;
    else  m_fovy = fovy;
    m_needUpdateProj = true;
}


float PerspectiveCamera::ratio() const
{
    return m_ratio;
}

void PerspectiveCamera::ratio(float ratio)
{
    float ratioMin = RATIO_MIN;
    m_ratio = std::max(ratioMin, ratio);
    m_needUpdateProj = true;
}

float PerspectiveCamera::near() const
{
    return m_near;
}

void PerspectiveCamera::near(float near)
{
    float nearMin = NEAR_MIN;
    m_near = std::max(nearMin, near);
    m_needUpdateProj = true;
}

float PerspectiveCamera::far() const
{
    return m_far;
}

void PerspectiveCamera::far(float far)
{
    m_far = std::max(m_near + 1.f, far);
    m_needUpdateProj = true;
}

void PerspectiveCamera::updateProjectionMatrix()
{
    if(m_needUpdateProj)
    {
        m_projection = glm::perspective(m_fovy, m_ratio, m_near, m_far);
        m_needUpdateProj = false;
    }
}

}
