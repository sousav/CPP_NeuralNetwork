//
// Created by Victor Sousa on 02/01/2020.
//

#ifndef NEURALNETWORK_INETWORK_HPP
#define NEURALNETWORK_INETWORK_HPP

#include "NetworkTrainer.hpp"

namespace Neural {

    class INetwork {

    public:
        virtual ~INetwork() {};

        virtual void train(INetworkTrainer const &trainer) = 0;

        virtual void feedForward(const std::vector<double> &inputVals) = 0;

        virtual std::vector<double> const getResults() const = 0;

        virtual void backProp(const std::vector<double> &targetVals) = 0;

        virtual void errorPlot() const = 0;

    };

}

#endif //NEURALNETWORK_INETWORK_HPP
