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

void create_gradient(int dx,int dy){
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
    writePGM(image, "test_grad.pgm");
}

Image<uint8_t> create_seuillage(const Image<uint8_t> &image, int seuil)
{
    Image<uint8_t> image2(image);
    for (int i=0;i<image.getSize();i++){
        if(image(i)>seuil)
            image2(i)=255;
        else
            image2(i)=0;
    }
    return image2;
}

Image<uint8_t> create_negatif(const Image<uint8_t> &image)
{
    Image<uint8_t> image2(image);
    for (int i=0;i<image.getSize();i++){
        image2(i)= 255-image(i);
    }
    return image2;
}

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
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    
    //writePGM(image, argv[2]);
    print_info(image);
    //create_gradient(1024,1024);
    //writePGM(create_seuillage(image,175),"seuillage.pgm");
    //writePGM(create_negatif(image),"negatif.pgm");
    //compute_histo(image);
    writePGM(normalize(image,0,255),"normalizeR.pgm");
    Image<uint8_t> image3=readPGM("normalizeR.pgm");
    writePGM(equalize(image3),"equalizeR.pgm");
    

    return 0;
}