void create_seuillage(const Image<uint8_t> &image)
{
    for (int i=0;i<image.getSize();i++){
        if(image(i)>175)
            image(i)=255;
        else
            image(i)=0;
    }
}