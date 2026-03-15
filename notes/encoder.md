# Encoder requirements

transfering data from bytes to symbols.
Each symbol = two pulses.
The duration unit is RMT ticks, determined by your resolution_hz configuration.
encoded output buffer

Input data (bytes)
        │
        ▼
Encoder
        │
        ▼
rmt_symbol_word_t[]
(duration + level pairs)
        │
        ▼
RMT TX hardware
        │
        ▼
GPIO waveform
        │
        ▼
WS2815 LED strip

## Data transfer time

T0H  | 0-code, High-level time     | 220ns ~ 380ns
T1H  | 1-code, High-level time     | 580ns ~ 1.6µs
T0L  | 0-code, Low-level time      | 580ns ~ 1.6µs
T1L  | 1-code, Low-level time      | 220ns ~ 420ns
RES  | Frame unit, Low-level time  | > 280µs


## use case

- WS2815 uses RGB order, 1 byte per color.
- Red = 255, Green = 0, Blue = 0

- first step: convert int to bit

- step 2: convert bit to pulse
    - Led has 3 colors
    - each color has 8 bits (one byte) -> 8 rmt_item32_t objects
    - each rmt_item32_t objects encode 1 bit.
    - each rmt_item32_t objects encode internally 4 values (timing + level)
    - so each color has 8 rmt_item32_t objects
    - so each LED has 24 rmt_item32_t objects


Bit   |  1
Byte  |  1 color
LED   |  3 Bytes


/**
 * @brief Definition of RMT item
 */
typedef struct {
    union {
        struct {
            uint32_t duration0 : 15; /*!< Duration of level0 */
            uint32_t level0 : 1;     /*!< Level of the first part */
            uint32_t duration1 : 15; /*!< Duration of level1 */
            uint32_t level1 : 1;     /*!< Level of the second part */
        };
        uint32_t val; /*!< Equivalent unsigned value for the RMT item */
    };
} rmt_item32_t;


RMT hardware requirement: the ESP32 RMT peripheral reads 32-bit “items” from memory directly.


strip -> 2 led

for each led
    i have 3 sub array of 8 bits each (convert to bits)

    for each sub array of 8 bits 

        for each 8 bits (convert to rmt_item32_t (the timed pulse).)

            {duration0 = long HIGH, level0 = 1, duration1 = short LOW, level1 = 0}

                rmt_item32_t r_items[8]; // R channel
                rmt_item32_t g_items[8]; // G channel
                rmt_item32_t b_items[8]; // B channel


rmt_symbol_word_t encoded_data[] = {

    // LED1
    // Green
    {80,1,45,0}, {40,1,85,0}, ...
    // Red
    {40,1,85,0}, {80,1,45,0}, ...
    // Blue
    {80,1,45,0}, {80,1,45,0}, ...

    // LED2
    // Green
    {40,1,85,0}, {40,1,85,0}, ...
    // Red
    {80,1,45,0}, {40,1,85,0}, ...
    // Blue
    {80,1,45,0}, {80,1,45,0}, ...

};
