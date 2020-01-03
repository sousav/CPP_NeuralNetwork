/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:14
 */


#ifndef ANETWORK_HPP_
#define ANETWORK_HPP_

#include <sstream>
#include <fstream>

#include "NetworkException.hpp"
#include "Layer.hpp"
#include "INetwork.hpp"

namespace Neural {

    class ANetwork: public INetwork {

    public:
        ANetwork(double recentAverageSmoothingFactor);
        virtual ~ANetwork();


    protected:
        std::vector<Layer> _layers; // _layers[layerNum][neuronNum]
        std::vector<double> _errorHistory;
        double _recentAverageError;
        double _recentAverageSmoothingFactor;

    public:
        virtual double getRecentAverageError(void) const;
        virtual std::vector<Neural::Layer> const &getLayer() const;
        virtual unsigned getLayerCount() const;
        virtual unsigned getInputCount() const;
        virtual unsigned getOutputCount() const;
        virtual unsigned getNeuronCount() const;
        virtual unsigned getConnectionCount() const;

    };

}

#endif /*ANETWORK_HPP_*/
