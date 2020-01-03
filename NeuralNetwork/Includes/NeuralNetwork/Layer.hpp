/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:19
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include "Neuron.hpp"

namespace Neural {

    class Layer {

    public:
        Layer(unsigned int size);
        ~Layer();

        void latchInput(std::vector<double> const &inputValues);
        void computeOutputGradient(std::vector<double> const &targetValues);
        void computeHiddenGradient(Layer const &nextLayer);
        void updateConnectionWeights(Layer &prevLayer);
        void forwardPropagate(Layer const &prevLayer);

        std::vector<double> const &getOutput() const;
        double sumOutput(unsigned index) const;

        unsigned int size() const;
        unsigned getConnectionCount() const;
        std::vector<Neural::Neuron> &neurons();
        std::vector<Neural::Neuron> const &getNeurons() const;

    private:
        std::vector<Neural::Neuron> _neurons;

    };

}

#else

namespace Neural {

    class Layer;

}

#endif /*LAYER_HPP_*/