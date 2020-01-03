//
// Created by Victor Sousa on 03/01/2020.
//

#include "Layer.hpp"

Neural::Layer::Layer(unsigned int size) {
    for (unsigned neuronNum = 0; neuronNum <= size; ++neuronNum) {
        this->_neurons.emplace_back(neuronNum);
    }
    this->neurons().back().setOutputVal(1.0); //bias neuron
}

Neural::Layer::~Layer() {

}

void Neural::Layer::forwardPropagate(const class Neural::Layer & prevLayer) {
    for (auto &neuron: this->_neurons) {
        neuron.feedForward(prevLayer);
    }
}

void Neural::Layer::latchInput(std::vector<double> const &inputValues) {
    for (unsigned i = 0; i < inputValues.size(); ++i) {
        this->_neurons[i].setOutputVal(inputValues[i]);
    }
}

void Neural::Layer::computeOutputGradient(std::vector<double> const &targetValues) {
    for (unsigned n = 0; n < this->_neurons.size() - 1; ++n) {
        this->_neurons[n].computeOutputGradient(targetValues[n]);
    }
}

void Neural::Layer::computeHiddenGradient(Neural::Layer const &nextLayer) {
    for (auto &neuron: this->_neurons) {
        neuron.computeHiddenGradient(nextLayer);
    }
}

void Neural::Layer::updateConnectionWeights(Neural::Layer &prevLayer) {
    for (auto &neuron: this->_neurons) {
        neuron.updateInputWeights(prevLayer);
    }
}

std::vector<double> const &Neural::Layer::getOutput() const {
    std::vector<double> resultVals;

    for (auto &neuron: this->_neurons) {
        resultVals.push_back(neuron.getOutputVal());
    }
    return std::move(resultVals);
}

double Neural::Layer::sumOutput(unsigned index) const {
    double sum = 0;
    for (auto &neuron: this->_neurons) {
        sum += neuron.getOutputVal() *
               neuron.getConnection()[index].weight;
    }
    return sum;
}

std::vector<Neural::Neuron> &Neural::Layer::neurons() {
    return this->_neurons;
}

std::vector<Neural::Neuron> const &Neural::Layer::getNeurons() const {
    return this->_neurons;
}

unsigned int Neural::Layer::size() const {
    return this->_neurons.size();
}

unsigned Neural::Layer::getConnectionCount() const {
    unsigned total = 0;

    for (auto const &neuron: this->_neurons) {
        total += neuron.getConnectionCount();
    }
    return total;
}