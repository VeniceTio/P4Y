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

Image<uint8_t> convolve(const Image<uint8_t> &image, const Image<double> &mask){
    Image<uint8_t> image2(image);
    Image<double> maskVar(mask);
    double pixel = 0;
    int index;
    int dimMaskConv = mask.getDx();
    int middleMask = dimMaskConv/2;
    int rightBord = dimMaskConv-middleMask;
    int leftBord = middleMask-1;
    for(int x=0;x<image.getDx();x++) {
        for (int y = 0; y < image.getDy(); y++) {
            index=-1;
            pixel=0;
            for (int xm = x-(middleMask-1); xm < x+rightBord+1; xm++) {
                for (int ym = y-(middleMask-1); ym < y+rightBord+1; ym++) {
                    index++;
                    if ( xm>-1 || xm< image.getDx()-1 || ym>-1 || ym<image.getDy()-1){
                        pixel += image(xm,ym)*mask(index);
                    }
                }
            }
            if (pixel<0){
                image2(x,y) = 0;
            } else if (pixel > 255){
                image2(x,y) = 255;
            } else {
                image2(x,y) = pixel;
            }
        }
    }
    return image2;
}
Image<double> gaussienMask(float sigma){
    int n = 5*sigma;
    if (n%2==0){
        n++;
    }
    Image<double> mask(n,n);
    int xm = 0;
    double poid=0;
    for(int x = -(n/2); x<(n/2)+1;x++){
        for(int y = -(n/2); y<(n/2)+1;y++){
            mask(xm) = exp(-(x*x+y*y)/(2*sigma*sigma));
            std::cout << " pixel (" << x << ";" << y << ") : " << mask(xm) << "\n";
            poid += mask(xm);
            xm++;
        }
    }
    for(int i = 0; i< mask.getSize()-1;i++){
        mask(i)=mask(i)/poid;
    }
    poid = 0;
    for(int i = 0; i< mask.getSize()-1;i++){
        poid += mask(i);
    }
    std::cout << " poid : " << poid << "\n";
    return mask;
}


int main(int argc, const char * argv[]) {
    if(argc !=5) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <teta> <option>\n";
        exit(EXIT_FAILURE);
    }
//    if(argv[3] != '4' && argv[3] != '8'){
//        std::cout << "<adjacence-type> : 4 or 8\n";
//        exit(EXIT_FAILURE);
//    }
    std::vector<double> data = {
            1./9,1./9,1./9,
            1./9,1./9,1./9,
            1./9,1./9,1./9
    };
    Image<double> mask1(3,3,data);

    std::vector<double> data2 = {
            1./16,2./16,1./16,
            2./16,4./16,2./16,
            1./16,2./16,1./16,
    };
    Image<double> mask2(3,3,data2);
    std::vector<double> data3 = {
            0,-1,0,
            -1,5,-1,
            0,-1,0,
    };
    Image<double> mask3(3,3,data3);
    std::vector<double> data4 = {
            -1,-1,-1,
            -1,9,-1,
            -1,-1,-1
    };
    Image<double> mask4(3,3,data4);
    std::vector<double> data5 = {
            -1,0,1,
            -2,0,2,
            -1,0,1
    };
    Image<double> mask5(3,3,data5);
    std::vector<double> data6 = {
            -1,-2,-1,
            0,0,0,
            1,2,1
    };
    Image<double> mask6(3,3,data6);

    //Image<double> mask3(gaussienMask(atof(argv[3])));

    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    if(strcmp(argv[4],"ga")==0) {
        writePGM(convolve(image, gaussienMask(atof(argv[3]))), argv[2]);
        std::cout << "GaussienMAsk";
    }else if (strcmp(argv[4],"l1")==0){
        writePGM(convolve(image, mask1), argv[2]);
    }else if (strcmp(argv[4],"l2")==0){
        writePGM(convolve(image, mask2), argv[2]);
    }else if (strcmp(argv[4],"r3")==0){
        writePGM(convolve(image, mask3), argv[2]);
    }else if (strcmp(argv[4],"r4")==0){
        writePGM(convolve(image, mask4), argv[2]);
    }else if (strcmp(argv[4],"a5")==0){
        writePGM(convolve(image, mask5), argv[2]);
    }else if (strcmp(argv[4],"a6")==0){
        writePGM(convolve(image, mask6), argv[2]);
    }
    return 0;
}