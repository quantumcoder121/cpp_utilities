#include<iostream>
#include<cstdlib>
#include<vector>
#include"numcpp.h"
#include"math.h"

using namespace std;

class neuron{

    // weights and bias
    numcpp<double> weights;
    double bias;

    // metadata
    string activation_func;

    public:

        neuron(){
            bias = 0;
            activation_func = "none";
        }

        neuron(long long int n_inputs, string a_func = "none"){
            weights = numcpp<double>(n_inputs, 0);
            bias = 0;
            activation_func = "none";
        }

        double output(numcpp<double>& input){
            if (input.length() != weights.length()){
                cout << "Input size not matching with the weight vector size, exiting ...";
                exit(0);
            }
            return weights.dot(input) + bias;
        }
};

class layer{
    
    // metadata
    string type;

    public:

        layer(string layer_type = "none"){
            type = layer_type;
        }
};

class dense : public layer{

    // neurons
    vector<neuron> neurons;
    
    // metadata
    long long int inputs;
    long long int outputs;
    string activation_func;

    public:

        dense(int n_inputs, int n_outputs, string a_func = "none"){
            neurons = vector<neuron>();
            for (int i = 0; i < n_outputs; i++){
                neuron new_neuron(n_inputs, a_func);
                neurons.push_back(new_neuron);
            }
            inputs = n_inputs;
            outputs = n_outputs;
            activation_func = a_func;
        }

        vector<double> output(numcpp<double>& input){
            if (input.length() != inputs){
                cout << "Input sizes not matching, exiting ...";
                exit(0);
            }
            vector<double> ret;
            for (int i = 0; i < outputs; i++){
                ret.push_back(neurons[i].output(input));
            }
        }
};

class input : public layer{

    // metadata
    long long int inputs;

    public:

        input(int n_inputs){
            inputs = n_inputs;
        }

        numcpp<double> output(numcpp<double>& input){
            if (input.length() != inputs){
                cout << "Input sizes not matching, exiting ...";
                exit(0);
            }
            return input;
        }
};

/*
class nn{

    vector<vector<neuron>> net;

    public:

        nn(vector<int> n_neurons, )
};
*/