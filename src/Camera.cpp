#include <iostream>

#include <glm/gtx/transform.hpp>

#include <Camera.hpp>

namespace RPi {

Camera::Camera(glm::vec3 const & position, glm::vec3 const & t, glm::vec3 const & up,
    float sensibility, float speed):
    m_phi(0), m_theta(0), m_position(position), m_target(t), m_up(up),
    m_orientation(), m_sideShift(), m_modelview(), m_sensibility(sensibility),
    m_speed(speed), m_needUpdateMV(true)
{
    target(t);
    m_sideShift = glm::normalize(glm::cross(m_up, m_orientation));
    updateMV();
}

Camera::~Camera()
{

}

glm::mat4 const & Camera::lookAt()
{
    updateMV();
    return m_modelview;
}

void Camera::move(Input const & input)
{
    if(input.mouseMoved())
    {
        this->orient(input.getXRel(), input.getYRel());
    }
    
    if(input.isKeyPressed(SDL_SCANCODE_UP))
    {
        m_position += m_orientation * m_speed;
    }

    if(input.isKeyPressed(SDL_SCANCODE_DOWN))
    {
        m_position -= m_orientation * m_speed;
    }

    if(input.isKeyPressed(SDL_SCANCODE_LEFT))
    {
        m_position += m_sideShift * m_speed;
    }

    if(input.isKeyPressed(SDL_SCANCODE_RIGHT))
    {
        m_position -= m_sideShift * m_speed;
    }

    if(input.isKeyPressed(SDL_SCANCODE_RSHIFT))
    {
        m_position += m_up * m_speed;
    }

    if(input.isKeyPressed(SDL_SCANCODE_RCTRL))
    {
        m_position -= m_up * m_speed;
    }

    m_target = m_position + m_orientation;
    m_needUpdateMV = true;
}


void Camera::position(glm::vec3 const & position)
{
    m_position = position;
    m_target = m_position + m_orientation;
        m_needUpdateMV = true;
}

glm::vec3 const & Camera::position()
{
    return m_position;
}

void Camera::target(glm::vec3 const & target)
{
    m_target = target;

    m_orientation = glm::normalize(m_target - m_position);

    //What is up?
    if(std::abs(m_up.x - 1.0) <= std::numeric_limits<float>::epsilon())
    {
        m_phi = static_cast<Angle>(asin(m_orientation.x));
        m_theta = static_cast<Angle>(acos(m_orientation.y / cos(m_phi)));

        if(m_orientation.y < 0) m_theta *= -1;
    }
    else if(std::abs(m_up.y - 1.0) <= std::numeric_limits<float>::epsilon())
    {
        m_phi = static_cast<Angle>(asin(m_orientation.y));
        m_theta = static_cast<Angle>(acos(m_orientation.z / cos(m_phi)));

        if(m_orientation.z < 0) m_theta *= -1;
    }
    else
    {
        m_phi = static_cast<Angle>(asin(m_orientation.x));
        m_theta = static_cast<Angle>(acos(m_orientation.z / cos(m_phi)));

        if(m_orientation.z < 0) m_theta *= -1;
    }

    static auto const toDegree = [](float rad)
    {
        return rad * 180.f / M_PI;
    };

    m_phi = toDegree(m_phi);
    m_theta = toDegree(m_theta);

    m_needUpdateMV = true;
}

glm::vec3 const & Camera::target()
{
    return m_target;
}

void Camera::up(glm::vec3 const & up)
{
    m_up = up;
    m_needUpdateMV = true;
}

glm::vec3 const & Camera::up()
{
    return m_up;
}

void Camera::sensibility(float sensibility)
{
    m_sensibility = sensibility;
}

float Camera::sensibility()
{
    return m_sensibility;
}

void Camera::speed(float speed)
{
    m_speed = speed;
}

float Camera::speed()
{
    return m_speed;
}

void Camera::orient(float xRel, float yRel)
{
    m_phi += -yRel * m_sensibility;
    m_theta += -xRel * m_sensibility;

    if(m_phi > Camera::PHI_MAX) m_phi = Camera::PHI_MAX;
    else if(m_phi < (-1 * Camera::PHI_MAX)) m_phi = -1 * Camera::PHI_MAX;

    static auto const toRadian = [](float deg)
    {
        return deg * M_PI / 180.f;
    };

    Angle phiRad   = toRadian(m_phi);
    Angle thetaRad = toRadian(m_theta);
    Angle cosPhi = static_cast<Angle>(cos(phiRad));
    Angle sinPhi = static_cast<Angle>(sin(phiRad));
    Angle cosTheta = static_cast<Angle>(cos(thetaRad));
    Angle sinTheta = static_cast<Angle>(sin(thetaRad));

    //What is up ?
    if(std::abs(m_up.x - 1.0) <= std::numeric_limits<float>::epsilon())
    {
        m_orientation = glm::vec3(sinPhi, cosPhi * cosTheta, cosPhi * sinTheta);
    }
    else if(std::abs(m_up.y - 1.0) <= std::numeric_limits<float>::epsilon())
    {
        m_orientation = glm::vec3(cosPhi * sinTheta, sinPhi, cosPhi * cosTheta);
    }
    else
    {
        m_orientation = glm::vec3(cosPhi * cosTheta, cosPhi * sinTheta, sinPhi);
    }

    m_sideShift = glm::normalize(glm::cross(m_up, m_orientation));

    m_target = m_position + m_orientation;

    m_needUpdateMV = true;
}

void Camera::updateMV()
{
    if(m_needUpdateMV)
    {
        m_modelview = glm::lookAt(m_position, m_target, m_up);
        m_needUpdateMV = false;
    }
}

}
