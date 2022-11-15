#ifndef MP_CPPDL_H
#define ML_CPPDL_H

#include <vector>
#include <string>
#include <numcpp.h>

// using namespace std;

namespace cppdl
{
    class neuron
    {
        // weights and bias
        numcpp::numcpp<double> weights;
        double bias;

        // metadata
        std::string activation_func;

        public:
            neuron();

            neuron(long long int, std::string a_func = "none");

            double output(numcpp::numcpp<double> &);
    };

    class layer
    {

        // metadata
        std::string type;

        public:
            layer(std::string layer_type = "none");
    };

    class dense : public layer
    {

        // neurons
        std::vector<neuron> neurons;

        // metadata
        long long int inputs;
        long long int outputs;
        std::string activation_func;

        public:
            dense(int, int, std::string a_func = "none");

            std::vector<double> output(numcpp::numcpp<double> &);
    };

    class input : public layer
    {

        // metadata
        long long int inputs;

        public:
            input(int);

            numcpp::numcpp<double> output(numcpp::numcpp<double> &);
    };

}
/*
class nn{

    vector<vector<neuron>> net;

    public:

        nn(vector<int> n_neurons, )
};
*/

#endif