## Tick = basic timing unit

- The RMT peripheral doesn’t work directly in nanoseconds or microseconds.
- it counts “ticks”, which are small increments of time based on the RMT clock source.
- Tick duration = 1 / resolution_hz = 1 / 10,000,000 = 0.1 µs = 100 ns


## LED bit encoding

- The WS2815 uses NZR (Non-Return-to-Zero) single-wire signaling
- 0 bit -> short HIGH, long LOW
- 1 bit -> long HIGH, short LOW
- Each bit is a pulse with a high and low phase

## Process

### 1 - Bits per LED
- WS2815 is 24 bits per led
    - 8 bits for green
    - 8 bits for blue
    - 8 bits for red

- Each bit is encoded by a high / low pulse.

- 1 LED = 24 bits = 24 RMT items (1 bit / item)

### 2 - How many LEDs per GPIO pin
- 25 LEDs = 600 bits
- This tells you how many RMT items you need and how much memory you need

### 3 - Bit timing (data transfer)

BIT : T_HIGH : T_LOW
0 : 220–380 ns : 580–1600 ns
1 : 580–1600 ns : 220–420 ns

- Pick a safe value in the middle for each:
    - 0-bit: High = 300 ns, Low = 1 µs
    - 1-bit: High = 1 µs, Low = 300 ns
- This is critical for resolution.

### 4 - Set RMT Resolution

- Resolution: How long a tick last
- tick length = 1 / resolution (Hz)

Example with 10 MHz (1 tick = 100 ns):
- O bit low = 3 ticks
- 0 bit high = 10 ticks
- 1 bit low = 10 ticks
- 2 bit high = 3 ticks

### 4 - Memory and queue

- Each LED bit = 1 RMT item
- Memory blocks have a fixed number of symbols (usually 64)
- Queue depth tells RMT how many blocks to buffer
- For many LEDs, you may need to split the data across multiple blocks and queue them.

### Resume 

- Bits per LED = 24
- Total bits = num_leds × 24
- Number of RMT items = total bits
- Tick length = 1 / resolution_hz
- Bit durations in ticks = round(T_high / tick, T_low / tick)
- Blocks needed = ceil(total bits / mem_block_symbols)
