//- Mazen Nasser Mohamed – ID: 20240453
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void gray_scale(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int avg = 0;
            for (int k = 0; k < image.channels; k++) {
                avg += image(i, j, k);
            }
            avg /= image.channels;
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = avg;
            }
        }
    }
}

void LightDark(Image &img, float factor) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            for (int z = 0; z < img.channels; z++) {
                int value = static_cast<int>(img(x, y, z) * factor);
                if (value > 255) value = 255;
                if (value < 0) value = 0;
                img(x, y, z) = static_cast<unsigned char>(value);
            }
        }
    }
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

    while (true) {
        cout << "0 - Exit\n";
        cout << "1 - Grayscale Filter\n";
        cout << "2 - Lighten/Darken Filter\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Exiting the program.\n";
                return 0;

            case 1: {
                Image img = originalImg;
                gray_scale(img);
                cout << "Grayscale filter applied.\n";
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

            case 2: {
                Image img = originalImg;
                float factor;
                cout << "Enter factor (e.g. >1 to lighten, <1 to darken): ";
                cin >> factor;
                LightDark(img, factor);
                cout << "Lighten/Darken filter applied.\n";
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
