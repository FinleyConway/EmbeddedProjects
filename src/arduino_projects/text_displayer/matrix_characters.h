#pragma once

struct CharMatrix
{
    unsigned char letter_rows[8];
};

namespace MCharacter {

    static constexpr CharMatrix A = {
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix B = {
        {
            0b11110000, 
            0b10001000,
            0b10001000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b00000000
        }
    };

    static constexpr CharMatrix C = {
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix D = {
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b00000000
        }
    };

    static constexpr CharMatrix E = {
        {
            0b11111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b11111000,
            0b00000000
        }
    };

    static constexpr CharMatrix F = {
        {
            0b11111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b00000000
        }
    };

    static constexpr CharMatrix G = {
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b10000000,
            0b10011000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix H = {
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix I = {
        {
            0b01110000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix J = {
        {
            0b00111000,
            0b00001000,
            0b00001000,
            0b00001000,
            0b00001000,
            0b01001000,
            0b00110000,
            0b00000000
        }
    };

    static constexpr CharMatrix K = {
        {
            0b10001000,
            0b10010000,
            0b10100000,
            0b11000000,
            0b10100000,
            0b10010000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix L = {
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b11111000,
            0b00000000
        }
    };

    static constexpr CharMatrix M = {
        {
            0b10001000,
            0b11011000,
            0b10101000,
            0b10101000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix N = {
        {
            0b10001000,
            0b10001000,
            0b11001000,
            0b10101000,
            0b10011000,
            0b10001000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix O = {
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix P = {
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b00000000
        }
    };

    static constexpr CharMatrix Q = {
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01110000,
            0b00001000,
            0b00000000
        }
    };

    static constexpr CharMatrix R = {
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10100000,
            0b10010000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix S = {
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b01110000,
            0b00001000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix T = {
        {
            0b11111000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00000000
        }
    };

    static constexpr CharMatrix U = {
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix V = {
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01010000,
            0b00100000,
            0b00000000
        }
    };

    static constexpr CharMatrix W = {
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10101000,
            0b10101000,
            0b01010000,
            0b00000000
        }
    };

    static constexpr CharMatrix X = {
        {
            0b10001000,
            0b10001000,
            0b01010000,
            0b00100000,
            0b01010000,
            0b10001000,
            0b10001000,
            0b00000000
        }
    };

    static constexpr CharMatrix Y = {
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b01111000,
            0b00001000,
            0b10001000,
            0b01110000,
            0b00000000
        }
    };

    static constexpr CharMatrix Z = {
        {
            0b11111000,
            0b00001000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b10000000,
            0b11111000,
            0b00000000
        }
    };

    static constexpr CharMatrix SPACE = {
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        }
    };

} // namespace MCharacter
