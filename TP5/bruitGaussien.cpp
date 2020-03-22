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

Image<uint8_t> bruitGaussien(const Image<uint8_t> &image, const double sigma){
    Image<uint8_t> image2(image);
    std::default_random_engine gen;
    std::normal_distribution<double> dist(0,sigma);
    double pixel;
    for(int y=0;y<image.getDy();y++) {
        for (int x = 0; x < image.getDx(); x++) {
            pixel = image(x,y) + dist(gen);
            if (pixel<0){
                pixel = 0;
            }
            else if (pixel > 255){
                pixel = 255;
            }
            image2(x,y) = pixel;
        }
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <n>\n";
        exit(EXIT_FAILURE);
    }
    //Image<double> mask3(gaussienMask(atof(argv[3])));

    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    writePGM(bruitGaussien(image, atof(argv[3])), argv[2]);
    return 0;
}