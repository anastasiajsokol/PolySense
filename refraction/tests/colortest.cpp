#include "../library/color.h"

#include <iostream>

int main(){
    using polysense::operator ""_nm;
    
    polysense::sRGB color = polysense::wavelength_to_srgb(500_nm);
    
    std::cout << "sRGB(" << color.red << ", " << color.green << ", " << color.blue << ") => (" << (int)(color.red * 255) << ", " << (int)(color.blue * 255) << ", " << (int)(color.green * 255) << ")" << std::endl;
    
    return EXIT_SUCCESS;
}