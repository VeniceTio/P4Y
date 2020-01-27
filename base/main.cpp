#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

void print_info(const Image<T> &image)
{
    std::cout << " Taille : " << image.getDx() << " x " << image.getDy();
    std::cout << " Nombre de pixel : " << image.getSize();
    std::cout << " Val min : " << image.getMin();
    std::cout << " Val max : " << image.getMax();
    int sommePx = 0;
    for (int i=0;i<image.getSize();i++){
        sommePx += image.getData().at(i);
    }
    std::cout << " Somme des pixels : " << sommePx;
    std::cout << " Moyenne de gris : " << (sommePx/image.getSize());
}


int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    
    print_info(&image);

    writePGM(image, argv[2]);

    return 0;
}
