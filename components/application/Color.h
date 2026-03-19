#pragma once

class Color {
    private:
        uint8_t _green;
        uint8_t _red;
        uint8_t _blue;
        Color(
            uint8_t green, 
            uint8_t red, 
            uint8_t blue
        ) 
            : 
            _green(green), 
            _red(red), 
            _blue(blue) 
        {}

        std::vector<uint8_t> serializeChannel(uint8_t channel) const {
            std::vector<uint8_t> bits(8);
            for (int bit = 7; bit >= 0; bit -- ) {
                bits[7 - bit] = (channel >> bit) & 0x01;
            }

            return bits;
        }
        
    public:
        static Color fromGRB(const uint8_t& green, const uint8_t& red, const uint8_t& blue) {
            return Color(green, red, blue);
        }

        void setGreen(const uint8_t& green) {
            _green = green;
        }

        void setRed(const uint8_t& red) {
            _red = red;
        }

        void setBlue(const uint8_t& blue) {
            _blue = blue;
        }

        uint8_t getGreen() const {
            return _green;
        }

        uint8_t getRed() const {
            return _red;
        }

        uint8_t getBlue() const {
            return _blue;
        }

        std::vector<uint8_t> serialize() const {
            std::vector<uint8_t> bits;
            std::vector<uint8_t> green = serializeChannel(_green);
            std::vector<uint8_t> red = serializeChannel(_red);
            std::vector<uint8_t> blue = serializeChannel(_blue);

            bits.insert(bits.end(), green.begin(), green.end());
            bits.insert(bits.end(), red.begin(), red.end());
            bits.insert(bits.end(), blue.begin(), blue.end());

            return bits;
        }
};