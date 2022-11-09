#include<iostream>
#include<cstdlib>

using namespace std;

#define MAX_SIZE 1024

/*
void merge(vector<double> arr, int f, int m, int l){
    vector<double> l_arr;
    vector<double> r_arr;
    for (int i = f; i <= m; i++){
        l_arr.push_back(arr[i]);
    }
    for (int i = m + 1; i <= l; i++){
        r_arr.push_back(arr[i]);
    }
    int i = 0;
    int j = 0;
    int k = 0;
    while (j < m - f + 1 && k < l - m){
        if (l_arr[j] < r_arr[k]){
            arr[i] = l_arr[j];
            j++;
        }
        else {
            arr[i] = r_arr[k];
            k++;
        }
        i++;
    }
    return;
}

void merge_sort(vector<double> arr, int f, int l){
    if (l - f == 1){
        int min;
        int max;
        if (arr[f] < arr[l]){
            min = arr[f];
            max = arr[l];
        }
        else {
            min = arr[l];
            max = arr[f];
        }
        return;
    }
    int m = (f + l) / 2;
    merge_sort(arr, f, m);
    merge_sort(arr, m + 1, l);
    merge(arr, f, m, l);
    return;
}
*/

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

        // following three could be potentially redundant constructors
        numcpp(int s){
            if (s <= 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        numcpp(long int s){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        numcpp(long long int s){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            size = s;
            max_size = s;
        }

        // following three are the standard set of constructors for now
        numcpp(int s, dtype a){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            for (int i = 0; i < s; i++){
                ptr[i] = a;
            }
            size = s;
            max_size = s;
        }

        numcpp(long int s, dtype a){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            for (int i = 0; i < s; i++){
                ptr[i] = a;
            }
            size = s;
            max_size = s;
        }

        numcpp(long long int s, dtype a){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            for (int i = 0; i < s; i++){
                ptr[i] = a;
            }
            size = s;
            max_size = s;
        }

        // unsafe constructor
        numcpp(long long int s, dtype* a){
            if (s < 0 || s == 0){
                cout << "Input size is not positive, exiting ...";
                exit(1);
            }
            ptr = new dtype[s];
            for (int i = 0; i < s; i++){
                ptr[i] = a[i];
            }
            size = s;
            max_size = s;
        }

        // size/length of the array
        long long int length(){
            return size;
        }

        // element access operator
        dtype& operator[](int index){
            if (index < 0){
                index = size + index;
            }
            if (index >= size || index < 0){
                cout << "Index out of bound, exiting ..." << endl;
                exit(0);
            }
            return ptr[index];
        }

        dtype& operator[](long int index){
            if (index < 0){
                index = size + index;
            }
            if (index >= size || index < 0){
                cout << "Index out of bound, exiting ..." << endl;
                exit(0);
            }
            return ptr[index];
        }

        dtype& operator[](long long int index){
            if (index < 0){
                index = size + index;
            }
            if (index >= size || index < 0){
                cout << "Index out of bound, exiting ..." << endl;
                exit(0);
            }
            return ptr[index];
        }

        // adding extra element to the array (memory allocation update as new_size = 2 * size)
        void append(dtype a){
            if (size == max_size){
                dtype* temp = new dtype[max_size];
                for (long long int i = 0; i < size; i++){
                    temp[i] = ptr[i];
                }
                ptr = new dtype[2 * max_size];
                for (long long int i = 0; i < size; i++){
                    ptr[i] = temp[i];
                }
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
                cout << "Lengths don't match, exiting ...\n";
                exit(0);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] + a[i];
            }
            return ret;
        }

        numcpp<dtype> operator+(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] + a;
            }
            return ret;
        }

        numcpp<dtype> operator-(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] - a[i];
            }
            return ret;
        }

        numcpp<dtype> operator-(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] - a;
            }
            return ret;
        }

        numcpp<dtype> operator*(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] * a[i];
            }
            return ret;
        }

        numcpp<dtype> operator*(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] * a;
            }
            return ret;
        }


        numcpp<dtype> operator/(numcpp<dtype> a){
            long long int s = a.length();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] / a[i];
            }
            return ret;
        }

        numcpp<dtype> operator/(dtype a){
            numcpp<dtype> ret = numcpp<dtype>(size);
            for (long long int i = 0; i < size; i++){
                ret[i] = ptr[i] / a;
            }
            return ret;
        }

        // dot product
        dtype dot(numcpp a){
            long long int s = a.length();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            if (s == 0){
                cout << "Array size zero, exiting ...";
            }
            dtype ret = ptr[0] * a[0];
            for (long long int i = 1; i < size; i++){
                ret = ret + ptr[i] * a[i];
            }
            return ret;
        }

        // printing the array
        void print(){
            if (size == 0){
                cout << "NULL" << endl;
            }
            else if (size == 1){
                cout << "[" << ptr[0] << "]" << endl;
            }
            else {
                cout << "[";
                for (int i = 0; i < size - 1; i++){
                    cout << ptr[i] << ", ";
                }
                cout << ptr[size - 1] << "]" << endl;
            }
        }

        // slice (a feature similar yet different to the one in python)
        numcpp<dtype> slice(long long int start = 0, long long int stop = -1, long long int step = 1){
            if (stop < 0){
                stop = size + stop;
            }
            if (start < 0){
                start = size + start;
            }
            // dtype p[size];
            numcpp<dtype> retval;
            // int j = 0;
            if (start < 0 || start >= size){
                cout << "Start index out of bound, exiting ..." << endl;
                exit(1);
            }
            if (stop < 0 || stop >= size){
                cout << "Stop index out of bound, exiting ..." << endl;
                exit(1);
            }
            if (step == 0){
                cout << "Step size cannot be zero, exiting ..." << endl;
                exit(1);
            }
            if (stop > start){
                if (step < 0){
                    cout << "Invalid step size, exiting ..." << endl;
                    exit(1);
                }
                for(long long int i = start; i <= stop; i = i + step){
                    retval.append(ptr[i]);
                    // j++;
                }
            }
            else if (stop < start){
                if (step > 0){
                    cout << "Invalid step size, exiting ..." << endl;
                    exit(1);
                }
                for(long long int i = start; i >= stop; i = i + step){
                    retval.append(ptr[i]);
                    // j++;
                }
            }
            else if (stop == start){
                retval.append(ptr[start]);
                // j++;
            }
            // numcpp<dtype> retval = numcpp<dtype>(j, p);
            // delete[] p;
            return retval;
        }

        dtype mean(){
            if (size == 0){
                cout << "Array size zero, exiting ...";
                exit(0);
            }
            dtype a = ptr[0];
            dtype n = size;
            for (int i = 1; i < size; i++){
                a = a + ptr[i];
            }
            return a / n;
        }

        /*
        numcpp sort(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            float arr[size];
            for(int i = 0; i < size; i++){
                arr[i] = ptr[i];
            }
            mergeSort(arr, 0, size - 1);
            numcpp retval(arr, size);
            return retval;
        }
        
        float median(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            float arr[size];
            for(int i = 0; i < size; i++){
                arr[i] = ptr[i];
            }
            mergeSort(arr, 0, size - 1);
            if (size % 2 == 0){
                return (arr[size / 2 - 1] + arr[size / 2]);
            }
            else {
                return (arr[(size - 1) / 2]);
            }
        }
        */

        // maximum and minimum elements in the array
        dtype max(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            dtype retval = ptr[0];
            for(int i = 1; i < size; i++){
                if (ptr[i] > retval){
                    retval = ptr[i];
                }
            }
            return retval;
        }

        dtype min(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            dtype retval = ptr[0];
            for(int i = 1; i < size; i++){
                if (ptr[i] < retval){
                    retval = ptr[i];
                }
            }
            return retval;
        }

        void elemwise_update(dtype (*func)dtype){
            for (long long int i = 0; i < size; i++){
                ptr[i] = func(ptr[i]);
            }
        }
};