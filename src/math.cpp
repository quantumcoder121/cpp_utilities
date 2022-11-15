#include <math.h>

#include <iostream>
#include <cstdlib>
#include <cfloat>

// why?
double math::mag(double a)
{
    return 0;
}

double math::exp(double a)
{
    double n = 0.0;
    double t = 1.0;
    double s = 0.0;
    while (t > DBL_EPSILON || t < -DBL_EPSILON)
    {
        s = s + t;
        n = n + 1;
        t = t * a / n;
    }
    return s;
}

double math::ln(double a)
{
    if (a < DBL_EPSILON)
    {
        std::cerr << "Input less than zero, exiting...\n";
        exit(1); // perhaps use abort() or exit(-1) to be consistent
    }
    double x;
    if (a > 1.0)
        x = 1.0 - 1.0 / a;
    else
        x = 1.0 - a;
    double n = 1.0;
    double t = x;
    double s = 0.0;
    while (t > DBL_EPSILON || t < -DBL_EPSILON)
    {
        s = s + t;
        t = t * x * n / (n + 1);
        n = n + 1;
    }
    if (a > 1.0)
        return s;
    else
        return -s;
}

double math::log(double a)
{
    double x = math::ln(a);
    return x / 2.302585093;
}

double math::sine(double a)
{
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while (t > DBL_EPSILON || t < -DBL_EPSILON)
    {
        s = s + t;
        t = (-1.0) * t * a * a / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return s;
}

double math::cosine(double a)
{
    double n = 0.0;
    double t = 1.0;
    double s = 0.0;
    while (t > DBL_EPSILON || t < -DBL_EPSILON)
    {
        s = s + t;
        t = (-1.0) * t * a * a / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return s;
}

double math::tangent(double a)
{
    double s = math::sine(a);
    double c = math::cosine(a);
    if (c < DBL_EPSILON && c > -DBL_EPSILON)
    {
        std::cerr << "Input value invalid, exiting...\n";
        exit(0);
    }
    return s / c;
}

double math::deg_to_rad(double a)
{
    return a * 3.1415926536 / 180.0;
}

double math::rad_to_deg(double a)
{
    return a * 180.0 / 3.1415926536;
}

// maybe make sin, cos, tan take args in radians and sine, cosine, tangent take args in degrees?
double math::sin(double a)
{
    return math::sine(math::deg_to_rad(a));
}

double math::cos(double a)
{
    return math::cosine(math::deg_to_rad(a));
}

double math::tan(double a)
{
    return math::tangent(deg_to_rad(a));
}

// STL function is way more efficient than this
double math::power(double x, double y)
{
    double a = y * math::ln(x);
    return math::exp(a);
}

double math::logb(double x, double y)
{
    double a = math::ln(y);
    return a / math::ln(x); // x == 1?
}

double math::arcsine(double a)
{
    if (a > 1.0 || a < -1.0)
    {
        std::cerr << "Invalid Input, exiting...\n";
        exit(0);
    }
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001)
    {
        s = s + t;
        t = n * n * a * a * t / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return s;
}

double math::arccosine(double a)
{
    return 3.1415926536 / 2.0 - math::arcsine(a);
}

double math::arctangent(double a)
{
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001)
    {
        s = s + t;
        t = (-1.0) * a * a * n * t / (n + 2);
        n = n + 2.0;
    }
    return s;
}

double math::arcsin(double a)
{
    double x = math::arcsine(a);
    return math::rad_to_deg(x);
}

double math::arccos(double a)
{
    double x = math::arccosine(a);
    return math::rad_to_deg(x);
}

double math::arctan(double a)
{
    double x = math::arctangent(a);
    return math::rad_to_deg(x);
}

double math::arg(double x, double y, bool in_deg)
{
    if (x < 0.000001 && x > -0.000001 && y < 0.000001 && y > -0.000001)
    {
        std::cerr << "Invalid Inputs, exiting...\n";
        exit(0);
    }
    double r;
    if (x < 0.000001 && x > -0.000001)
    {
        if (y > 0.0)
            r = 90.0;
        else
            r = -90.0;
    }
    else if (x > 0.0)
        r = math::arctan(y / x);
    else
    {
        if (y < 0.000001 && y > -0.000001)
            r = 180.0;
        else if (y > 0.0)
            r = 180.0 + math::arctan(y / x);
        else
            r = -180.0 + math::arctan(y / x);
    }
    if (!in_deg)
        r = math::deg_to_rad(r);
    return r;
}

// fixed lambda parameter capture and implicit conversion
double math::bin(const std::function<double(double)> &func, double l, double r)
{
    double d = r - l;
    double m = (r + l) / 2.0;
    double m_v = func(m);
    if (d < DBL_EPSILON)
        return m;
    else if (m_v > 0)
        return math::bin(func, l, m);
    else
        return math::bin(func, m, r);
}

double math::sqrt(double a)
{
    if (a < DBL_EPSILON)
    {
        std::cerr << "Invalid Input, exiting...\n";
        exit(1);
    }
    if (a > 1)
    {
        return math::bin([a](double x) -> double
                    { return x * x - a; }, 0, a);
    }
    else
    {
        return math::bin([a](double x) -> double { return x * x - a; }, 0, 1);
    }
}

// fixed implicit conversion
double math::derivative(const std::function<double(double)> &func, double a)
{
    double h = math::bin([](double x) -> double { return x * x - DBL_EPSILON; }, 0, 1);
    return (func(a + h) - func(a)) / h;
}