/**
 *  Spectrum Rendering Support Utility
 *      liscensed under MIT Liscense
 *      author Anastasia Sokol
 *      resources
 *          https://www.fourmilab.ch/documents/specrend/
**/

#ifndef POLYSENSE_REFRACTION_COLOR_H
#define POLYSENSE_REFRACTION_COLOR_H

#include <string>

#include <stdint.h>

namespace polysense {

/**
 *  Represents a specific wave to convert into color space
**/
struct wavelength {
    long double wave;

    inline constexpr wavelength(long double wave) : wave(wave) {}

    inline operator long double(){
        return wave;
    }
};

inline constexpr wavelength operator ""_nm(long double wave) {
    return wavelength(wave);
}

/**
 *  Used to convert between perceptual CIE colors to a device color
**/
using primary_t = long double;

struct primary_color {
    primary_t x, y;
};

struct color_space {
    std::string name;

    primary_color red, green, blue;
    primary_t gamma;
};

}; // end namespace polysense

#endif