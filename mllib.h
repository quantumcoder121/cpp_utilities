#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

class linear_regression{

    // weights and biases
    vector<double> weights;
    double bias;

    // metadata
    int inputs;

    public:

        linear_regression(int n_inputs){
            weights = vector<double> (n_inputs, 0);
            inputs = n_inputs;
        }

        train(vector<vector<double>> features, vector<double> labels){
            if (features.size() != labels.size()){
                cout << "Number of features and labels not matching, exiting ...\n";
                exit(1);
            }
            if (features[0].size() != inputs){
                cout << "Number of features and weights not matching, exiting ...\n";
                exit(1);
            }
            
        }
};