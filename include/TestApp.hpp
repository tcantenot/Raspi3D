#ifndef RPI_TEST_APP_HPP
#define RPI_TEST_APP_HPP

#include <App.hpp>

namespace RPi {

class TestApp : public App
{
    public:
        TestApp(Window & window, int argc, char ** argv);
        virtual ~TestApp();

        virtual void run() override;
};

}

#endif //RPI_TEST_APP_HPP
