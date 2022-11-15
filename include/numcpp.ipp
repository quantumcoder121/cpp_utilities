#ifndef NUMCPP_IMPL
#define NUMCPP_IMPL

#include <numcpp.h>
#include <iostream>
#include <cstdlib>
#define NUMCPP_MAX_SIZE 1024

template <typename dtype>
numcpp::numcpp<dtype>::numcpp()
{
    ptr = new dtype[1];
    size = 0;
    max_size = 1;
}

// copy constructor
template <typename dtype>
numcpp::numcpp<dtype>::numcpp(const numcpp<dtype> &a)
{
    long long int s = a.length();
    ptr = new dtype[s];
    size = s;
    max_size = s;
    #pragma omp parallel for
    for (long long int i = 0; i < s; i++)
        ptr[i] = a[i];
}

// following three could be potentially redundant constructors
// leads to template resolution problems!!
// also why??
// template <typename dtype>
// numcpp::numcpp<dtype>::numcpp(int s)
// {
//     if (s <= 0)
//     {
//         std::cerr << "Input length is not positive, exiting...\n";
//         exit(1);
//     }
//     ptr = new dtype[s];
//     size = s;
//     max_size = s;
// }

// template <typename dtype>
// numcpp::numcpp<dtype>::numcpp(long int s)
// {
//     if (s < 0 || s == 0)
//     {
//         std::cerr << "Input length is not positive, exiting...\n";
//         exit(1);
//     }
//     ptr = new dtype[s];
//     size = s;
//     max_size = s;
// }

template <typename dtype>
numcpp::numcpp<dtype>::numcpp(long long int s)
{
    if (s < 0 || s == 0)
    {
        std::cerr << "Input length is not positive, exiting...\n";
        exit(1);
    }
    ptr = new dtype[s];
    size = s;
    max_size = s;
}

// following three are the standard set of constructors for now
template <typename dtype>
numcpp::numcpp<dtype>::numcpp(int s, dtype a)
{
    if (s < 0 || s == 0)
    {
        std::cerr << "Input length is not positive, exiting...\n";
        exit(1);
    }
    ptr = new dtype[s];
    #pragma omp parallel for
    for (long long int i = 0; i < s; i++)
        ptr[i] = a;
    size = s;
    max_size = s;
}

template <typename dtype>
numcpp::numcpp<dtype>::numcpp(long int s, dtype a)
{
    if (s < 0 || s == 0)
    {
        std::cerr << "Input length is not positive, exiting...\n";
        exit(1);
    }
    ptr = new dtype[s];
    #pragma omp parallel for
    for (long long int i = 0; i < s; i++)
        ptr[i] = a;
    size = s;
    max_size = s;
}

template <typename dtype>
numcpp::numcpp<dtype>::numcpp(long long int s, dtype a)
{
    if (s < 0 || s == 0)
    {
        std::cerr << "Input length is not positive, exiting...\n";
        exit(1);
    }
    ptr = new dtype[s];
    #pragma omp parallel for
    for (long long int i = 0; i < s; i++)
        ptr[i] = a;
    size = s;
    max_size = s;
}

// unsafe constructor (commented out for now)
// numcpp(long long int s, dtype* a){
//     if (s < 0 || s == 0){
//         std::cout << "Input size is not positive, exiting ...";
//         exit(1);
//     }
//     ptr = new dtype[s];
//     for (int i = 0; i < s; i++){
//         ptr[i] = a[i];
//     }
//     size = s;
//     max_size = s;
// }

// size/length of the array
template <typename dtype>
long long int numcpp::numcpp<dtype>::length() const
{
    return size;
}

// element access operator
template <typename dtype>
dtype &numcpp::numcpp<dtype>::operator[](int index)
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}

template <typename dtype>
dtype &numcpp::numcpp<dtype>::operator[](long int index)
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}

template <typename dtype>
dtype &numcpp::numcpp<dtype>::operator[](long long int index)
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}

// const element access operator
template <typename dtype>
const dtype &numcpp::numcpp<dtype>::operator[](int index) const
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}

template <typename dtype>
const dtype &numcpp::numcpp<dtype>::operator[](long int index) const
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}

template <typename dtype>
const dtype &numcpp::numcpp<dtype>::operator[](long long int index) const
{
    if (index < 0)
        index = size + index;
    if (index >= size || index < 0)
    {
        std::cerr << "Index out of bounds, exiting...\n";
        exit(1);
    }
    return ptr[index];
}


// adding extra element to the array (memory allocation update as new_size = 2 * size)
template <typename dtype>
void numcpp::numcpp<dtype>::append(dtype a)
{
    if (size == NUMCPP_MAX_SIZE)
    {
        std::cerr << "Exceeding length limit, exiting...\n";
        exit(2);
    }
    if (size == max_size)
    {
        dtype *temp = new dtype[max_size];
        #pragma omp parallel for
        for (long long int i = 0; i < size; i++)
            temp[i] = ptr[i];
        ptr = new dtype[2 * max_size];
        #pragma omp parallel for
        for (long long int i = 0; i < size; i++)
            ptr[i] = temp[i];
        delete[] temp;
        max_size = 2 * max_size;
    }
    ptr[size] = a;
    size = size + 1;
    return;
}

// element wise operations
template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator+(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] + a[i];
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator+=(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] + a[i];
    return;
}

// numcpp<dtype> operator+(dtype a){
//     numcpp<dtype> ret = numcpp<dtype>(size);
//     #pragma omp parallel for
//     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] + a;
//     return ret;
// }

template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator-(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] - a[i];
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator-=(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] - a[i];
    return;
}

// numcpp<dtype> operator-(dtype a){
//     numcpp<dtype> ret = numcpp<dtype>(size);
//     #pragma omp parallel for
//     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] - a;
//     return ret;
// }

template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator*(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] * a[i];
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator*=(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] * a[i];
    return;
}

template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator*(dtype a)
{
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] * a;
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator*=(dtype a)
{
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] * a;
    return;
}

template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator/(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] / a[i];
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator/=(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] / a[i];
    return;
}

template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::operator/(dtype a)
{
    numcpp<dtype> ret = numcpp<dtype>(size);
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ret[i] = ptr[i] / a;
    return ret;
}

template <typename dtype>
void numcpp::numcpp<dtype>::operator/=(dtype a)
{
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = ptr[i] / a;
    return;
}

// dot product
template <typename dtype>
dtype numcpp::numcpp<dtype>::dot(numcpp<dtype> a)
{
    long long int s = a.length();
    if (s != size)
    {
        std::cerr << "Array lengths don't match, exiting...\n";
        exit(1);
    }
    if (s == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    dtype ret = ptr[0] * a[0];
    #pragma omp parallel for
    for (long long int i = 1; i < size; i++)
        ret = ret + ptr[i] * a[i];
    return ret;
}

template <typename dtype>
dtype numcpp::numcpp<dtype>::abs()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    dtype ret = ptr[0] * ptr[0];
    #pragma omp parallel for
    for (long long int i = 1; i < size; i++)
        ret = ret + ptr[i] * ptr[i];
    return sqrt(ret);
}

// printing the array
template <typename dtype>
void numcpp::numcpp<dtype>::print()
{
    if (size == 0)
        std::cout << "NULL\n";
    else if (size == 1)
        std::cout << "[" << ptr[0] << "]\n";
    else
    {
        std::cout << "[";
        for (long long int i = 0; i < size - 1; i++)
            std::cout << ptr[i] << ", ";
        std::cout << ptr[size - 1] << "]\n";
    }
    return;
}

// slice (a feature similar yet different to the one in python)
template <typename dtype>
numcpp::numcpp<dtype> numcpp::numcpp<dtype>::slice(long long int start, long long int stop, long long int step)
{
    if (stop < 0)
    {
        stop = size + stop;
    }
    if (start < 0)
    {
        start = size + start;
    }
    numcpp<dtype> retval;
    if (start < 0 || start >= size)
    {
        std::cerr << "Start index out of bounds, exiting...\n";
        exit(1);
    }
    if (stop < 0 || stop >= size)
    {
        std::cerr << "Stop index out of bounds, exiting...\n";
        exit(1);
    }
    if (step == 0)
    {
        std::cerr << "Step size cannot be zero, exiting...\n";
        exit(1);
    }
    if (stop > start)
    {
        if (step < 0)
        {
            std::cerr << "Invalid step size, exiting...\n";
            exit(1);
        }
        #pragma omp parallel for
        for (long long int i = start; i <= stop; i = i + step)
            retval.append(ptr[i]);
    }
    else if (stop < start)
    {
        if (step > 0)
        {
            std::cerr << "Invalid step size, exiting...\n";
            exit(1);
        }
        #pragma omp parallel for
        for (long long int i = start; i >= stop; i = i + step)
            retval.append(ptr[i]);
    }
    else if (stop == start)
        retval.append(ptr[start]);
    return retval;
}

template <typename dtype>
dtype numcpp::numcpp<dtype>::mean()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    dtype a = ptr[0];
    dtype n = size;
    #pragma omp parallel for
    for (long long int i = 1; i < size; i++)
        a = a + ptr[i];
    return a / n;
}

// pending work
// numcpp sort(){
//     if (size == 0){
//         std::cout << "Array size NULL, exiting ...";
//         exit(0);
//     }
//     float arr[size];
//     for(int i = 0; i < size; i++){
//         arr[i] = ptr[i];
//     }
//     mergeSort(arr, 0, size - 1);
//     numcpp retval(arr, size);
//     return retval;
// }

// float median(){
//     if (size == 0){
//         std::cout << "Array size NULL, exiting ...";
//         exit(0);
//     }
//     float arr[size];
//     for(int i = 0; i < size; i++){
//         arr[i] = ptr[i];
//     }
//     mergeSort(arr, 0, size - 1);
//     if (size % 2 == 0){
//         return (arr[size / 2 - 1] + arr[size / 2]);
//     }
//     else {
//         return (arr[(size - 1) / 2]);
//     }
// }

// maximum and minimum elements in the array
template <typename dtype>
dtype numcpp::numcpp<dtype>::max()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    dtype retval = ptr[0];
    // #pragma omp parallel for // pending work
    for (long long int i = 1; i < size; i++)
    {
        if (ptr[i] > retval)
            retval = ptr[i];
    }
    return retval;
}

template <typename dtype>
dtype numcpp::numcpp<dtype>::min()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    dtype retval = ptr[0];
    // #pragma omp parallel for // pending work
    for (long long int i = 1; i < size; i++)
    {
        if (ptr[i] < retval)
            retval = ptr[i];
    }
    return retval;
}

// indexes of maximum and minimum elements in the array
template <typename dtype>
long long int numcpp::numcpp<dtype>::argmax()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    long long int retval = 0;
    // #pragma omp parallel for // pending work
    for (long long int i = 1; i < size; i++)
    {
        if (ptr[i] > retval)
            retval = i;
    }
    return retval;
}

template <typename dtype>
long long int numcpp::numcpp<dtype>::argmin()
{
    if (size == 0)
    {
        std::cerr << "Array length zero, exiting...\n";
        exit(3);
    }
    long long int retval = 0;
    // #pragma omp parallel for // pending work
    for (long long int i = 1; i < size; i++)
    {
        if (ptr[i] < retval)
            retval = i;
    }
    return retval;
}

template <typename dtype>
void numcpp::numcpp<dtype>::elemwise_update(const std::function<dtype(dtype)> &func)
{
    #pragma omp parallel for
    for (long long int i = 0; i < size; i++)
        ptr[i] = func(ptr[i]);
}

// memory being leaked !!
// what exactly does this do?
template <typename dtype>
void numcpp::linspace(dtype l, dtype f, long long int n)
{
    long long int size = n;
    long long int max_size = n;
    dtype *ptr = new dtype[size];
    double step_size = (l - f) / n;
    #pragma omp parallel for
    for (long long int i = 0; i < n; i++)
        ptr[i] = l + step_size * i;
    return;
}

#endif