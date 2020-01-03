/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:28:03
 */


#include "Neuron.hpp"

Neural::Neuron::Neuron(unsigned myIndex, double eta, double alpha) {
    this->_eta = eta;
    this->_alpha = alpha;
    this->_mIndex = myIndex;
}

Neural::Neuron::~Neuron() {

}

Neural::Neuron::Neuron(const Neural::Neuron &neuron) {
    this->_eta = neuron._eta;
    this->_alpha = neuron._alpha;
    this->_outputVal = neuron._outputVal;
    this->_outputWeights = neuron._outputWeights;
    this->_mIndex = neuron._mIndex;
    this->_gradient = neuron._gradient;
}

Neural::Neuron &Neural::Neuron::operator =(const Neural::Neuron &neuron) {
    this->_eta = neuron._eta;
    this->_alpha = neuron._alpha;
    this->_outputVal = neuron._outputVal;
    this->_outputWeights = neuron._outputWeights;
    this->_mIndex = neuron._mIndex;
    this->_gradient = neuron._gradient;
    return *this;
}

void Neural::Neuron::setOutputSize(unsigned size) {
    for (unsigned c = 0; c < size; ++c) {
        this->_outputWeights.emplace_back();
        this->_outputWeights.back().weight = randomWeight();
    }
}

void Neural::Neuron::setOutputVal(double val) {
    this->_outputVal = val;
}

double Neural::Neuron::getOutputVal() const {
    return this->_outputVal;
}

void Neural::Neuron::feedForward(const Layer &prevLayer) {
    this->_outputVal = Neural::Neuron::transferFunction(prevLayer.sumOutput(this->_mIndex));
}

void Neural::Neuron::computeOutputGradient(double targetVal) {
    double delta = targetVal - this->_outputVal;
    this->_gradient = delta * Neural::Neuron::transferFunctionDerivative(this->_outputVal);
}

void Neural::Neuron::computeHiddenGradient(const Layer &nextLayer) {
    double dow = sumDOW(nextLayer);
    this->_gradient = dow * Neural::Neuron::transferFunctionDerivative(this->_outputVal);
}

void Neural::Neuron::updateInputWeights(Layer &prevLayer) {
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer
    for (auto &neuron: prevLayer.neurons()) {
        double oldDeltaWeight = neuron._outputWeights[this->_mIndex].deltaWeight;

        double newDeltaWeight =
                // Individual input, magnified by the gradient and train rate:
                this->_eta
                * neuron.getOutputVal()
                * this->_gradient
                // Also add momentum = a fraction of the previous delta weight;
                + this->_alpha
                * oldDeltaWeight;

        neuron._outputWeights[this->_mIndex].deltaWeight = newDeltaWeight;
        neuron._outputWeights[this->_mIndex].weight += newDeltaWeight;
    }
}

std::vector<Neural::INeuron::Connection> const &Neural::Neuron::getConnection() const {
    return this->_outputWeights;
}

void Neural::Neuron::setConnection(unsigned index, Neural::INeuron::Connection const &data) {
    this->_outputWeights[index].weight = data.weight;
    this->_outputWeights[index].deltaWeight = data.deltaWeight;
}

unsigned Neural::Neuron::getConnectionCount() const {
    return this->_outputWeights.size();
}

double Neural::Neuron::transferFunction(double x) const {
    // tanh - output range [-1.0..1.0]
    return tanh(x);
}

double Neural::Neuron::transferFunctionDerivative(double x) const {
    // tanh derivative
    return 1.0 - x * x;
}

double Neural::Neuron::randomWeight(void) const {
     return rand() / double(RAND_MAX);
}

double Neural::Neuron::sumDOW(const Neural::Layer &nextLayer) const {
    double sum = 0.0;

    // Sum our contributions of the errors at the nodes we feed.
    for (unsigned n = 0; n < nextLayer.getNeurons().size() - 1; ++n) {
        sum += this->_outputWeights[n].weight * nextLayer.getNeurons()[n]._gradient;
    }
    return sum;
}
