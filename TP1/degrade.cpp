#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"

Image<uint8_t> create_gradient(int dx,int dy){
    Image<uint8_t> image(dx,dy);

    int step = 1;
    if(image.getSize()>255){
        step = ceil(image.getSize()/255);
    }
    int val = -1;
    for (int i=0;i<image.getSize();i++){
        if(i%step==0)
            val++;
        image(i) = val;
    }
    //image.print();
    return image;
}

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <output.pgm> <width> <height> \n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image = create_gradient(atoi(argv[2]),atoi(argv[3]));
    writePGM(image,argv[1]);
    return 0;
}