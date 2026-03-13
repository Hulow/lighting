#pragma once

enum class WS2815Timing : uint32_t {
    T0H = 300, /* 220 ns ~ 380 ns */
    T0L = 1090, /* 580 ns ~ 1.6µs */
    T1H = 1090, /* 580 ns ~ 1.6µs */
    T1L = 320 /* 220 ns ~ 420 ns */
};

class BitToRMTMapper {
    private:
        int _resolution;
        uint32_t nsToTick(uint8_t timing);
    public:
        BitToRMTMapper(const int& resolution);
        rmt_item32_t map(const uint8_t& bit);
};