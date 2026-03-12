#include "../components/adapters/RMTAdapter.h"

extern "C" void app_main() {
    RMTAdapter& adapter = RMTAdapter::init();
}