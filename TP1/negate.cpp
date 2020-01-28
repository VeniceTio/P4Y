#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

Image<uint8_t> create_negatif(const Image<uint8_t> &image)
{
    Image<uint8_t> image2(image);
    for (int i=0;i<image.getSize();i++){
        image2(i)= 255-image(i);
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2 = create_negatif(image);
    writePGM(image2,argv[2]);
    return 0;
}