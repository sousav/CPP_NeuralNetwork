/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:50
 */


#include "ANetwork.hpp"

Neural::ANetwork::ANetwork(double recentAverageSmoothingFactor) {
    this->_recentAverageError = 1;
    this->_recentAverageSmoothingFactor = recentAverageSmoothingFactor;
}

Neural::ANetwork::~ANetwork() {

}

double Neural::ANetwork::getRecentAverageError(void) const {
    return this->_recentAverageError;
}

std::vector<Neural::Layer> const & Neural::ANetwork::getLayer() const {
    return this->_layers;
}

unsigned Neural::ANetwork::getLayerCount() const {
    return this->_layers.size();
}

unsigned Neural::ANetwork::getInputCount() const {
    return (this->_layers.empty() ? 0 : this->_layers.front().size() - 1);
}

unsigned Neural::ANetwork::getOutputCount() const {
    return (this->_layers.empty() ? 0 : this->_layers.back().size() - 1);
}

unsigned Neural::ANetwork::getNeuronCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        total += layer.size();
    }
    return total;
}

unsigned Neural::ANetwork::getConnectionCount() const {
    unsigned total = 0;

    for (auto const &layer: this->_layers) {
        total += layer.getConnectionCount();
    }
    return total;
}
