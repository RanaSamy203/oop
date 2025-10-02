// - Rana Samy Rizk – ID: 20242126
// ✅ Implemented the Invert Colors filter and the Rotate filter (90°, 180°, 270°)

#include"Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// filter 3
Image invertColors(const Image &img) {
    Image inverted(img.width, img.height);
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int c = 0; c < img.channels; ++c) {
                inverted(x, y, c) = 255 - img(x, y, c);
            }
        }
    }
    return inverted;
}

// filter 6
void rotate90(Image &img) {
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(j, img.width - 1 - i, k) = img(i, j, k);
    img = rotated;
}


void rotate180(Image &img) {
    Image rotated(img.width, img.height);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
    img = rotated;
}


void rotate270(Image &img) {
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.height - 1 - j, i, k) = img(i, j, k);
    img = rotated;
}

int main() {
    string filename;
    cout << "Enter the filename of the image: ";
    cin >> filename;
    Image originalImg(filename);

    if (!originalImg.imageData) {
        cerr << "Failed to load image, Please use .bmp, .jpg, .jpeg, or .png: " << filename << endl;
        return -1;
    }
    while (true)
    {
        cout << "\nmenu\n";
        cout << "choose a filter to apply or 0 to exit:\n";
        cout << "0- Exit\n";
        cout<<"3- Invert Image\n";
        cout<<"6- Rotate Image\n";

        int choice;
        cin >> choice;

        switch (choice){
            case 0:
                cout << "Exiting the program.\n";
                return 0;

            case 5:{
                Image img = originalImg;
                img = invertColors(img);
                cout << "Invert Image filter applied.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                    cout << "Image saved as " << saveFile << "\n";
                }
                break;
               
            }

            
            case 6:{
                Image img = originalImg;
                int angle;
                cout << "Enter rotation angle (90, 180, 270): ";
                cin >> angle;
                if (angle == 90) {
                    rotate90(img);
                } else if (angle == 180) {
                    rotate180(img); 
                } else if (angle == 270) {
                    rotate270(img); 
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                    cout << "Image saved as " << saveFile << "\n";
                }
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    return 0;
}