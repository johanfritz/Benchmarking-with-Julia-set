#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <complex>

int recursion(double re, double im, double c_real, double im_real, int limit);
void saveToCSV(const std::vector<std::vector<int>> &matrix, const std::string filename);
int main()
{
    auto t0 = std::chrono::high_resolution_clock::now();
    double realmin = -2; // bounding coordinates
    double imagmin = -2;
    double realmax = 2;
    double imagmax = 2;

    double c_real = -0.4; // constant c in generating Julia set
    double c_imag = 0.6;

    float precision = 1500; // arbitrary scaling factor (impacts resolution)

    float deltareal = realmax - realmin;
    float deltaimag = imagmax - imagmin;

    int realsize = static_cast<int>(precision * deltareal); // image sizes (pixels)
    int imagsize = static_cast<int>(precision * deltaimag);
    int elements = realsize * imagsize; // this is used for evaluation purposes
    std::vector<std::vector<int>> matrix(imagsize, std::vector<int>(realsize));
    for (int k = 0; k < realsize; k++) // int k is looping over the real axis, starting from left of matrix (negative values)
    {
        for (int j = 0; j < imagsize; j++) // int j is looping over imaginary axis, startis form top of matrix (positive values)
        {
            // matrix assignment here
            matrix[j][k] = recursion(realmin+k/precision, imagmax-j/precision, c_real, c_imag, 200);
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);
    float timeper = ns.count() / elements;
    std::cout << ns.count()/pow(10, 9) << " total render time (seconds)" << std::endl;
    std::cout << timeper << " render time per pixel (nanoseconds)" << std::endl;
    //saveToCSV(matrix, "matrix.csv");
    std::string script = "python plotcsv.py";
    //system(script.c_str()); 
    return 0;
}
int recursion(double re, double im, double c_re, double c_im, int limit)
{
    float re_temp;
    float im_temp;
    for (int k = 0; k < limit; k++)
    {
        re_temp=re*re-im*im+c_re;
        im_temp=2*re*im + c_im;
        if(re*re+im*im>2.25){return k;}
        re=re_temp;
        im=im_temp;
    }
    return limit;
}

void saveToCSV(const std::vector<std::vector<int>> &matrix, const std::string filename)
{
    std::ofstream file(filename);
    for (const std::vector<int> &row : matrix)
    {
        for (int k = 0; k < row.size() - 1; k++)
        {
            file << row[k];
            file << ",";
        }
        file << row[row.size() - 1];
        file << "\n";
    }
    file.close();
    return;
}
