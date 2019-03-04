//Derek Tomassi
//COMP 116
//Prof Gagne
#include <iostream>
#include <fstream>
using namespace std;

struct Pixel {
    int red;
    int green;
    int blue;
};
/*
*TODO: COMPLETE: flip methods
       DEBUG: fade method
*/


//List of global variables to be used through all methods in the program
int width, height;
string PPMType; //variable used when writing the new .ppm file
int maxRGBVal;

//List of all the methods used throughout the program
Pixel* readFile(string filename);
void writeFile(Pixel* PPMArr);
void maxRed(Pixel* PPMArr);
void maxGreen(Pixel* PPMArr);
void maxBlue(Pixel* PPMArr);
void fade(Pixel* PPMArr);
void grayscale(Pixel* PPMArr);
void flipHorizontal(Pixel* PPMArr);
void flipVertical(Pixel* PPMArr);

int main () {
    string filename;
    Pixel* PPMArr;

    cout << "===PPM Photo Filter===" << endl;
    cout << "Enter the filename: ";
    cin >> filename;
    cout << endl;

    PPMArr = readFile(filename);

    //Test if the method returned with error
    if (PPMArr == nullptr) {
        return 1;
    }

    //Asking what filter to use
    string filter;
    cout << "Enter the filter you want to use: " << endl;
    cout << "maxRed" << endl;
    cout << "maxBlue" << endl;
    cout << "maxGreen" << endl;
    cout << "fade" << endl;
    cout << "grayscale" << endl;
    cout << "flipVertical" << endl;
    cout << "flipHorizontal" << endl;
    cin >> filter;

    //Conditionals to decide which method to call base on user input
    if (filter == "maxRed") {
        maxRed(PPMArr);
    } else if (filter == "maxBlue") {
        maxBlue(PPMArr);
    } else if (filter == "maxGreen") {
        maxGreen(PPMArr);
    } else if (filter == "fade") {
        fade(PPMArr);
    } else if (filter == "grayscale") {
        grayscale(PPMArr);
    } else if (filter == "flipVertical") {
        flipVertical(PPMArr);
    } else if (filter == "flipHorizontal") {
        flipHorizontal(PPMArr);
    }

    delete[] PPMArr;
    return 0;
}

Pixel* readFile(string filename) {
    ifstream inFile;

    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Invalid filename" << endl;
        return nullptr;
    }

    inFile >> PPMType;

    //obtaining the width and height from the file
    inFile >> width;
    inFile >> height;

    inFile >> maxRGBVal;

    Pixel* PPMArr = new Pixel[width*height];

    int count = 0;
    while(!inFile.eof()) {
        inFile >> PPMArr[count].red;
        inFile >> PPMArr[count].green;
        inFile >> PPMArr[count].blue;
        count++;
    }

    //done with input file closing input file stream
    inFile.close();

    return PPMArr;
}

void maxRed(Pixel* PPMArr) {
    //going through the array and changing all .red values to 255
    for (int i = 0; i < (width*height); i++) {
        PPMArr[i].red = 255;
    }

    writeFile(PPMArr);
}

void maxGreen(Pixel* PPMArr) {
    //going through the array and changing all .green values to 255
    for (int i = 0; i < (width*height); i++) {
        PPMArr[i].green = 255;
    }

    writeFile(PPMArr);
}

void maxBlue(Pixel* PPMArr) {
    //going through the array and changing all .blue values to 255
    for (int i = 0; i < (width*height); i++) {
        PPMArr[i].blue = 255;
    }

    writeFile(PPMArr);
}

void fade(Pixel* PPMArr) {
    //taking absolute value from 128 and setting the vals
    for (int i = 0; i < (width*height); i++) {
        PPMArr[i].red = (((PPMArr[i].red- 128) / 2 - 1) * -1) + PPMArr[i].red;
        PPMArr[i].green = (((PPMArr[i].green - 128) / 2 - 1) * -1) + PPMArr[i].green;
        PPMArr[i].blue = (((PPMArr[i].blue - 128) / 2 - 1) * -1) + PPMArr[i].blue;
    }

    writeFile(PPMArr);
}

void grayscale(Pixel* PPMArr) {
    //taking average of all the pixels
    for (int i = 0; i < (width*height); i++) {
        int average = (PPMArr[i].red + PPMArr[i].green + PPMArr[i].blue) / 3;
        PPMArr[i].red = average;
        PPMArr[i].green = average;
        PPMArr[i].blue = average;
    }

    writeFile(PPMArr);
}

void flipHorizontal(Pixel* PPMArr) {
    int middle = width / 2;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < middle; col++) {
            Pixel temp;
            temp.red = PPMArr[(row*width)+col].red;
            temp.green = PPMArr[(row*width)+col].green;
            temp.blue = PPMArr[(row*width)+col].blue;

            PPMArr[(row*width)+col].red = PPMArr[(width-1)+((row*width)-col)].red;
            PPMArr[(row*width)+col].green = PPMArr[(width-1)+((row*width)-col)].green;
            PPMArr[(row*width)+col].blue = PPMArr[(width-1)+((row*width)-col)].blue;

            PPMArr[(width-1)+((row*width)-col)].red = temp.red;
            PPMArr[(width-1)+((row*width)-col)].green = temp.green;
            PPMArr[(width-1)+((row*width)-col)].blue = temp.blue;
        }
    }

    writeFile(PPMArr);
}


void flipVertical(Pixel* PPMArr) {
    int middle = height / 2;

    for (int row = 0; row < middle; row++) {
        for (int col = 0; col < width; col++) {
            Pixel temp;
            temp.red = PPMArr[(row*width)+col].red;
            temp.green = PPMArr[(row*width)+col].green;
            temp.blue = PPMArr[(row*width)+col].blue;

            PPMArr[(row*width)+col].red = PPMArr[(height - (row + 1)) * width + col].red;
            PPMArr[(row*width)+col].green = PPMArr[(height - (row + 1)) * width + col].green;
            PPMArr[(row*width)+col].blue = PPMArr[(height - (row + 1)) * width + col].blue;

            PPMArr[(height - (row + 1)) * width + col].red = temp.red;
            PPMArr[(height - (row + 1)) * width + col].green = temp.green;
            PPMArr[(height - (row + 1)) * width + col].blue = temp.blue;
        }
    }

    writeFile(PPMArr);
}

void writeFile(Pixel* PPMArr) {
    ofstream outFile;

    string newFilename;
    cout << "Name of new file: ";
    cin >> newFilename;
    cout << endl;
    newFilename = newFilename;

    outFile.open(newFilename);

    //putting in first three lines of the file
    outFile << PPMType << endl;
    outFile << width << " " << height << endl;
    outFile << maxRGBVal << endl;

    //filling all of the rgb pixel values in
    for (int i = 0; i < (width*height); i++) {
        outFile << PPMArr[i].red << endl;
        outFile << PPMArr[i].green << endl;
        outFile << PPMArr[i].blue << endl;
    }

    outFile.close();
}
