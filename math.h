#include<iostream>
#include<cstdlib>

using namespace std;

double exp(double a){
    double n = 0.0;
    double t = 1.0;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001){
        s = s + t;
        n = n + 1;
        t = t * a / n;
    }
    return (s);
}

double ln(double a){
    if (a < 0.0){
        cout << "Input less than zero, exiting ...";
        exit(0);
    }
    double x;
    if (a > 1.0) x = 1.0 - 1.0 / a;
    else x = 1.0 - a;
    double n = 1.0;
    double t = x;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001){
        s = s + t;
        t = t * x * n / (n + 1);
        n = n + 1;
    }
    if (a > 1.0) return s;
    else return -s;
}

double log(double a){
    double x = ln(a);
    return x / 2.302585093;
}

double sine(double a){
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001){
        s = s + t;
        t = (- 1.0) * t * a * a / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return (s);
}

double cosine(double a){
    double n = 0.0;
    double t = 1.0;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001){
        s = s + t;
        t = (- 1.0) * t * a * a / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return (s);
}

double tangent(double a){
    double s = sine(a);
    double c = cosine(a);
    if (c < 0.000001 && c > -0.000001){
        cout << "Input value invalid, exiting ...";
        exit(0);
    }
    return s / c;
}

double deg_to_rad(double a){
    return a * 3.1415926536 / 180.0;
}

double rad_to_deg(double a){
    return a * 180.0 / 3.1415926536;
}

double sin(double a){
    return sine(deg_to_rad(a));
}

double cos(double a){
    return cosine(deg_to_rad(a));
}

double tan(double a){
    return tangent(deg_to_rad(a));
}

double power(double x, double y){
    double a = y * ln(x);
    return exp(a);
}

double logb(double x, double y){
    double a = ln(y);
    return a / ln(x);
}

double arcsine(double a){
    if (a > 1.0 || a < -1.0){
        cout << "Invalid Input, exiting ...";
        exit(0);
    }
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while(t > 0.000001 || t < -0.000001){
        s = s + t;
        t = n * n * a * a * t / (n * n + 3.0 * n + 2.0);
        n = n + 2.0;
    }
    return s;
}

double arccosine(double a){
    return 3.1415926536 / 2.0 - arcsine(a);
}

double arctangent(double a){
    double n = 1.0;
    double t = a;
    double s = 0.0;
    while (t > 0.000001 || t < -0.000001){
        s = s + t;
        t = (-1.0) * a * a * n * t / (n + 2);
        n = n + 2.0;
    }
    return s;
}

double arcsin(double a){
    double x = arcsine(a);
    return rad_to_deg(x);
}

double arccos(double a){
    double x = arccosine(a);
    return rad_to_deg(x);
}

double arctan(double a){
    double x = arctangent(a);
    return rad_to_deg(x);
}

double arg(double x, double y, bool in_deg = true){
    if (x < 0.000001 && x > -0.000001 && y < 0.000001 && y > -0.000001){
        cout << "Invalid Inputs, exiting ...";
        exit(0);
    }
    double r;
    if (x < 0.000001 && x > -0.000001){
        if (y > 0.0) r = 90.0;
        else r = -90.0;
    }
    else if (x > 0.0) r = arctan(y / x);
    else {
        if (y < 0.000001 && y > -0.000001) r = 180.0;
        else if (y > 0.0) r = 180.0 + arctan(y / x);
        else r = -180.0 + arctan(y / x);
    }
    if (!in_deg) r = deg_to_rad(r);
    return r;
}

double bin(double (*func)(double), double l, double r){
    double d = r - l;
    double m = (r + l) / 2.0;
    double m_v = func(m);
    if (d < 0.000001) return m;
    else if (m_v > 0) return bin(func, l, m);
    else return bin(func, m, r);
}
