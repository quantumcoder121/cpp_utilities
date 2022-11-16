#include <cppdl.h>
#include <iostream>
#include <cstdlib>

cppdl::neuron::neuron()
{
    bias = 0;
    activation_func = "none";
}

cppdl::neuron::neuron(long long int n_inputs, std::string a_func): weights(numcpp::numcpp<double>(n_inputs, 0))
{
    bias = 0;
    activation_func = a_func;
}

double cppdl::neuron::output(numcpp::numcpp<double> &input)
{
    if (input.length() != weights.length())
    {
        std::cerr << "Input size not matching with the weight vector size, exiting ...\n";
        exit(0);
    }
    return weights.dot(input) + bias;
}

cppdl::layer::layer(std::string layer_type)
{
    type = layer_type;
}

// a_func isn't used here?
cppdl::dense::dense(int n_inputs, int n_outputs, std::string a_func)
{
    neurons = std::vector<cppdl::neuron>();
    for (int i = 0; i < n_outputs; i++)
    {
        cppdl::neuron new_neuron(n_inputs, a_func);
        neurons.push_back(new_neuron);
    }
    inputs = n_inputs;
    outputs = n_outputs;
    activation_func = a_func;
}


std::vector<double> cppdl::dense::output(numcpp::numcpp<double> &input)
{
    if (input.length() != inputs)
    {
        std::cerr << "Input sizes not matching, exiting ...\n";
        exit(0);
    }
    std::vector<double> ret;
    for (int i = 0; i < outputs; i++)
    {
        ret.push_back(neurons[i].output(input));
    }
    return ret;
}

cppdl::input::input(int n_inputs)
{
    inputs = n_inputs;
}

numcpp::numcpp<double> cppdl::input::output(numcpp::numcpp<double> &input)
{
    if (input.length() != inputs)
    {
        std::cerr << "Input sizes not matching, exiting ...\n";
        exit(0);
    }
    return input;
}