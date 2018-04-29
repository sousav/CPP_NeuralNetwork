/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:35
 */


#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Layer.hpp"

namespace Neural {

    class INeuron {

    public: struct Connection {
            double weight;
            double deltaWeight;
        };

    public:
        ~INeuron() {};

        virtual void feedForward(const Neural::Layer &prevLayer) = 0;
        virtual void calcOutputGradients(double targetVal) = 0;
        virtual void calcHiddenGradients(const Neural::Layer &nextLayer) = 0;
        virtual void updateInputWeights(Neural::Layer &prevLayer) = 0;

        virtual void setConnection(unsigned index, Connection const &data) = 0;
        virtual std::vector<Connection> const &getConnection() const = 0;
        virtual unsigned getConnectionCount() const = 0;

    };

    class Neuron : private INeuron {

    public:
        Neuron(unsigned numOutputs, unsigned myIndex, double eta = 0.15, double alpha = 0.5);
        ~Neuron();
        Neuron(const Neuron &neuron);
        Neuron &operator =(const Neuron &neuron);

        void setOutputVal(double val);
        double getOutputVal(void) const;

        void feedForward(const Neural::Layer &prevLayer);
        void calcOutputGradients(double targetVal);
        void calcHiddenGradients(const Neural::Layer &nextLayer);
        void updateInputWeights(Neural::Layer &prevLayer);

        void setConnection(unsigned index, Connection const &data);
        std::vector<Connection> const &getConnection() const;
        unsigned getConnectionCount() const;

    private:
        double _eta;   // [0.0..1.0] overall net training rate
        double _alpha; // [0.0..n] multiplier of last weight change (momentum)
        double _outputVal;
        std::vector<Connection> _outputWeights;
        unsigned _myIndex;
        double _gradient;

        double transferFunction(double x) const;
        double transferFunctionDerivative(double x) const;
        double randomWeight(void) const;
        double sumDOW(const Neural::Layer &nextLayer) const;

    };

}

#else

namespace Neural {

    class Neuron;

}

#endif /*NEURON_HPP*/
