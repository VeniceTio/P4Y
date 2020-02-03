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

std::vector<int> compute_histo(const Image<uint8_t> &image)
{
    std::vector<int> histo = std::vector<int> (256,0);
    for (int i = 0;i<image.getSize();i++){
        histo[image(i)]++;
    }
    return histo;
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
int Mean(std::vector<int> &histo,int deb,int fin, int N){
    float Pbg = 0;
    float Mbg = 0;
    for (int j=deb;j<fin+1;j++){
        Pbg += histo[j];
        Mbg += j * histo[j];
    }
    Pbg = Pbg/N;
    Mbg = Mbg/(N*Pbg);
    return Mbg;
}

int kmeans(const Image<uint8_t> &image, int k)
{
    std::vector<int> histo = std::vector<int> (256,0);
    compute_histo(image,histo);
    int N = image.getSize();
    int s_new = 128;
    int seuil = 128;
    do{
        seuil = s_new;
        s_new = 0;
        for (int h = 0; h<k;h++) {
            s_new += Mean(histo, seuil * h, seuil * (h + 1),N);
        }
        s_new = s_new/k;
    }while (s_new != seuil)

    return s_new;
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    int seuil = kmeans(image);
    std::cout << " Seuil optimal : " << seuil;
    writePGM(create_seuillage(image,seuil),argv[2]);
    return 0;
}