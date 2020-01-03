/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:54
 */


#include "Network.hpp"

Neural::Network::Network(double recentAverageSmoothingFactor): ANetwork(recentAverageSmoothingFactor) {

}

Neural::Network::~Network() {

}

Neural::Network::Network(const Neural::Network &network) : ANetwork(network) {

}

Neural::Network &Neural::Network::operator=(const Neural::Network &network) {
    Neural::ANetwork::operator=(network);
    return *this;
}

Neural::Network &Neural::Network::operator<<(Layer layer) {
    if (!this->_layers.empty()) {
        for (auto &neuron: this->_layers.back().neurons()) {
            neuron.setOutputSize(layer.getNeurons().size() - 1);
        }
    }
    this->_layers.push_back(layer);
    return *this;
}

void Neural::Network::train(INetworkTrainer const &trainer) {
    std::vector<Neural::INetworkTrainer::TrainingData> const& trainingData = trainer.getTrainingData();

    int trainingPass = 0;
    for (auto const &data: trainingData) {
        this->feedForward(data.input);
        std::vector<double> result = this->getResults();
        if (data.output.size() != trainer.getTopology().back()) {
            throw Neural::InvalidTrainingFile("Your are requesting " + std::to_string(data.output.size()) + " output data but your network can only output " + std::to_string(trainer.getTopology().back()) + "..");
        }
        this->backProp(data.output);
        trainingPass++;
    }
}

void Neural::Network::feedForward(const std::vector<double> &inputVals) {
    if (inputVals.size() != this->_layers[0].size() - 1) {
        throw Neural::InvalidInput("You want to input " + std::to_string(inputVals.size()) + " values but your network can only accept " + std::to_string(this->_layers[0].size() - 1));
    }

    this->_layers[0].latchInput(inputVals);

    // forward propagate
    for (unsigned layerNum = 1; layerNum < this->_layers.size(); ++layerNum) {
        this->_layers[layerNum].forwardPropagate(this->_layers[layerNum - 1]);
    }
}

std::vector<double> const Neural::Network::getResults() const {
    return this->_layers.back().getOutput();
}

void Neural::Network::backProp(const std::vector<double> &targetVals) {
    // Calculate overall net error (RMS of output neuron errors)
    Layer &outputLayer = this->_layers.back();
    double error = 0.0;

    for (unsigned n = 0; n < outputLayer.getOutput().size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer.getOutput()[n];
        error += delta * delta;
    }
    error /= outputLayer.size() - 1; // get average error squared
    error = sqrt(error); // RMS


    // Implement a recent average measurement
    this->_recentAverageError = (this->_recentAverageError * this->_recentAverageSmoothingFactor + error) / (this->_recentAverageSmoothingFactor + 1.0);

    this->_errorHistory.push_back(this->_recentAverageError);


    outputLayer.computeOutputGradient(targetVals);

    for (unsigned layerNum = this->_layers.size() - 2; layerNum > 0; --layerNum) {
        this->_layers[layerNum].computeHiddenGradient(this->_layers[layerNum + 1]);
    }

    for (unsigned layerNum = this->_layers.size() - 1; layerNum > 0; --layerNum) {
        this->_layers[layerNum].updateConnectionWeights(this->_layers[layerNum - 1]);
    }
}

void Neural::Network::errorPlot() const {
    plt::plot(this->_errorHistory);

    plt::title("Error factor");
    plt::legend();

    plt::show();
}

std::ostream &operator<<(std::ostream& os, const Neural::Network &network) {
    os << std::endl << "|------------- NETWORK INFO -------------|" << std::endl;
    std::vector<Neural::Layer> const layers = network.getLayer();
    os << "\tNetwork has " << network.getLayerCount() << " layer" << (network.getLayerCount() > 1 ? "s" : "") << std::endl;
    os << "\tIt takes " << network.getInputCount() << " input" << (network.getInputCount() > 1 ? "s" : "") <<" and give in return " << network.getOutputCount() << " output" << (network.getOutputCount() > 1 ? "s" : "") << std::endl;
    os << "\tIt has a total of " << network.getNeuronCount() << " neurons and " << network.getConnectionCount() << " connections" << std::endl;
    os << "\tIts recent average error factor is " << network.getRecentAverageError() << std::endl;
    os << std::endl << "\t|--------- Layer Status ---------|" << std::endl;
    unsigned i = 0;
    for (auto const &layer: layers) {
        os << "\t\tLayer " << i << (i == 0 ? ", Input layer" : i == layers.size() - 1 ? ", Output layer" : "") << ", " << layer.size() - 1 << " neuron" << (layer.size() - 1 > 1 ? "s" : "") << std::endl;
        unsigned j = 0;
        for (auto const &neuron: layer.getNeurons()) {
            std::vector<Neural::INeuron::Connection> connections = neuron.getConnection();
            os << "\t\t\tNeuron " << j << " with " << connections.size() << " connection" << (connections.size() > 1 ? "s" : "") << (j == layer.size() - 1 ? " (bias neuron)" : "") << std::endl;
            unsigned k = 0;
            for (auto const &connection: connections) {
                os << "\t\t\t\tConnection " << k << " with a weight of " << connection.weight << std::endl;
                k++;
            }
            os << std::endl;
            j++;
        }
        os << std::endl;
        i++;
    }
    os << "\t|--------------------------------|" << std::endl;
    os << "|----------------------------------------|" << std::endl;
    return os;
}
