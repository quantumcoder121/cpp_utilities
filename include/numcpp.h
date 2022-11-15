#ifndef ML_NUMCPP
#define ML_NUMCPP


#include <math.h>
#include <functional>



// pending work
// void merge(vector<double> arr, int f, int m, int l){
//     vector<double> l_arr;
//     vector<double> r_arr;
//     for (int i = f; i <= m; i++){
//         l_arr.push_back(arr[i]);
//     }
//     for (int i = m + 1; i <= l; i++){
//         r_arr.push_back(arr[i]);
//     }
//     int i = 0;
//     int j = 0;
//     int k = 0;
//     while (j < m - f + 1 && k < l - m){
//         if (l_arr[j] < r_arr[k]){
//             arr[i] = l_arr[j];
//             j++;
//         }
//         else {
//             arr[i] = r_arr[k];
//             k++;
//         }
//         i++;
//     }
//     return;
// }

// void merge_sort(vector<double> arr, int f, int l){
//     if (l - f == 1){
//         int min;
//         int max;
//         if (arr[f] < arr[l]){
//             min = arr[f];
//             max = arr[l];
//         }
//         else {
//             min = arr[l];
//             max = arr[f];
//         }
//         return;
//     }
//     int m = (f + l) / 2;
//     merge_sort(arr, f, m);
//     merge_sort(arr, m + 1, l);
//     merge(arr, f, m, l);
//     return;
// }

namespace numcpp {
    template <typename dtype>
    class numcpp {
        dtype *ptr;
        long long int size;
        long long int max_size;

        public:
            // default constructor
            numcpp();

            // copy constructor
            numcpp(const numcpp<dtype> &);

            // following three could be potentially redundant constructors
            // leads to template resolution problems!!
            // also why??
            // numcpp(int);

            // numcpp(long int);

            numcpp(long long int);

            // following three are the standard set of constructors for now
            numcpp(int, dtype);

            numcpp(long int, dtype);

            numcpp(long long int, dtype);

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
            long long int length() const;

            // element access operator
            dtype &operator[](int);

            dtype &operator[](long int);

            dtype &operator[](long long int);

            // const element access operator
            const dtype &operator[](int) const;

            const dtype &operator[](long int) const;

            const dtype &operator[](long long int) const;

            // adding extra element to the array (memory allocation update as new_size = 2 * size)
            void append(dtype);

            // element wise operations
            numcpp<dtype> operator+(numcpp<dtype>);

            void operator+=(numcpp<dtype>);

            // numcpp<dtype> operator+(dtype a){
            //     numcpp<dtype> ret = numcpp<dtype>(size);
            //     #pragma omp parallel for
            //     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] + a;
            //     return ret;
            // }

            numcpp<dtype> operator-(numcpp<dtype>);

            void operator-=(numcpp<dtype>);

            // numcpp<dtype> operator-(dtype a){
            //     numcpp<dtype> ret = numcpp<dtype>(size);
            //     #pragma omp parallel for
            //     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] - a;
            //     return ret;
            // }

            numcpp<dtype> operator*(numcpp<dtype>);

            void operator*=(numcpp<dtype>);

            numcpp<dtype> operator*(dtype);

            void operator*=(dtype);

            numcpp<dtype> operator/(numcpp<dtype>);

            void operator/=(numcpp<dtype>);

            numcpp<dtype> operator/(dtype);

            void operator/=(dtype);

            // dot product
            dtype dot(numcpp<dtype>);

            dtype abs();

            // printing the array
            void print();

            // slice (a feature similar yet different to the one in python)
            numcpp<dtype> slice(long long int start = 0, long long int stop = -1, long long int step = 1);

            dtype mean();

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
            dtype max();

            dtype min();

            // indexes of maximum and minimum elements in the array
            long long int argmax();

            long long int argmin();

            void elemwise_update(const std::function<dtype(dtype)> &);
    };

    template <typename dtype> void linspace(dtype l, dtype f = 0, long long int n = 1);
}

#include <numcpp.ipp>

#endif