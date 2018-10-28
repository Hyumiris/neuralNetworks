
#include "NeuralNetwork.h"

#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>
#include <cmath>

/*
---------------------------------------------------
----- constructors
---------------------------------------------------
*/

NeuralNetwork::NeuralNetwork() : _weights(0), _biases(0) {}

NeuralNetwork::NeuralNetwork(std::vector<int> const &layerSpecs) : NeuralNetwork(layerSpecs.size(), layerSpecs.data()) {}

NeuralNetwork::NeuralNetwork(int layerCount, int const layerDepths[]) : _biases(layerCount > 0 ? layerCount - 1 : 0), _weights(layerCount > 0 ? layerCount - 1 : 0)
{
	if (layerCount < 1)
	{
		throw std::length_error("at least 2 layers are required");
	}
	for (int i = layerCount - 1; i >= 1; --i)
		_biases[i - 1] = Vector(layerDepths[i]);

	for (int i = layerCount - 2; i >= 0; --i)
		_weights[i] = Matrix(layerDepths[i + 1], layerDepths[i]);
}

NeuralNetwork::NeuralNetwork(NeuralNetwork const &nn) : _biases(nn._biases), _weights(nn._weights) {}

NeuralNetwork::NeuralNetwork(NeuralNetwork &&nn) : NeuralNetwork()
{
	swap(*this, nn);
}

/*
---------------------------------------------------
----- assignment operators
---------------------------------------------------
*/

NeuralNetwork &NeuralNetwork::operator=(NeuralNetwork nn)
{
	swap(*this, nn);
	return *this;
}

/*
---------------------------------------------------
----- accessors
---------------------------------------------------
*/

int NeuralNetwork::numLayers() const
{
	return _biases.size() == 0 ? 0 : _biases.size() + 1;
}

int NeuralNetwork::layerSize(int layer) const
{
	if (layer < 0 || layer >= numLayers())
	{
		throw std::range_error("nonexistent layer");
	}
	return layer != 0 ? _biases[layer - 1].Length() : _weights[layer].Width();
}

void NeuralNetwork::setActivationFn(activationFn activation, activationFn_inv activation_inv)
{
	this->_activation = activation;
	this->_activation_inv = activation_inv;
}

/*
---------------------------------------------------
----- neural network operations
---------------------------------------------------
*/

void NeuralNetwork::generateRandomConfiguration(double weightMin, double weightMax, double biasMin, double biasMax)
{
	/* set up engine */
	std::mt19937 rng;
	rng.seed(std::random_device()());
	/* define distributions */
	std::uniform_real_distribution<double> weightDist(weightMin, weightMax);
	std::uniform_real_distribution<double> biasDist(biasMin, biasMax);

	/* randomize values */
	for (int i = _weights.size() - 1; i >= 0; --i)
	{
		_weights[i].op([&rng, &weightDist](double old) {
			return weightDist(rng);
		});
	}

	for (int i = _biases.size() - 1; i >= 0; --i)
	{
		_biases[i].op([&rng, &biasDist](double old) {
			return biasDist(rng);
		});
	}
}

std::vector<double> NeuralNetwork::forward(std::vector<double> const &input)
{
	Vector tmp(input.size());
	std::copy(input.begin(), input.end(), tmp.begin());

	for (int i = 0; i < numLayers() - 1; ++i)
	{
		Vector multResult = _weights[i] * tmp;
		Vector plusBias = multResult + _biases[i];
		tmp = activate(plusBias);
	}

	std::vector<double> retVal(tmp.Length());
	std::copy(tmp.begin(), tmp.end(), retVal.begin());

	return retVal;
}

/*
---------------------------------------------------
----- helper functions
---------------------------------------------------
*/

void swap(NeuralNetwork &nn1, NeuralNetwork &nn2)
{
	using std::swap;
	swap(nn1._biases, nn2._biases);
	swap(nn1._weights, nn2._weights);
}

void NeuralNetwork::print()
{
	for (int i = 0; i < numLayers() - 1; i++)
	{
		std::cout << "Layer " << i + 1 << std::endl;
		std::cout << "Weights:" << std::endl;
		_weights[i].print();
		std::cout << "Biases:" << std::endl;
		_biases[i].print();
		std::cout << std::endl;
	}
}

Vector &NeuralNetwork::activate(Vector &v)
{
	v.op(_activation);
	return v;
}

/*
---------------------------------------------------
----- external functions
---------------------------------------------------
*/

double NN_IDENTITY(double d)
{
	return d;
}
double NN_IDENTITY_INV(double d)
{
	return d;
}

const double NN_SIGMOID_GAIN = 1.0;
double NN_SIGMOID(double d)
{
	return 1.0 / (1.0 + exp(-d * NN_SIGMOID_GAIN));
}

double NN_SIGMOID_INV(double d)
{
	double sigmoid = NN_SIGMOID(d);
	return sigmoid * (1 - sigmoid);
}
