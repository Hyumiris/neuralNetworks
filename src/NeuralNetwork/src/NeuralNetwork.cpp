
#include "NeuralNetwork.h"

#include <stdexcept>

/*
---------------------------------------------------
----- constructors
---------------------------------------------------
*/

NeuralNetwork::NeuralNetwork() : NeuralNetwork(0, nullptr) {}

NeuralNetwork::NeuralNetwork(std::vector<int> const &layerSpecs) : NeuralNetwork(layerSpecs.size(), layerSpecs.data()) {}

NeuralNetwork::NeuralNetwork(int layerCount, int const layerDepths[]) : _biases(layerCount), _weights(layerCount > 0 ? layerCount - 1 : 0)
{
	if (layerCount < 0)
	{
		throw std::length_error("negative layercount");
	}
	for (int i = layerCount - 1; i >= 0; --i)
		_biases[i] = Vector(layerDepths[i]);

	for (int i = layerCount - 2; i >= 0; --i)
		_weights[i] = Matrix(layerDepths[i], layerDepths[i + 1]);
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
	return _biases.size();
}

int NeuralNetwork::layerSize(int layer) const
{
	return _biases[layer].Length();
}

void NeuralNetwork::setActivationFn(activationFn activation, activationFn_inv activation_inv)
{
	this->activation = activation;
	this->activation_inv = activation_inv;
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

double NN_SIGMOID(double d)
{
	return 0.0;
}

double NN_SIGMOID_INVERSE(double d)
{
	return 0.0;
}
