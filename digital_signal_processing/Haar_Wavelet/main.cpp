#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <filesystem>
using namespace std;

// Function declarations
void readRawFile(const string& filepath, vector<vector<uint8_t>>& image, int& width, int& height);
void writeRawFile(const string& filepath, const vector<vector<uint8_t>>& image);
void haarTransform(vector<vector<double>>& image, int rows, int cols);
void inverseHaarTransform(vector<vector<double>>& image, int rows, int cols);
void quantizeByFrequency(vector<vector<double>>& image, int rows, int cols, const vector<int>& quantLevels);
double calculateMSE(const vector<vector<uint8_t>>& original, const vector<vector<uint8_t>>& reconstructed);

int main() 
{
    string inputDir = "input/";
    string outputDir = "output/";

    // list of input image filenames
    vector<string> filenames = {
        "Barbara_512x512_yuv400_8bit.raw",
        "Couple_512x512_yuv400_8bit.raw",
        "Airplane_256x256_yuv400_8bit.raw",
        "Baboon_256x256_yuv400_8bit.raw",
        "Lenna_256x256_yuv400_8bit.raw"
    };

    vector<int> haarIterations = { 3 }; // iterations for Haar transform
    vector<int> quantLevels = { 1, 2, 3, 4, 5, 6, 7 }; // quantization levels

    // loop over each image
    for (const auto& filename : filenames) {
        string inputPath = inputDir + filename;
        int width, height;
        vector<vector<uint8_t>> image;

        // read input image
        readRawFile(inputPath, image, width, height);

        // convert the image to double for processing
        vector<vector<double>> transformed(height, vector<double>(width));
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                transformed[i][j] = static_cast<double>(image[i][j]);

        // perform Haar transform
        for (int iterations : haarIterations) {
            vector<vector<double>> workingImage = transformed;

            for (int k = 0; k < iterations; k++)
                haarTransform(workingImage, height, width);

            // apply quantization per frequency band
            quantizeByFrequency(workingImage, height, width, quantLevels);

            // perform inverse Haar Transform
            for (int k = 0; k < iterations; k++)
                inverseHaarTransform(workingImage, height, width);

            // convert back to uint8_t
            vector<vector<uint8_t>> reconstructed(height, vector<uint8_t>(width));
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    reconstructed[i][j] = static_cast<uint8_t>(min(max(workingImage[i][j], 0.0), 255.0));

            // write output image
            string outputFilename = filename.substr(0, filename.find_last_of('.')) + "_Haar" + to_string(iterations) + "_FreqQuant.raw";
            string outputPath = outputDir + outputFilename;
            writeRawFile(outputPath, reconstructed);

            // print result
            double mse = calculateMSE(image, reconstructed);
            cout << "Image: " << filename << endl;
            cout << "-> Output: " << outputFilename << endl;
            cout << "Haar Iterations: " << iterations << endl;
            cout << "MSE: " << mse << endl << endl;
        }

        // quantize without Haar transform
        for (int level : quantLevels) {
            vector<vector<double>> quantizedImage = transformed;

            // apply uniform quantization directly on the original image
            double factor = pow(2.0, level);
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    quantizedImage[i][j] = round(quantizedImage[i][j] / factor) * factor;

            // convert back to uint8_t
            vector<vector<uint8_t>> reconstructed(height, vector<uint8_t>(width));
            for (int i = 0; i < height; i++) 
                for (int j = 0; j < width; j++) 
                    reconstructed[i][j] = static_cast<uint8_t>(min(max(quantizedImage[i][j], 0.0), 255.0));

            // write output image
            string outputFilename = filename.substr(0, filename.find_last_of('.')) + "_NoHaar_Quant" + to_string(level) + ".raw";
            string outputPath = outputDir + outputFilename;
            writeRawFile(outputPath, reconstructed);

            // print result
            double mse = calculateMSE(image, reconstructed);
            cout << "Image: " << filename << endl;
            cout << "-> Output: " << outputFilename << endl;
            cout << "No Haar Transform" << endl;
            cout << "Quantization Level: " << level << endl;
            cout << "MSE: " << mse << endl << endl;
        }
    }

    return 0;
}


// function to read image
void readRawFile(const string& filepath, vector<vector<uint8_t>>& image, int& width, int& height) {
    ifstream file(filepath, ios::binary | ios::ate);
    if (!file) {
        cerr << "Error opening file: " << filepath << endl;
        exit(EXIT_FAILURE);
    }

    streamsize fileSize = file.tellg();
    file.seekg(0, ios::beg);

    if (fileSize == 512 * 512) {
        width = 512;
        height = 512;
    }
    else if (fileSize == 256 * 256) {
        width = 256;
        height = 256;
    }
    else {
        cerr << "Unknown resolution for file: " << filepath << endl;
        exit(EXIT_FAILURE);
    }

    // read image
    image.resize(height, vector<uint8_t>(width));
    for (int i = 0; i < height; i++)
        file.read(reinterpret_cast<char*>(image[i].data()), width);

    file.close();
}

void writeRawFile(const string& filepath, const vector<vector<uint8_t>>& image) 
{
    ofstream file(filepath, ios::binary);

    if (!file) {
        cerr << "Error opening file: " << filepath << endl;
        exit(EXIT_FAILURE);
    }

    // write image
    for (const auto& row : image)
        file.write(reinterpret_cast<const char*>(row.data()), row.size());
    file.close();
}

void haarTransform(vector<vector<double>>& image, int rows, int cols) 
{
    vector<vector<double>> temp(rows, vector<double>(cols));
    // horizontal transform
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            temp[i][j] = (image[i][2 * j] + image[i][2 * j + 1]) / sqrt(2.0); // low pass
            temp[i][j + cols / 2] = (image[i][2 * j] - image[i][2 * j + 1]) / sqrt(2.0); // high pass
        }
    }
    image = temp;

    // vertical transform
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows / 2; i++) {
            temp[i][j] = (image[2 * i][j] + image[2 * i + 1][j]) / sqrt(2.0); // low pass
            temp[i + rows / 2][j] = (image[2 * i][j] - image[2 * i + 1][j]) / sqrt(2.0); // high pass
        }
    }
    image = temp;
}

void inverseHaarTransform(vector<vector<double>>& image, int rows, int cols) 
{
    vector<vector<double>> temp(rows, vector<double>(cols));
    // vertical inverse transform
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows / 2; i++) {
            temp[2 * i][j] = (image[i][j] + image[i + rows / 2][j]) / sqrt(2.0); // low pass
            temp[2 * i + 1][j] = (image[i][j] - image[i + rows / 2][j]) / sqrt(2.0); // high pass
        }
    }
    image = temp;

    // horizontal inverse transform
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            temp[i][2 * j] = (image[i][j] + image[i][j + cols / 2]) / sqrt(2.0); // low pass
            temp[i][2 * j + 1] = (image[i][j] - image[i][j + cols / 2]) / sqrt(2.0); // high pass
        }
    }
    image = temp;
}

void quantizeByFrequency(vector<vector<double>>& image, int rows, int cols, const vector<int>& quantLevels) 
{
    int bands = quantLevels.size();
    int step = rows / (1 << (bands - 1));

    // apply quantization level to each frequency band
    for (int b = 0; b < bands; b++) {
        int start = step * b;
        int end = step * (b + 1);
        double factor = pow(2.0, quantLevels[b]);

        for (int i = start; i < end && i < rows; i++)
            for (int j = start; j < end && j < cols; j++)
                image[i][j] = round(image[i][j] / factor) * factor; // quantize the coefficients
    }
}

double calculateMSE(const vector<vector<uint8_t>>& original, const vector<vector<uint8_t>>& reconstructed)
{
    int rows = original.size(), cols = original[0].size();
    double mse = 0.0;

    // compute the sum of squared differences
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double diff = static_cast<double>(original[i][j]) - static_cast<double>(reconstructed[i][j]);
            mse += diff * diff;
        }
    }

    return mse / (rows * cols); // normalize
}
