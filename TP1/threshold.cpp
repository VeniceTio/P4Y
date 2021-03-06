#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

Image<uint8_t> create_seuillage(const Image<uint8_t> &image, int seuil)
{
    Image<uint8_t> image2(image);
    for (int i=0;i<image.getSize();i++){
        if(image(i)>seuil)
            image2(i)=255;
        else
            image2(i)=0;
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <seuil> \n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2 = create_seuillage(image,argv[3]);
    writePGM(image2,argv[2]);
    return 0;
}