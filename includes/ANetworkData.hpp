//
// ANetworkData.hpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP_NeuralNetwork/includes/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May  2 01:01:41 2017 Sousa Victor
// Last update Tue May  2 01:04:12 2017 Sousa Victor
//

#ifndef ANETWORKDATA_HPP_
#define ANETWORKDATA_HPP_

#include "Layer.hpp"

namespace Neural {

    class ANetworkData {

    public:
        ANetworkData(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor);
        ~ANetworkData();
        ANetworkData(const ANetworkData &data);
        ANetworkData &operator =(const ANetworkData &data);

        virtual double getRecentAverageError(void) const;
        virtual std::vector<Neural::Layer> const &getLayer() const;
        virtual unsigned getLayerCount() const;
        virtual unsigned getInputCount() const;
        virtual unsigned getOutputCount() const;
        virtual unsigned getNeuronCount() const;
        virtual unsigned getConnectionCount() const;

    protected:
        std::vector<Layer> _layers; // _layers[layerNum][neuronNum]
        double _error;
        double _recentAverageError;
        double _recentAverageSmoothingFactor;

    };

}

#endif /*ANETWORKDATA_HPP_*/
