/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:22
 */


#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#include <MatPlotLib/MatPlotLib.h>

#include "NetworkException.hpp"
#include "NetworkTrainer.hpp"
#include "ANetworkData.hpp"
#include "Layer.hpp"

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

    class Network : public INetwork, public ANetworkData {

    public:
        Network(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor = 100);
        ~Network();
        Network(const Network &network);
        Network &operator =(const Network &network);

        void train(INetworkTrainer const &trainer);
        void feedForward(const std::vector<double> &inputVals);
        std::vector<double> const getResults() const;
        void backProp(const std::vector<double> &targetVals);

        void errorPlot() const;

    private:
        void showVectorVals(std::string const &label, std::vector<double> const &v) const;

    };

}

std::ostream &operator<<(std::ostream& os, const Neural::Network &network);

#else

namespace Neural {

    class INetwork;
    class Network : public INetwork;

}

#endif /*NETWORK_HPP_*/
