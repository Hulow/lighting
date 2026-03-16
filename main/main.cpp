#include "../components/adapters/RMTAdapter.h"
#include "../components/adapters/RMTEncoder.h"
#include "../components/adapters/RMTMapper.h"
#include "../components/adapters/RMTConfigBuilder.h"

extern "C" int app_main() {

    std::array<LED, 1> stripOne{{200, 20, 30}};
    RMTEncoder<1> encoder(10000000, stripOne);
    RMTAdapter adapterPin18(
        RMTConfigBuilder()
        .gpioNum(GPIO_NUM_18)
        .clock(static_cast<rmt_clock_source_t>(RMT_CLK_SRC_DEFAULT))
        .memBlocks(64)
        .queueDepth(1)
        .resolutionHz(10'000'000)
        .build()
    );

    encoder.encodeStrip();
    // adapterPin18.sendRMTItems(
    //     ws2815_encoder,
    //     led_colors,
    //     sizeof(led_colors)
    // );
    return 0;
}