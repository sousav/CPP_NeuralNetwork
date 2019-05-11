/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   29/04/2018 20:10:29
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 29/04/2018 20:27:31
 */


#ifndef TRAININGDATA_HPP_
#define TRAININGDATA_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "NetworkException.hpp"

namespace Neural {

    class INetworkTrainer {

    public:
        struct TrainingData {
            std::vector<double> input;
            std::vector<double> output;
        };

    public:
        ~INetworkTrainer() {};

        virtual std::vector<unsigned> const &getTopology() const = 0;

        virtual std::vector<Neural::INetworkTrainer::TrainingData> const &getTrainingData() const = 0;

        virtual void setDebugFLag(bool mode) = 0;

        virtual bool getDebugFLag() const = 0;

    };

    class NetworkTrainer : public INetworkTrainer {

    public:
        NetworkTrainer(const std::string filename);

        ~NetworkTrainer();

        NetworkTrainer(const NetworkTrainer &trainer);

        NetworkTrainer &operator=(const NetworkTrainer &trainer);

        std::vector<unsigned> const &getTopology() const;

        std::vector<Neural::INetworkTrainer::TrainingData> const &getTrainingData() const;

        void setDebugFLag(bool mode);

        bool getDebugFLag() const;

    private:
        bool _debug;
        std::vector<unsigned> _topology;
        std::vector<Neural::INetworkTrainer::TrainingData> _trainingData;

        std::vector<unsigned> readTopology(std::ifstream &file) const;

        std::vector<double> readNextInputs(std::ifstream &file) const;

        std::vector<double> readTargetOutputs(std::ifstream &file) const;

    };

}

#endif /*TRAININGDATA_HPP_*/
