#include <iostream>

#include <EGLIntrospection.hpp>


int main(int, char const **)
{
    EGLIntrospection::Initialize();

    std::cout << "Version : " << EGLIntrospection::GetVersion() << std::endl;
    std::cout << EGLIntrospection::GetConfig() << std::endl;
    return 0;
}
