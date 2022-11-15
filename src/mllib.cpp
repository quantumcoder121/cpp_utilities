#include <mllib.h>
#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <ctime>

double mllib::mse_loss(double predicted, double actual)
{
    return (predicted - actual) * (predicted - actual);
}

mllib::linear_regression::linear_regression(int n_inputs): weights(numcpp::numcpp<double>(n_inputs, 0))
{
    inputs = n_inputs;
}

void mllib::linear_regression::sgd_train(numcpp::numcpp<numcpp::numcpp<double> > features, numcpp::numcpp<double> labels, double lr, long long int epochs)
{
    if (features.length() != labels.length())
    {
        std::cerr << "Number of features and labels not matching, exiting ...\n";
        exit(1);
    }
    long long int batch_size = features.length();
    double h = math::bin([](double x) -> double { return x * x - DBL_EPSILON; }, 0, 1);
    double curr_loss = 0;
    srand(time(0));
    for (long long int i = 0; i < epochs; i++)
    {
        long long int j = rand() % batch_size;
        if (features[j].length() != inputs)
        {
            std::cerr << "Number of features and weights not matching, exiting ...\n";
            exit(1);
        }
        numcpp::numcpp<double> feature = features[j];
        double label = labels[j];
        double predicted = weights.dot(feature) + bias;
        curr_loss = mllib::mse_loss(predicted, label);
        if (i > 0)
            std::cout << "Training Loss: " << curr_loss << " | " << "Epoch: " << i << '\n';
        feature.elemwise_update([predicted, h, label](double x) -> double { return mllib::mse_loss(predicted + x * h, label); });
        weights -= (feature - curr_loss)*lr / h;
    }
    std::cout << "Training Loss: " << curr_loss << " | " << "Epoch: " << epochs << '\n';
    return;
}
