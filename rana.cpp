#include"Image_Class.h"
int main(){

    Image image("luffy.jpg");
    Image rotated(image.height, image.width);
    for(int i=0;i<image.height;i++){
        for(int j=0;j<image.width;j++){
            for(int k=0;k<image.channels;k++){
                rotated(j, image.width - 1 - i, k) = image(i, j, k);
            }
        }
    }
    rotated.saveImage("rotated_luffy.jpg");
    return 0;

}