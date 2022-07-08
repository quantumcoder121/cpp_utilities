#include<iostream>
#include<cstdlib>

using namespace std;

#define MAX_SIZE 1024

void merge(float array[], int const left, int const mid, int const right) {

	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto *leftArray = new float[subArrayOne], *rightArray = new float[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void mergeSort(float array[], int const begin, int const end) {

	if (begin >= end) return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

class numcpp{

    private:
        float *ptr;
        int size;

    public:

        numcpp(){
            size = 0;
            ptr = NULL;
        }

        numcpp(float *p, int s){
            size = s;
            ptr = NULL;
            if (s != 0){
                ptr = new float[MAX_SIZE];
                for (int i = 0; i < s; i++){
                    ptr[i] = p[i];
                }
            }
        }

        int length(){
            return size;
        }

        float* arr(){
            return ptr;
        }

        float& operator[](int index){
            if (index < 0){
                index = size + index;
            }
            if (index >= size || index < 0){
                cout << "Index out of bound, exiting ..." << endl;
                exit(0);
            }
            return ptr[index];
        }

        numcpp operator+(numcpp a){
            int s = a.length();
            float *p = a.arr();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            float q[size];
            for (int i = 0; i < size; i++){
                q[i] = p[i] + ptr[i];
            }
            return numcpp(q, size);
        }

        numcpp operator-(numcpp a){
            int s = a.length();
            float *p = a.arr();
            if (s != size){
                cout << "Lengths don't match, exiting ...";
                exit(0);
            }
            float q[size];
            for (int i = 0; i < size; i++){
                q[i] = ptr[i] - p[i];
            }
            return numcpp(q, size);
        }

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

        numcpp slice(int start = 0, int stop = -1, int step = 1){
            if (stop < 0){
                stop = size + stop;
            }
            if (start < 0){
                start = size + start;
            }
            float *p = new float[size];
            int j = 0;
            if (start < 0 || start >= size){
                cout << "Start Index out of bound, exiting ..." << endl;
                exit(0);
            }
            if (stop < 0 || stop >= size){
                cout << "Stop Index out of bound, exiting ..." << endl;
                exit(0);
            }
            if (step == 0){
                cout << "Step size cannot be zero, exiting ..." << endl;
                exit(0);
            }
            if (stop > start){
                if (step < 0){
                    cout << "Invalid step size, exiting ..." << endl;
                    exit(0);
                }
                for(int i = start; i <= stop; i = i + step){
                    p[j] = ptr[i];
                    j++;
                }
            }
            else if (stop < start){
                if (step > 0){
                    cout << "Invalid step size, exiting ..." << endl;
                    exit(0);
                }
                for(int i = start; i >= stop; i = i + step){
                    p[j] = ptr[i];
                    j++;
                }
            }
            else if (stop == start){
                p[0] = ptr[start];
                j = 1;
            }
            numcpp retval(p, j);
            return retval;
        }

        float mean(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            float a = 0.0;
            float n = size;
            for (int i = 0; i < size; i++){
                a = a + ptr[i];
            }
            return a/n;
        }

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

        float max(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            float retval = ptr[0];
            if (size == 1){
                return retval;
            }
            for(int i = 1; i < size; i++){
                if (ptr[i] > retval){
                    retval = ptr[i];
                }
            }
            return retval;
        }

        float min(){
            if (size == 0){
                cout << "Array size NULL, exiting ...";
                exit(0);
            }
            float retval = ptr[0];
            if (size == 1){
                return retval;
            }
            for(int i = 1; i < size; i++){
                if (ptr[i] < retval){
                    retval = ptr[i];
                }
            }
            return retval;
        }

        void append(float a){
            if (size == 0){
                ptr = new float[MAX_SIZE];
                ptr[0] = a;
                return;
            }
            if (size > MAX_SIZE){
                cout << "Array size exceeds maximum size, exiting ..." << endl;
                exit(0);
            }
            size = size + 1;
            ptr[size - 1] = a;
            return;
        }
};
