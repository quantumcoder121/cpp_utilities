#include<iostream>
#include<cstdlib>
#include"numcpp.h"
#include<cfloat>
#include"math.h"
#include<ctime>

using namespace std;

double mse_loss(double predicted, double actual){
    return (predicted - actual) * (predicted - actual);
}

class linear_regression{

    // weights and biases
    numcpp<double> weights;
    double bias;

    // metadata
    int inputs;

    public:

        linear_regression(int n_inputs){
            weights = numcpp<double> (n_inputs, 0);
            inputs = n_inputs;
        }

        void sgd_train(numcpp<numcpp<double>> features, numcpp<double> labels, double lr = 0.01, long long int epochs = 100, double (*func)(double, double)){
            if (features.length() != labels.length()){
                cout << "Number of features and labels not matching, exiting ...\n";
                exit(1);
            }
            long long int batch_size = features.length();
            double h = bin([](double x) -> double{return x * x - DBL_EPSILON;}, 0, 1);
            double curr_loss = 0;
            srand(time(0));
            for (long long int i = 0, i < epochs, i++){
                long long int j = rand() % batch_size;
                if (features[j].length() != inputs){
                    cout << "Number of features and weights not matching, exiting ...\n";
                    exit(1);
                }
                numcpp<double> feature = features[j];
                double label = labels[j];
                double predicted = weights.dot(feature) + bias;
                curr_loss = func(predicted, label);
                if (i > 0) cout << "Training Loss: " + curr_loss + " | " + "Epoch: " + i << endl;
                feature.elemwise_update([](double x){return func(predicted + x * h, label)});
                weights = weights - lr * (feature - curr_loss) / h;
            }
            cout << "Training Loss: " + curr_loss + " | " + "Epoch: " + epochs << endl;
            return;
        }
};