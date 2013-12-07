#include <Context.hpp>

#ifdef __arm__
#include <bcm_host.h>
#endif

namespace RPi {

Context::Context()
{
    #ifdef __arm__
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
