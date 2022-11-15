#ifndef ML_MLLIB_H
#define ML_MLLIB_H


#include <numcpp.h>


// using namespace std;

namespace mllib {
    double mse_loss(double, double);

    class linear_regression {
        // weights and biases
        numcpp::numcpp<double> weights;
        double bias;

        // metadata
        int inputs;

        public:
            linear_regression(int);

            void sgd_train(numcpp::numcpp<numcpp::numcpp<double>>, numcpp::numcpp<double>, double lr = 0.01, long long int epochs = 100);
    };
}

#endif