#include <Context.hpp>

namespace RPi {

Context::Context()
{
    #ifdef RPI_NO_X
    bcm_host_init();
    #endif
}

Context::~Context()
{
    #ifdef RPI_NO_X
    bcm_host_deinit();
    #endif
}

}
