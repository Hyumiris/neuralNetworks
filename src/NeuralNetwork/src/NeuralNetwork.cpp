
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

void NeuralNetwork::setLearningRate(double d)
{
	_learningRate = d;
}

void NeuralNetwork::setActivationFn(activationFn activation, activationFn_der activation_inv)
{
	this->_activation = activation;
	this->_activation_der = activation_inv;
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
	return forward_v(Vector(input));
}

double NeuralNetwork::getError(std::vector<double> const input, std::vector<double> const expectedResult)
{
	return calculateLoss(forward_v(input), Vector(expectedResult));
}

double NeuralNetwork::getError(std::vector<std::vector<double>> const input, std::vector<std::vector<double>> const expectedResult)
{
	return calculateLoss(forward_m(vecToMatrix(input)), vecToMatrix(expectedResult));
}

/*
currently the result and input get activated
*/
void NeuralNetwork::train(std::vector<std::vector<double>> const &trainingData, std::vector<std::vector<double>> const &trainingResults)
{
	Matrix inputMatrix = vecToMatrix(trainingData);
	Matrix expectedMatrix = vecToMatrix(trainingResults);
	if (inputMatrix.Width() != expectedMatrix.Width())
	{
		throw std::invalid_argument("trainingData and trainingResults need the same sample size");
	}

	// set up storage to temporarily hold results for all layers
	std::vector<Matrix> layerZ(numLayers());
	std::vector<Matrix> layerActivated(numLayers());
	layerZ[0] = inputMatrix;
	// this determines whether the input gets activated
	layerActivated[0] = layerZ[0];

	// calculate all layers
	layerZ[1] = _weights[0] * layerZ[0];
	addBias(layerZ[1], _biases[0]);
	for (int i = 0; i < numLayers() - 1; ++i)
	{
		layerZ[i + 1] = _weights[i] * layerActivated[i];
		addBias(layerZ[i + 1], _biases[i]);
		layerActivated[i + 1] = getActivated(layerZ[i + 1]);
	}
	// this determines whether the result gets activated
	Matrix result = layerActivated[numLayers() - 1];

	// train
	Matrix err = result - expectedMatrix;
	Matrix Z, dLossdZ, dLossdWeights, deltaWeights, dLossdBias, dLossdInput, deltaInput;
	Vector deltaBias;
	for (int i = layerZ.size() - 2; i >= 0; i--)
	{
		Z = layerZ[i + 1]; // avoid this copy?
		Z.op(_activation_der);
		/* this assumes mse as loss function */
		dLossdZ = (2 * err).op(Z, [](double d1, double d2) { return d1 * d2; });

		dLossdWeights = dLossdZ * layerActivated[i].transpose();
		deltaWeights = -1 * _learningRate * dLossdWeights;

		double const biasFactor = 0.001;
		dLossdBias = dLossdZ;
		deltaBias = Vector(dLossdBias.Height());
		for (int h = dLossdBias.Height() - 1; h >= 0; --h)
		{
			double sum = 0.0;
			for (int w = dLossdBias.Width() - 1; w >= 0; --w)
			{
				sum += dLossdBias(h, w);
			}
			deltaBias(h) += sum / dLossdBias.Width();
		}
		deltaBias *= -1 * _learningRate * biasFactor;

		dLossdInput = _weights[i].transpose() * dLossdZ;
		deltaInput = -1 * dLossdInput;

		_weights[i] += deltaWeights;
		_biases[i] += deltaBias;
		err = deltaInput;
	}
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
	swap(nn1._activation, nn2._activation);
	swap(nn1._activation_der, nn2._activation_der);
	swap(nn1._learningRate, nn2._learningRate);
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

/*
---------------------------------------------------
----- private functions
---------------------------------------------------
*/

void NeuralNetwork::activate(Matrix &m) const
{
	m.op(_activation);
}

Matrix NeuralNetwork::getActivated(Matrix const &m) const
{
	Matrix retVal(m);
	activate(retVal);
	return retVal;
}

void NeuralNetwork::addBias(Matrix &m, Vector const &bias) const
{
	for (int h = m.Height() - 1; h >= 0; --h)
	{
		for (int w = m.Width() - 1; w >= 0; --w)
		{
			m(h, w) += bias(h);
		}
	}
}

Vector NeuralNetwork::forward_v(Vector const &input) const
{
	return Vector(forward_m(input));
}

Matrix NeuralNetwork::forward_m(Matrix const &input) const
{
	Matrix retVal(input);

	for (int i = 0; i < numLayers() - 1; ++i)
	{
		retVal = _weights[i] * retVal;
		addBias(retVal, _biases[i]);
		activate(retVal);
	}

	return retVal;
}

double NeuralNetwork::calculateLoss(Matrix const &result, Matrix const &expectedResult) const
{
	/* hardcoded mse */
	Matrix diff = (result - expectedResult);
	diff.op([](double d) { return d * d; });
	return std::accumulate(diff.begin(), diff.end(), 0.0) / (diff.Height() * diff.Width());
}

Matrix NeuralNetwork::vecToMatrix(std::vector<std::vector<double>> const &vec) const
{
	if (std::any_of(vec.begin(), vec.end(),
					[&vec](std::vector<double> const &v) { return v.size() != vec[0].size(); }))
	{
		throw std::invalid_argument("not all vectors are of the same size");
	}
	Matrix retVal(vec[0].size(), vec.size());
	for (int x = vec.size() - 1; x >= 0; --x)
	{
		std::vector<double> const &v = vec[x];
		for (int y = v.size() - 1; y >= 0; --y)
		{
			retVal(y, x) = v[y];
		}
	}
	return retVal;
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
double NN_IDENTITY_DER(double d)
{
	return 1;
}

double NN_SIGMOID_GAIN = 1.0;
double NN_SIGMOID(double d)
{
	return 1.0 / (1.0 + exp(-d * NN_SIGMOID_GAIN));
}

double NN_SIGMOID_DER(double d)
{
	double sigmoid = NN_SIGMOID(d);
	return NN_SIGMOID_GAIN * sigmoid * (1.0 - sigmoid);
}
