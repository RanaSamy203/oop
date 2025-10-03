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

Image merge_images(Image &image1) {
    string filename_2;
    cout << "Pls enter second image path: ";
    cin >> filename_2;
    Image image2(filename_2);
    if (!image2.imageData) {
        cerr << "Failed to load second image!" << endl;
        return image1;
    }
    Image new_image(image2.width, image2.height);
    new_image.channels = image1.channels;
    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) =
                    image1(int(i * double(image1.width) / new_image.width),
                           int(j * double(image1.height) / new_image.height), k);
            }
        }
    }
    for (int i = 0; i < new_image.width; i++) {
        for (int j = 0; j < new_image.height; j++) {
            for (int k = 0; k < new_image.channels; k++) {
                new_image(i, j, k) =
                    (image2(i, j, k) + new_image(i, j, k)) / 2;
            }
        }
    }
    return new_image;
}

Image detect_image_edges(Image &image) {
    Image img = image;
    gray_scale(img);
    BandW(img);
    int width = img.width;
    int height = img.height;
    Image edges(width, height);
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int Gx = img(x + 1, y, 0) - img(x - 1, y, 0);
            int Gy = img(x, y + 1, 0) - img(x, y - 1, 0);
            if (abs(Gx) + abs(Gy) > 128) {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 0;
            } else {
                edges(x, y, 0) = edges(x, y, 1) = edges(x, y, 2) = 255;
            }
        }
    }
    return edges;
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
        cout << "3 - Merge Images\n";
        cout << "4 - Detect Image Edges\n";
        int choice;
        cin >> choice;
        switch (choice) {
            case 0:
                return 0;
            case 1: {
                Image img = originalImg;
                gray_scale(img);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                }
                break;
            }
            case 2: {
                Image img = originalImg;
                float factor;
                cout << "Enter factor (e.g. >1 to lighten, <1 to darken): ";
                cin >> factor;
                LightDark(img, factor);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                }
                break;
            }
            case 3: {
                Image img = originalImg;
                img = merge_images(img);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                }
                break;
            }
            case 4: {
                Image img = detect_image_edges(originalImg);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string saveFile;
                cout << "Enter filename to save the image or press Enter to skip: ";
                getline(cin, saveFile);
                if (!saveFile.empty()) {
                    img.saveImage(saveFile);
                }
                break;
            }
            default:
                break;
        }
    }
    return 0;
}


