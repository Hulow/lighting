#include "driver/rmt_tx.h"

#include "../components/adapters/RMTAdapter.h"



extern "C" int app_main() {
    RMTAdapter adapterPin18(18);

    return 0;
}