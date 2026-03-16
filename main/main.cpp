#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/RMTEncoder.h"
#include "../components/adapters/RMTMapper.h"
#include "../components/adapters/RMTConfigBuilder.h"

extern "C" int app_main() {
    RMTAdapter<1> adapterPin18(
        RMTConfigBuilder()
        .gpioNum(GPIO_NUM_18)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64)
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build(),
        {{200, 20, 30}}
    );
    return 0;
}