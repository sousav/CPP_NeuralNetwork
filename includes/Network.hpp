//
// Network.hpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP/BasicNeural/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Sun Apr 23 19:19:17 2017 Sousa Victor
// Last update Mon May  1 23:29:26 2017 Sousa Victor
//

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#include "NetworkException.hpp"
#include "NetworkTrainer.hpp"
#include "Layer.hpp"

namespace Neural {

    class INetwork {

    public:
        virtual ~INetwork() {};

        virtual void train(INetworkTrainer const &trainer) = 0;

        virtual void feedForward(const std::vector<double> &inputVals) = 0;
        virtual std::vector<double> const getResults() const = 0;
        virtual void backProp(const std::vector<double> &targetVals) = 0;
        virtual double getRecentAverageError(void) const = 0;

        virtual std::vector<Neural::Layer> const &getLayer() const = 0;
        virtual unsigned getLayerCount() const = 0;
        virtual unsigned getInputCount() const = 0;
        virtual unsigned getOutputCount() const = 0;
        virtual unsigned getNeuronCount() const = 0;
        virtual unsigned getConnectionCount() const = 0;

    };

    class Network : public INetwork {

    public:
        Network(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor = 100);
        ~Network();
        Network(const Network &network);
        Network &operator =(const Network &network);

        void train(INetworkTrainer const &trainer);

        void feedForward(const std::vector<double> &inputVals);
        std::vector<double> const getResults() const;
        void backProp(const std::vector<double> &targetVals);
        double getRecentAverageError(void) const;

        std::vector<Neural::Layer> const &getLayer() const;
        unsigned getLayerCount() const;
        unsigned getInputCount() const;
        unsigned getOutputCount() const;
        unsigned getNeuronCount() const;
        unsigned getConnectionCount() const;

    private:
        std::vector<Layer> _layers; // _layers[layerNum][neuronNum]
        double _error;
        double _recentAverageError;
        double _recentAverageSmoothingFactor;

        void showVectorVals(std::string const &label, std::vector<double> const &v) const;

    };

}

std::ostream &operator<<(std::ostream& os, const Neural::INetwork &network);

#else

namespace Neural {

    class Network;

}

#endif /*NETWORK_HPP_*/
