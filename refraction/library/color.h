/**
 *  Spectrum Rendering Support Utility
 *      liscensed under MIT Liscense
 *      author Anastasia Sokol
 *      resources
 *          https://www.fourmilab.ch/documents/specrend/
**/

#ifndef POLYSENSE_REFRACTION_COLOR_H
#define POLYSENSE_REFRACTION_COLOR_H

#include <stdexcept>
#include <cmath>

#include <stdint.h>

namespace polysense {

using wave_t = long double;
using color_t = long double;

/**
 *  Represents a specific wave to convert into color space
**/
struct wavelength {
    wave_t wave;

    inline constexpr wavelength(wave_t wave) : wave(wave) {}

    inline constexpr bool operator >(wavelength other){
        return wave > (wave_t)other;
    }

    inline constexpr bool operator <(wavelength other){
        return wave < (wave_t)other;
    }

    inline constexpr bool operator >=(wavelength other){
        return wave >= (wave_t)other;
    }

    inline constexpr bool operator <=(wavelength other){
        return wave <= (wave_t)other;
    }

    inline constexpr operator wave_t(){
        return wave;
    }
};

inline constexpr wavelength operator ""_nm(unsigned long long wave) {
    return wavelength(wave);
}

inline constexpr wavelength operator ""_nm(long double wave) {
    return wavelength(wave);
}

/**
 *  Represents a sRGB color value
 *      TODO: allow for custom color spaces
**/
struct sRGB {
    color_t red, green, blue;

    inline constexpr sRGB(color_t red, color_t green, color_t blue) : red(red), green(green), blue(blue) {}
};

/**
 *  Convert a given wavelength to sRGB value
 *      WARNING: this code does not work!
**/
sRGB wavelength_to_srgb(wavelength wave){
    // must be set in the following conditional block
    color_t r, g, b;

    // magic conditional block from internet... I need to better understand what is going on
    //      translated js from https://www.johndcook.com/wavelength_to_RGB.html
    // more comprehensive (but less comprehensible) starting point https://www.fourmilab.ch/documents/specrend/#cprog
    if(wave >= 380_nm && wave < 440_nm){
        r = -((wave_t)wave - 440) / (440 - 380);
        g = 0.0;
        b = 1.0;
    } else if(wave >= 440_nm && wave < 490_nm){
        r = 0.0;
        g = ((wave_t)wave - 440) / (490 - 440);
        b = 1.0;
    } else if(wave >= 490_nm && wave < 510_nm){
        r = 0.0;
        g = 1.0;
        b = -((wave_t)wave - 510) / (510 - 490);
    } else if(wave >= 510_nm && wave < 580_nm){
        r = -((wave_t)wave - 510) / (580 - 510);
        g = 1.0;
        b = 0.0;
    } else if(wave >= 580_nm && wave < 645_nm){
        r = 1.0;
        g = -((wave_t)wave - 645) / (645 - 580);
        b = 0.0;
    } else if(wave >= 645_nm && wave < 781_nm){
        r = 1.0;
        g = 0.0;
        b = 0.0;
    } else {
        throw std::invalid_argument("Only wavelengths in the range [380, 781) nm can be converted");
    }

    if(r < 0.0 || g < 0.0 || b < 0.0){
        throw std::invalid_argument("Wavelength resulted in negative rgb component - not representable");
    }

    const wave_t gamma = 0.8;
    return sRGB(std::pow(r, gamma), std::pow(g, gamma), std::pow(b, gamma));
}

}; // end namespace polysense

#endif