#include<iostream>
#include<cstdlib>
#include"math.h"

#define MAX_SIZE 1024

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

template <typename dtype> class numcpp{
 
        dtype* ptr;
        long long int size;
        long long int max_size;

    public:

        // default constructor
        numcpp(){
            ptr = new dtype[1];
            size = 0;
            max_size = 1;
        }

        // copy constructor
        numcpp(numcpp<dtype> &a){
            long long int s = a.length();
            ptr = new dtype[s];
            size = s;
            max_size = s;
            #pragma omp parallel for
            for (long long int i = 0; i < s; i++) ptr[i] = a[i];
        }

        // following three could be potentially redundant constructors
        numcpp(int s){
            if (s <= 0){
                std::cout << "Input length is not positive, exiting...\n";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        numcpp(long int s){
            if (s < 0 || s == 0){
                std::cout << "Input length is not positive, exiting...\n";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        numcpp(long long int s){
            if (s < 0 || s == 0){
                std::cout << "Input length is not positive, exiting...\n";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        // following three are the standard set of constructors for now
        numcpp(int s, dtype a){
            if (s < 0 || s == 0){
                std::cout << "Input length is not positive, exiting...\n";
                exit(1);
            }
            ptr = new dtype[s];
            #pragma omp parallel for
            for (long long int i = 0; i < s; i++) ptr[i] = a;
            size = s;
            max_size = s;
        }

        numcpp(long int s, dtype a){
            if (s < 0 || s == 0){
                std::cout << "Input length is not positive, exiting...\n";
                exit(1);
            }
            ptr = new dtype[s];
            #pragma omp parallel for
            for (long long int i = 0; i < s; i++) ptr[i] = a;
            size = s;
            max_size = s;
        }

        numcpp(long long int s, dtype a){
            if (s < 0 || s == 0){
                std::cout << "Input length is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            #pragma omp parallel for
            for (long long int i = 0; i < s; i++) ptr[i] = a;
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
        long long int length(){
            return size;
        }

        // element access operator
        dtype& operator[](int index){
            if (index < 0) index = size + index;
            if (index >= size || index < 0){
                std::cout << "Index out of bounds, exiting...\n";
                exit(1);
            }
            return ptr[index];
        }

        dtype& operator[](long int index){
            if (index < 0) index = size + index;
            if (index >= size || index < 0){
                std::cout << "Index out of bounds, exiting...\n";
                exit(1);
            }
            return ptr[index];
        }

        dtype& operator[](long long int index){
            if (index < 0) index = size + index;
            if (index >= size || index < 0){
                std::cout << "Index out of bounds, exiting...\n";
                exit(1);
            }
            return ptr[index];
        }

        // adding extra element to the array (memory allocation update as new_size = 2 * size)
        void append(dtype a){
            if (size == MAX_SIZE){
                std::cout << "Exceeding length limit, exiting...\n";
                exit(2);
            }
            if (size == max_size){
                dtype* temp = new dtype[max_size];
                #pragma omp parallel for
                for (long long int i = 0; i < size; i++) temp[i] = ptr[i];
                ptr = new dtype[2 * max_size];
                #pragma omp parallel for
                for (long long int i = 0; i < size; i++) ptr[i] = temp[i];
                delete[] temp;
                max_size = 2 * max_size;
            }
            ptr[size] = a;
            size = size + 1;
            return;
        }

        // element wise operations
        numcpp<dtype> operator+(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] + a[i];
            return ret;
        }

        void operator+=(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] + a[i];
            return;
        }

        // numcpp<dtype> operator+(dtype a){
        //     numcpp<dtype> ret = numcpp<dtype>(size);
        //     #pragma omp parallel for
        //     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] + a;
        //     return ret;
        // }

        numcpp<dtype> operator-(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] - a[i];
            return ret;
        }

        void operator-=(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] - a[i];
            return;
        }

        // numcpp<dtype> operator-(dtype a){
        //     numcpp<dtype> ret = numcpp<dtype>(size);
        //     #pragma omp parallel for
        //     for (long long int i = 0; i < size; i++) ret[i] = ptr[i] - a;
        //     return ret;
        // }

        numcpp<dtype> operator*(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] * a[i];
            return ret;
        }

        void operator*=(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] * a[i];
            return;
        }

        numcpp<dtype> operator*(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] * a;
            return ret;
        }

        numcpp<dtype> operator*=(dtype a){
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] * a;
            return;
        }

        numcpp<dtype> operator/(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] / a[i];
            return ret;
        }

        void operator/=(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] / a[i];
            return;
        }

        numcpp<dtype> operator/(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ret[i] = ptr[i] / a;
            return ret;
        }

        numcpp<dtype> operator/=(dtype a){
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = ptr[i] / a;
            return;
        }

        // dot product
        dtype dot(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                std::cout << "Array lengths don't match, exiting...\n";
                exit(1);
            }
            if (s == 0){
                std::cout << "Array length zero, exiting...\n";
                exit(3);
            }
            dtype ret = ptr[0] * a[0];
            #pragma omp parallel for
            for (long long int i = 1; i < size; i++) ret = ret + ptr[i] * a[i];
            return ret;
        }

        dtype abs(){
            if (size == 0){
                std::cout << "Array length zero, exiting...\n";
                exit(3);
            }
            dtype ret = ptr[0] * ptr[0];
            #pragma omp parallel for
            for (long long int i = 1; i < size; i++) ret = ret + ptr[i] * ptr[i];
            return sqrt(ret);
        }

        // printing the array
        void print(){
            if (size == 0) std::cout << "NULL" << endl;
            else if (size == 1) std::cout << "[" << ptr[0] << "]" << endl;
            else {
                std::cout << "[";
                for (long long int i = 0; i < size - 1; i++) std::cout << ptr[i] << ", ";
                std::cout << ptr[size - 1] << "]" << endl;
            }
            return;
        }

        // slice (a feature similar yet different to the one in python)
        numcpp<dtype> slice(long long int start = 0, long long int stop = -1, long long int step = 1){
            if (stop < 0){
                stop = size + stop;
            }
            if (start < 0){
                start = size + start;
            }
            numcpp<dtype> retval;
            if (start < 0 || start >= size){
                std::cout << "Start index out of bounds, exiting...\n";
                exit(1);
            }
            if (stop < 0 || stop >= size){
                std::cout << "Stop index out of bounds, exiting...\n";
                exit(1);
            }
            if (step == 0){
                std::cout << "Step size cannot be zero, exiting...\n";
                exit(1);
            }
            if (stop > start){
                if (step < 0){
                    std::cout << "Invalid step size, exiting...\n";
                    exit(1);
                }
                #pragma omp parallel for
                for(long long int i = start; i <= stop; i = i + step) retval.append(ptr[i]);
            }
            else if (stop < start){
                if (step > 0){
                    std::cout << "Invalid step size, exiting...\n";
                    exit(1);
                }
                #pragma omp parallel for
                for(long long int i = start; i >= stop; i = i + step) retval.append(ptr[i]);
            }
            else if (stop == start) retval.append(ptr[start]);
            return retval;
        }

        dtype mean(){
            if (size == 0){
                std::cout << "Array length zero, exiting ...";
                exit(3);
            }
            dtype a = ptr[0];
            dtype n = size;
            #pragma omp parallel for
            for (long long int i = 1; i < size; i++) a = a + ptr[i];
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
        dtype max(){
            if (size == 0){
                std::cout << "Array length zero, exiting...\n";
                exit(3);
            }
            dtype retval = ptr[0];
            // #pragma omp parallel for // pending work
            for(long long int i = 1; i < size; i++){
                if (ptr[i] > retval) retval = ptr[i];
            }
            return retval;
        }

        dtype min(){
            if (size == 0){
                std::cout << "Array length zero, exiting ...";
                exit(3);
            }
            dtype retval = ptr[0];
            // #pragma omp parallel for // pending work
            for(long long int i = 1; i < size; i++){
                if (ptr[i] < retval) retval = ptr[i];
            }
            return retval;
        }

        // indexes of maximum and minimum elements in the array
        long long int argmax(){
            if (size == 0){
                std::cout << "Array length zero, exiting...\n";
                exit(3);
            }
            long long int retval = 0;
            // #pragma omp parallel for // pending work
            for(long long int i = 1; i < size; i++){
                if (ptr[i] > retval) retval = i;
            }
            return retval;
        }

        long long int argmin(){
            if (size == 0){
                std::cout << "Array length zero, exiting ...";
                exit(3);
            }
            long long int retval = 0;
            // #pragma omp parallel for // pending work
            for(long long int i = 1; i < size; i++){
                if (ptr[i] < retval) retval = i;
            }
            return retval;
        }

        void elemwise_update(dtype (*func)dtype){
            #pragma omp parallel for
            for (long long int i = 0; i < size; i++) ptr[i] = func(ptr[i]);
        }
};

numcpp::void linspace(dtype f = 0, dtype l, long long int n = 1){
    size = n;
    max_size = n;
    ptr = new dtype[s];
    double step_size = (l - f) / n;
    #pragma omp parallel for
    for (long long int i = 0; i < n; i++) ptr[i] = l + step_size * i;
    return;
}