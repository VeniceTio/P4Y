#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

Image<uint8_t> normalize(const Image<uint8_t> &image,int min, int max)
{
    Image<uint8_t> image2(image);
    int oldMax = image.getMax();
    int oldMin = image.getMin();
    float coef = 0;
    float result = 0;
    for (int i=0;i<image.getSize();i++){
        coef = (max-min)/(oldMax-oldMin);
        result = min + (image(i)-oldMin)*coef;
        //std::cout << (image(i)-oldMin) <<" "<< result <<"\n";
        //std::cout << "( " << max << " - " << min << " ) / ( " << oldMax << " - " << oldMin << " = " << coef << "\n";
        std::cout << (int)(image(i));
        image2(i)= min + ((int)(image(i))-oldMin) * ( (float)(max-min)/(float)(oldMax-oldMin));
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=5) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> <min> <max>\n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2 = normalize(image,argv[3],argv[4]);
    writePGM(image2,argv[2]);
    return 0;
}