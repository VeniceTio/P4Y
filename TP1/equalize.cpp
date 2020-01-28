#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

Image<uint8_t> equalize(const Image<uint8_t> &image){
    Image<uint8_t> image2(image);
    std::vector<int> histo = std::vector<int> (256,0);
    for (int i = 0;i<image.getSize();i++){
        histo[image(i)]++;
    }
    int oldMax = image.getMax();
    int oldMin = image.getMin();
    int sum = 0;
    for (int i = oldMin; i < image.getSize(); i++) {
      sum = 0;
      for (int j = oldMin; j < image(i); j++) {
         sum += histo[j];
      }
      image2(i) = ((oldMax - oldMin)/(double)image.getSize())*sum;
    }
    return image2;
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm>\n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image2 = equalize(image);
    writePGM(image2,argv[2]);
    return 0;
}