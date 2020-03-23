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
 * la fonction bruitGaussien va plus ou moins aleterer l'image en ajoutant une valeur au pixel. La valeur ajouté est aléatoire
 * et est répartie celon la loi normal uniform. On peut lancer la fonction de la manière suivante.
 *
 * params:
 *  - image de type Image<uint8_t> image à traiter
 *  - sigma de type double correspond à l'ecart type de la loi normal'
 *
 *  return :
 *  image2 de type Image<uint8_t> image resultante de la modification
 */
Image<uint8_t> bruitGaussien(const Image<uint8_t> &image, const double sigma){
    Image<uint8_t> image2(image);
    std::default_random_engine gen;
    std::normal_distribution<double> dist(0,sigma);
    double pixel;
    for(int y=0;y<image.getDy();y++) {
        for (int x = 0; x < image.getDx(); x++) {   // parcours des pixels celon leur coordonnée (x;y)
            pixel = image(x,y) + dist(gen);         // ajout d'une valeur parasyte defini celon la loi normal
            if (pixel<0){                           // ^
                pixel = 0;                          // |
            }
            else if (pixel > 255){
                pixel = 255;                        // verifier qu'une valeur est bien entre 255 et 0
            }                                       // |
            image2(x,y) = pixel;                    // v
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
    writePGM(bruitGaussien(image, atof(argv[3])), argv[2]);
    return 0;
}