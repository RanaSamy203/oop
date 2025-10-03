//- Rana Samy Rizk – ID: 20242126
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// filter 3
Image invertColors(const Image &img)
{
    Image inverted(img.width, img.height);
    for (int x = 0; x < img.width; ++x)
    {
        for (int y = 0; y < img.height; ++y)
        {
            for (int c = 0; c < img.channels; ++c)
            {
                inverted(x, y, c) = 255 - img(x, y, c);
            }
        }
    }
    return inverted;
}

// filter 6
void rotate90(Image &img)
{
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(j, img.width - 1 - i, k) = img(i, j, k);
    img = rotated;
}

void rotate180(Image &img)
{
    Image rotated(img.width, img.height);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.width - 1 - i, img.height - 1 - j, k) = img(i, j, k);
    img = rotated;
}

void rotate270(Image &img)
{
    Image rotated(img.height, img.width);
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j)
            for (int k = 0; k < img.channels; ++k)
                rotated(img.height - 1 - j, i, k) = img(i, j, k);
    img = rotated;
}

// filter 9
void addWhiteFrame(Image &image, int thickness, string style)
{
    unsigned char r = 255, g = 255, b = 255; // white color
    for (int x = 0; x < image.width; ++x)
    {
        for (int y = 0; y < thickness; ++y)
        {
            if (style == "dotted" && (x + y) % 2 != 0)
                continue;

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;

            image(x, image.height - 1 - y, 0) = r;
            image(x, image.height - 1 - y, 1) = g;
            image(x, image.height - 1 - y, 2) = b;
        }
    }

    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < thickness; ++x)
        {
            if (style == "dotted" && (x + y) % 2 != 0)
                continue;

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;

            image(image.width - 1 - x, y, 0) = r;
            image(image.width - 1 - x, y, 1) = g;
            image(image.width - 1 - x, y, 2) = b;
        }
    }
}

// filter 12
void applyBoxBlur(Image &image, int blurLevel)
{
    int kernelSize = 2 * blurLevel + 1;
    int halfKernel = blurLevel;
    Image temp = image; // Copy for reading original pixels

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int sum[3] = {0, 0, 0};
            int count = 0;

            for (int dx = -halfKernel; dx <= halfKernel; ++dx)
            {
                for (int dy = -halfKernel; dy <= halfKernel; ++dy)
                {
                    int x = i + dx;
                    int y = j + dy;

                    if (x >= 0 && x < image.width && y >= 0 && y < image.height)
                    {
                        for (int k = 0; k < 3; ++k)
                        {
                            sum[k] += temp(x, y, k);
                        }
                        ++count;
                    }
                }
            }

            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = sum[k] / count;
            }
        }
    }
}
int main()
{
    string filename;
    cout << "Enter the filename of the image: ";
    cin >> filename;
    Image originalImg(filename);

    if (!originalImg.imageData)
    {
        cerr << "Failed to load image, Please use .bmp, .jpg, .jpeg, or .png: " << filename << endl;
        return -1;
    }

    while (true)
    {
        cout << "1- Invert Image\n";
        cout << "2- Rotate Image\n";
        cout << "3- Blur Images\n";
        cout << "4- Adding a Frame to the Picture\n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Exiting the program.\n";
            return 0;
        case 1:
        {
            Image img = originalImg;
            img = invertColors(img);
            cout << "Invert Image filter applied.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        case 2:
        {
            Image img = originalImg;
            int angle;
            cout << "Enter rotation angle (90, 180, 270): ";
            cin >> angle;
            if (angle == 90)
            {
                rotate90(img);
            }
            else if (angle == 180)
            {
                rotate180(img);
            }
            else if (angle == 270)
            {
                rotate270(img);
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        case 3:
        {
            int blurLevel;
            cout << "Enter blur level (e.g., 1 to 5): ";
            cin >> blurLevel;
            Image img = originalImg;
            applyBoxBlur(img, blurLevel);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
                img.saveImage(saveFile);
                cout << "Image saved as " << saveFile << "\n";
            }
            break;
        }
        
        case 4:
        {
            int thickness;
            string style;
            cout << "Enter frame style (simple or dotted): ";
            cin >> style;
            cout << "Enter frame thickness in pixels: ";
            cin >> thickness;

            Image img = originalImg;
            addWhiteFrame(img, thickness, style);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string saveFile;
            cout << "Enter filename to save the image or press Enter to skip: ";
            getline(cin, saveFile);
            if (!saveFile.empty())
            {
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