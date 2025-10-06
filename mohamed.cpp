
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void BandW(Image &img) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            int r = img(x, y, 0);
            int g = img(x, y, 1);
            int b = img(x, y, 2);
            double gray = 0.3 * r + 0.59 * g + 0.11 * b;
            unsigned char bw = (gray >= 128) ? 255 : 0;
            for (int z = 0; z < img.channels; z++) {
                img(x, y, z) = bw;
            }
        }
    }
}

void flipH(Image &img) {
    for (int x = 0; x < img.width / 2; x++) {
        for (int y = 0; y < img.height; y++) {
            for (int z = 0; z < img.channels; z++) {
                unsigned char temp = img(x, y, z);
                img(x, y, z) = img(img.width - 1 - x, y, z);
                img(img.width - 1 - x, y, z) = temp;
            }
        }
    }
}

void flipV(Image &img) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height / 2; y++) {
            for (int z = 0; z < img.channels; z++) {
                unsigned char temp = img(x, y, z);
                img(x, y, z) = img(x, img.height - 1 - y, z);
                img(x, img.height - 1 - y, z) = temp;
            }
        }
    }
}

void crop(Image &img, int startX, int startY, int cropWidth, int cropHeight) {
    if (startX < 0 || startY < 0) {
        cout << "Starting point cannot be negative." << endl;
        return;
    }
    if (cropWidth > img.width - startX || cropHeight > img.height - startY) {
        cout << "Crop size is too large for the given starting point." << endl;
        return;
    }

    Image cropped(cropWidth, cropHeight);

    for (int x = 0; x < cropWidth; x++) {
        for (int y = 0; y < cropHeight; y++) {
            for (int z = 0; z < img.channels; z++) {
                cropped(x, y, z) = img(x + startX, y + startY, z);
            }
        }
    }

    img = cropped;
}

void resizeImage(Image &img, int newWidth, int newHeight) {
    Image resized(newWidth, newHeight);

    // Calculate the ratio between old and new dimensions
    float xRatio = (float)img.width / newWidth;
    float yRatio = (float)img.height / newHeight;

    for (int x = 0; x < newWidth; x++) {
        for (int y = 0; y < newHeight; y++) {
            int origX = int(x * xRatio);
            int origY = int(y * yRatio);
            for (int z = 0; z < img.channels; z++) {
                resized(x, y, z) = img(origX, origY, z);
            }
        }
    }

    img = resized;
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
        cout << "\nmenu\n";
        cout << "choose a filter to apply or 0 to exit:\n";
        cout << "0- Exit\n";
        cout << "1- Black and White\n";
        cout << "2- Flip\n";
        cout << "3- Crop Image\n";
        cout << "4- Resize Image\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Exiting the program.\n";
                return 0;

            case 1: {
                Image img = originalImg;
                BandW(img);
                cout << "Black and White filter applied.\n";
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
                cout << "if u want to flip horizontal press 1, if u want to flip vertical press 2\n";
                int whichflip;
                cin >> whichflip;

                if (whichflip == 1) {
                    flipH(img);
                    cout << "Image flipped horizontally.\n";
                } else if (whichflip == 2) {
                    flipV(img);
                    cout << "Image flipped vertically.\n";
                } else {
                    cout << "Invalid choice for flip direction.\n";
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

            case 3: {
                Image img = originalImg;

                int startX, startY, cropWidth, cropHeight;
                cout << "Enter starting X coordinate: ";
                cin >> startX;
                cout << "Enter starting Y coordinate: ";
                cin >> startY;
                cout << "Enter width of crop: ";
                cin >> cropWidth;
                cout << "Enter height of crop: ";
                cin >> cropHeight;

                crop(img, startX, startY, cropWidth, cropHeight);
                cout << "Image cropped.\n";

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
            case 4: {
                Image img = originalImg;
                int newWidth, newHeight;
                cout << "Enter new width: ";
                cin >> newWidth;
                cout << "Enter new height: ";
                cin >> newHeight;

                resizeImage(img, newWidth, newHeight);
                cout << "Image resized.\n";

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


