//
// Created by TheWitcher on 02/03/2020.
//
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../TP4/image.h"
#include "../TP4/fileio.h"

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

double MSE(const Image<uint8_t> &image, const Image<uint8_t> &imagePrime){
    double valeur = 0;
    for(int y=0;y<image.getDy();y++) {
        for (int x = 0; x < image.getDx(); x++) {
            valeur += ((image(x,y) - imagePrime(x,y))*(image(x,y) - imagePrime(x,y)));
        }
    }
    return valeur/image.getSize();
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm>\n";
        exit(EXIT_FAILURE);
    }
    //Image<double> mask3(gaussienMask(atof(argv[3])));

    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2=readPGM(argv[2]);
    print_info(image);
    std::cout << "MSE : " << MSE(image, image2);
    return 0;
}