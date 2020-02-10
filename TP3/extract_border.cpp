//
// Created by TheWitcher on 10/02/2020.
//
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

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

Image<uint8_t> extract_border(const Image<uint8_t> &image, int adjacence){
    Image<uint8_t> image2(image);
    int pixel = 0;
    bool bord = false;
    for(int x=0;x<image.getDx();x++){
        for(int y=0;y<image.getDy();y++){
            pixel = image(x,y);
            if(pixel==255){
                if( x==0 || x== image.getDx()-1 || y==0 || y==image.getDy()-1){
                    bord = true;
                }else {
                    if (adjacence == 8) {
                        for (int xv = -1; xv < 2; xv++) {
                            for (int yv = -1; yv < 2; yv++) {
                                if (image(x + xv, y + yv) == 0) {
                                    bord = true;
                                }
                            }
                        }
                    } else {
                        if (image(x - 1, y) == 0 || image(x + 1, y) == 0 || image(x, y + 1) == 0 ||
                            image(x, y - 1) == 0) {
                            bord = true;
                        }
                    }
                }
            }
            if(bord){
                image2(x,y)=image(x,y);
                bord = false;
            }else {
                image2(x,y)=0;
            }
        }
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <adjacence-type>\n";
        exit(EXIT_FAILURE);
    }
//    if(argv[3] != '4' && argv[3] != '8'){
//        std::cout << "<adjacence-type> : 4 or 8\n";
//        exit(EXIT_FAILURE);
//    }
    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    writePGM(extract_border(image,atoi(argv[3])),argv[2]);
    return 0;
}