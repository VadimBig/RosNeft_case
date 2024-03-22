#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

class Function
{
public:
    double P;
    double amg;
    double amo;
    double Cpo;
    double Cpg;
    double Htarget;

    double calculateFunctionValue(double T)
    {
        return (((((Cpg / 4183) * (1.8 * T + 32) + (1.4503773779 * exp(1) - 4 * P) * ((1.619 * exp(1) - 10 * (1.4503773779 * exp(1) - 4 * P) + 1.412 * exp(1) - 6) * (1.4503773779 * exp(1) - 4 * P) - 0.02734)) * 2325.9612 * amg) + (((Cpo / 4183) * (1.8 * T + 32) + (1.4503773779 * exp(1) - 4 * P) * 3.36449 * exp(1) - 3) * amo * 2325.9612)) - Htarget);
    }
};

// Comment: This function implements the Dihotomia method for finding the root of a function.
double dihotomiaMethod(double a, double b, double e, Function *function)
{
    auto f = *function;

    while (f.calculateFunctionValue(a) * f.calculateFunctionValue(b) > 0)
    {
        a = a + 2;
        b = b - 2;

        if (a > b)
        {
            std::cout << "Temperature below 273 degrees Celsius" << std::endl;
            break;
        }
    }

    double c = 0;

    while ((b - a) / 2 > e)
    {
        c = (a + b) / 2;

        if ((f.calculateFunctionValue(a) * f.calculateFunctionValue(c)) > 0)
            a = c;
        else
            b = c;
    }

    return c;
}

// Comment: This function implements the Tangent method for finding the root of a function.
double tangentMethod(double a, double b, double e, Function *function)
{
    auto f = *function;
    double y = 0;
    double res = 0;

    while (f.calculateFunctionValue(a) * f.calculateFunctionValue(b) > 0)
    {
        a = a + 2;
        b = b - 2;

        if (a > b)
        {
            std::cout << "Temperature below 273 degrees Celsius" << std::endl;
            break;
        }
    }

    do
    {
        y = res;
        res = b - ((b - a) / (f.calculateFunctionValue(b) - f.calculateFunctionValue(a))) * f.calculateFunctionValue(b);
        a = b;
        b = res;
    } while (std::fabs(y - res) >= e);

    return res;
}

// Comment: This function implements the Simple Iteration method for finding the root of a function.
double simpleIterationMethod(double a, double b, double e, Function *function) {
    auto f = *function;
    double x0 = a;
    double x1 = b;
    double cMid = b - a;
    double x2 = f.calculateFunctionValue(cMid);

    while (f.calculateFunctionValue(a) * f.calculateFunctionValue(b) > 0)
    {
        a = a + 2;
        b = b - 2;

        if (a > b)
        {
            std::cout << "Temperature below 273 degrees Celsius" << std::endl;
            break;
        }
    }

    while (abs(x2- cMid) > e) {
        cMid = x2;
        x2 = f.calculateFunctionValue(cMid);
    }

    return x2;
}

void saveResultsToFile(double result) {
    std::ofstream outputFile("results.txt");
    if (outputFile.is_open()) {
        outputFile << "Result: " << result << std::endl;
        outputFile.close();
        std::cout << "Results saved to file successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}


int main()
{
    double a = -273;
    double b = 30000;
    double e = 0.0000000001;

    std::ifstream file("data.txt");
    std::vector<double> values;
    std::cout<<"Please, enter the number of method 1 - is Dihotomia method, 2 - is Tangent method, 3 - is Simple Iteration method!"<< std::endl;
    int num;
    std::cin >> num;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                double value = std::stod(line.substr(pos + 1));
                values.push_back(value);
            }
        }
        file.close();
    }
    int i = 0;
    double rezalt = 0;
    Function function{values[0], values[1], values[2], values[3],values[4], values[5]};
    if(num == 1){    std::cout <<"Temperature is " <<dihotomiaMethod(a, b, e, &function)<< "С" << std::endl;
            rezalt = dihotomiaMethod(a, b, e, &function);
            saveResultsToFile(rezalt);};

    if(num == 2){    std::cout << "Temperature is " <<tangentMethod(a, b, e, &function)<< "С"  << std::endl; 
        rezalt = tangentMethod(a, b, e, &function);
            saveResultsToFile(rezalt);};

    if(num == 3){ std::cout << "Temperature is " <<simpleIterationMethod(a, b, e, &function)<< "С"  << std::endl;     rezalt = simpleIterationMethod(a, b, e, &function);
            saveResultsToFile(rezalt);};

    return 0;
}
