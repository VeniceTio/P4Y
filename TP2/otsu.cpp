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

void compute_histo(const Image<uint8_t> &image, std::vector<int> &histo)
{
    for (int i = 0;i<image.getSize();i++){
        histo[image(i)]++;
    }
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

int otsu(const Image<uint8_t> &image){
    std::vector<int> histo = std::vector<int> (256,0);
    std::cout << "Etape 1 : \n";
    compute_histo(image,histo);
    std::cout << "Etape 1 : \n";
    int N = image.getSize();
    float Pbg,Pfg, Mbg, Mfg;
    float Var;
    float maxSeuil= 0;
    int bestSeuil = 0;
    std::cout << "Etape 3 : \n";
    for (int i = 0;i<256;i++){
        Pbg = 0;
        Pfg = 0;
        Mbg = 0;
        Mfg = 0;
        std::cout << "Etape 4' : \n";
        for (int j=0;j<i+1;j++){
//            std::cout << "Etape : " << j << "\n";
            Pbg += histo[j];
            Mbg += j * histo[j];
        }
        Pbg = Pbg/N;
        Mbg = Mbg/(N*Pbg);
        std::cout << "Pbg : " << Pbg << "Mbg : " << Mbg << "\n";
        for (int k=i+1;k<256;k++){
            Pfg += histo[k];
            Mfg +=k * histo[k];
        }
        Pfg = Pfg/N;
        Mfg = Mfg/(N*Pfg);
        std::cout << "Pfg : " << Pbg << "Mfg : " << Mbg << "\n";
        if(Pbg+Pfg != 1){
            std::cout << "Erreur de calcule !";
        }
        Var = Pbg * Pfg * ((Mbg-Mfg)*(Mbg-Mfg));
        std::cout << "Var : " << Var;
        if(Var > maxSeuil){
            maxSeuil = Var;
            bestSeuil = i;
        }
    }
    return bestSeuil;
}

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }
    Image<uint8_t> image=readPGM(argv[1]);
    print_info(image);
    int seuil = otsu(image);
    std::cout << " Seuil optimal : " << seuil;
    writePGM(create_seuillage(image,seuil),argv[2]);
    return 0;
}