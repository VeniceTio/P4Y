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
#include <vector>
#include <iostream>
#include "../TP4/image.h"
#include "../TP4/fileio.h"

/**
 * la fonction bruitPulsion bruite les pixel d'une image donnée en parmametre celon un pourcentage pré-defini.
 * Un pixel bruité soit noir soit blanc
 *
 * params:
 *  - image de type Image<uint8_t> image à traiter
 *  - p de type float correspond à la probabilité qu'un pixel soit bruité
 *
 *  return :
 *  image2 de type Image<uint8_t> image resultante de la modification
 */
Image<uint8_t> bruitPulsion(const Image<uint8_t> &image, const float p){
    Image<uint8_t> image2(image);
    int pixel;
    for(int y=0;y<image.getDy();y++) {
        for (int x = 0; x < image.getDx(); x++) {
            if((rand()%101)/100.<p){
                pixel = 0;
                if ((rand()%2)==1){
                    pixel = 255;
                }
                image2(x,y) = pixel;
            }
        }
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <n>\n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    writePGM(bruitPulsion(image, atof(argv[3])), argv[2]);
    return 0;
}