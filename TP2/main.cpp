#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "../TP1/fileio.h"

void print_info(const Image<uint8_t> &image)
{
    std::cout << " Taille : " << image.getDx() << " x " << image.getDy() << "\n";
    std::cout << " Nombre de pixel : " << image.getSize() << "\n";
    std::cout << " Val min : " << unsigned(image.getMin()) << "\n";
    std::cout << " Val max : " << unsigned(image.getMax()) << "\n";
    int sommePx = 0;
    for (int i=0;i<image.getSize();i++){
        sommePx += image(i);
    }
    std::cout << " Somme des pixels : " << sommePx << "\n";
    std::cout << " Moyenne de gris : " << (sommePx/image.getSize()) << "\n";
}

void compute_histo(const Image<uint8_t> &image)
{
    std::vector<int> histo = std::vector<int> (256,0);
    for (int i = 0;i<image.getSize();i++){
        histo[image(i)]++;
    }
    for(int i = 0;i<256;i++){
        std::cout << i << " " << histo[i] << "\n";
    }
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    //compute_histo(image);
    writePGM(normalize(image,0,255),"normalizeR.pgm");
    Image<uint8_t> image3=readPGM("normalizeR.pgm");
    writePGM(equalize(image3),"equalizeR.pgm");
    

    return 0;
}