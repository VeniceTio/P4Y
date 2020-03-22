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

Image<uint8_t> medianFilter(const Image<uint8_t> &image, const int size2){
    Image<uint8_t> image2(image);
    int dimMaskConv = size2;
    int middleMask = dimMaskConv/2;
    int rightBord = dimMaskConv-middleMask;
    int median;
    std::vector<uint8_t> list;
    for(int x=0;x<image.getDx();x++) {
        for (int y = 0; y < image.getDy(); y++) {
            for (int xm = x-(middleMask-1); xm < x+rightBord+1; xm++) {
                for (int ym = y-(middleMask-1); ym < y+rightBord+1; ym++) {
                    if ( xm>-1 && xm< image.getDx()-1 && ym>-1 && ym<image.getDy()-1){
                        list.push_back(image(xm,ym));
                    }
                }
            }
            sort(list.begin(),list.end());
            median = list.size()/2;
            image2(x,y) = list[median];
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
    //Image<double> mask3(gaussienMask(atof(argv[3])));

    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    writePGM(medianFilter(image, atoi(argv[3])), argv[2]);
    return 0;
}