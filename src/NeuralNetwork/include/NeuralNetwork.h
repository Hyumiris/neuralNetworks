
#ifndef neuralnetwork_h
#define neuralnetwork_h

#include <Matrix.h>
#include <Vector.h>

#include <vector>

class NeuralNetwork
{
  public:
	/* constructors */
	NeuralNetwork();
	NeuralNetwork(std::vector<int> const &layerSpecs);
	NeuralNetwork(int layerCount, int const *layerDepths);
	NeuralNetwork(NeuralNetwork const &nn);
	NeuralNetwork(NeuralNetwork &&nn);

	/* assignment operators */
	NeuralNetwork &operator=(NeuralNetwork nn);

	/* accessors */
	int numLayers() const;
	int layerSize(int layer) const;

	/* helper functions */
	friend void swap(NeuralNetwork &nn1, NeuralNetwork &nn2);

  private:
	std::vector<Vector> _biases;
	std::vector<Matrix> _weights;
};

#endif
