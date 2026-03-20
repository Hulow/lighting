#include "../application/ports/ITimer.h"
#include <cstdint>

class FreeRTOSTimer : public ITimer {
    public:
        void wait(const uint32_t& ms);
};