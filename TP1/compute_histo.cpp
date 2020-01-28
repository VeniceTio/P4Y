#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

void compute_histo(const Image<uint8_t> &image)
{
    std::vector<int> histo = std::vector<int> (256,0);
    for (int i = 0;i<image.getSize();i++){
        histo[image(i)]++;
    }
    for(int i = 0;i<256;i++){
        std::cout << i << " " << histo[i] << "\n";
    }
}

int main(int argc, const char * argv[]) {
    if(argc !=2) {
        std::cout << "Usage : " << argv[0] << " <input.pgm>\n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    compute_histo(image);
    return 0;
}