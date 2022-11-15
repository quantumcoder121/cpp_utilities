#ifndef ML_MATH_H
#define ML_MATH_H

// #include <iostream>
// #include <cstdlib>
// #include <cfloat>
#include <functional>

// for most of these, the C++ STL functions would be more efficient
// the only disadvantage is that they don't usually check whether the
// input is valid or not
// if you wish to implement this, it'd still be better to write a
// function that checks the input and then calls the STL function,
// instead of implementing the whole function

// using namespace std; // never put this in a header file
// put your own functions in a namespace

namespace math
{
    double mag(double);

    double exp(double);

    double ln(double);

    double log(double);

    double sine(double);

    double cosine(double);

    double tangent(double);

    double deg_to_rad(double);

    double rad_to_deg(double);

    double sin(double);

    double cos(double);

    double tan(double);

    double power(double, double);

    double logb(double, double);

    double arcsine(double);

    double arccosine(double);

    double arctangent(double);

    double arcsin(double);

    double arccos(double);

    double arctan(double);

    double arg(double, double, bool _ = true);

    double bin(const std::function<double(double)> &, double, double); // fixed lambda parameter capture and implicit conversion

    double sqrt(double);

    double derivative(const std::function<double(double)> &, double); // fixed implicit conversion of lambda
}

#endif