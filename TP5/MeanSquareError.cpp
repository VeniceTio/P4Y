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

/**
 * la fonction MSE est un outil de mesure renvoyant un double indiquant la dissimilarité entre 2 image
 * params :
 *  - image type Image<uint8_t> : premiere image à comparé
 *  - image2 type Image<uint8_t> : deuxieme image à comparé
 *
 *  return :
 *      - ... type double : indicateur de dissimilarité des 2 images
 */
double MSE(const Image<uint8_t> &image, const Image<uint8_t> &imagePrime){
    double valeur = 0;
    for(int y=0;y<image.getDy();y++) {
        for (int x = 0; x < image.getDx(); x++) {  //double boucle permettant de parcourrir les image avec les coordonnées (x;y)
            valeur += ((image(x,y) - imagePrime(x,y))*(image(x,y) - imagePrime(x,y)));  //application de la formule
        }
    }
    return valeur/image.getSize();
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm>\n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2=readPGM(argv[2]);
    std::cout << "MSE : " << MSE(image, image2) << "\n";
    return 0;
}