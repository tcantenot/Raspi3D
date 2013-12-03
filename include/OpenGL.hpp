#ifndef OPENGL_HPP
#define OPENGL_HPP

class OpenGL
{
    public:

        static bool Initialize();

    private:
        static bool initEGLContext();
};

#endif //OPENGL_HPP
