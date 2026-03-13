#include "driver/rmt_tx.h"

#include "../components/adapters/RMTAdapter.h"



extern "C" int app_main() {

    RMTAdapter adapter = RMTAdapter::init(18);

    return 0;
}