
#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int layerCount, int layerDepths[]) : _layerCount(layerCount), _layerDepth(layerDepths)
{
	_layers = new Matrix *[_layerCount];
	_weights = new Matrix *[_layerCount - 1];

	for (int i = _layerCount - 1; i >= 0; --i)
		_layers[i] = new Matrix[_layerDepth[i]];

	for (int i = _layerCount - 2; i >= 0; --i)
		_weights[i] = new Matrix(_layerDepth[i], _layerDepth[i + 1]);
}

NeuralNetwork::~NeuralNetwork()
{
	for (int i = _layerCount - 1; i >= 0; --i)
		delete[] _layers[i];
	delete[] _layers;
	for (int i = _layerCount - 2; i >= 0; --i)
		delete _weights[i];
	delete[] _weights;
}
