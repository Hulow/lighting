#include "WS2815Encoder.h"

template <size_t N>
WS2815Encoder<N>::WS2815Encoder(BitToRMTMapper& mapper, std::array<LED, N>& strip) : _mapper(mapper), _strip(strip) {}

template <size_t N>
void WS2815Encoder<N>::encode() {}