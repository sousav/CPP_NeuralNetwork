//
// ANetworkData.cpp for  in /Users/vicostudio/Documents/Shared Folder/Work/NeuralNetwork/CPP_NeuralNetwork/sources/
//
// Made by Sousa Victor
// Login   <sousa_v@epitech.eu>
//
// Started on  Tue May  2 01:03:08 2017 Sousa Victor
// Last update Tue May  2 01:07:10 2017 Sousa Victor
//

#include "ANetworkData.hpp"

Neural::ANetworkData::ANetworkData(const std::vector<unsigned> &topology, double recentAverageSmoothingFactor) {
    this->_recentAverageSmoothingFactor = recentAverageSmoothingFactor;
    unsigned numLayers = topology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {
        this->_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        // We have a new layer, now fill it with neurons
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {
            this->_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }
        this->_layers.back().back().setOutputVal(1.0); //bias neuron
    }
}

Neural::ANetworkData::~ANetworkData() {

}

Neural::ANetworkData::ANetworkData(const ANetworkData &data) {
    this->_layers = data._layers;
    this->_error = data._error;
    this->_recentAverageError = data._recentAverageError;
    this->_recentAverageSmoothingFactor = data._recentAverageSmoothingFactor;
}

Neural::ANetworkData &Neural::ANetworkData::operator =(const ANetworkData &data) {
    this->_layers = data._layers;
    this->_error = data._error;
    this->_recentAverageError = data._recentAverageError;
    this->_recentAverageSmoothingFactor = data._recentAverageSmoothingFactor;
    return *this;
}


double Neural::ANetworkData::getRecentAverageError(void) const {
    return this->_recentAverageError;
}

std::vector<Neural::Layer> const & Neural::ANetworkData::getLayer() const {
    return this->_layers;
}

unsigned Neural::ANetworkData::getLayerCount() const {
    return this->_layers.size();
}

unsigned Neural::ANetworkData::getInputCount() const {
    return (this->_layers.size() == 0 ? 0 : this->_layers.front().size() - 1);
}

unsigned Neural::ANetworkData::getOutputCount() const {
    return (this->_layers.size() == 0 ? 0 : this->_layers.back().size() - 1);
}

unsigned Neural::ANetworkData::getNeuronCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        total += layer.size();
    }
    return total;
}

unsigned Neural::ANetworkData::getConnectionCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        for (auto const &neuron: layer) {
            total += neuron.getConnectionCount();
        }
    }
    return total;
}
