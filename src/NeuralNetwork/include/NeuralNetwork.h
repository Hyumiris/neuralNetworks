
#ifndef neuralnetwork_h
#define neuralnetwork_h

#include <Matrix.h>

class NeuralNetwork
{
	NeuralNetwork(NeuralNetwork const &) = delete;
	NeuralNetwork &operator=(NeuralNetwork const &) = delete;
	NeuralNetwork(NeuralNetwork &&) = delete;
	NeuralNetwork &operator=(NeuralNetwork &&) = delete;

  public:
	NeuralNetwork(int layerCount, int *layerDepths);
	~NeuralNetwork();

  private:
	int _layerCount;
	int *_layerDepth;

	Matrix **_layers;
	Matrix **_weights;
};

#endif
