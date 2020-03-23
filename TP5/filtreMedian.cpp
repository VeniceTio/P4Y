//
// Created by TheWitcher on 02/03/2020.
//
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include "../TP4/image.h"
#include "../TP4/fileio.h"


/**
 * la fonction medianFilter permet d'apliquer un filtre median, c.a.d qui seletion la valeur median
 * des pixel present dans une fenetre pre-defini
 *
 * params:
 *  - image de type Image<uint8_t> image à traiter
 *  - size2 de type int defini la taille de la fenetre autour des pixels traité
 *
 *  return :
 *  image2 de type Image<uint8_t> image resultante de la modification
 */
Image<uint8_t> medianFilter(const Image<uint8_t> &image, const int size2){
    Image<uint8_t> image2(image);
    int dimMaskConv = size2;
    int middleMask = dimMaskConv/2;
    int rightBord = dimMaskConv-middleMask;
    int median;
    std::vector<uint8_t> list;
    for(int x=0;x<image.getDx();x++) {
        for (int y = 0; y < image.getDy(); y++) { // premiere double boucle permet de parcourir tout les pixels
            for (int xm = x-(middleMask-1); xm < x+rightBord+1; xm++) {
                for (int ym = y-(middleMask-1); ym < y+rightBord+1; ym++) { // permet de parcourir les pixels de la fenetre par rapport au pixel traité
                    if ( xm>-1 && xm< image.getDx()-1 && ym>-1 && ym<image.getDy()-1){    // choix des pixel si ils sont dans l'image
                        list.push_back(image(xm,ym));
                    }
                }
            }
            sort(list.begin(),list.end());           // tri de la liste pour pouvoir utiliser la valeur median
            median = list.size()/2;                  // position de la valeur median
            image2(x,y) = list[median];              // récuperation de la valeur median + application de cette valeur
            list.clear();
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
    writePGM(medianFilter(image, atoi(argv[3])), argv[2]);
    return 0;
}