
#ifndef neuralnetwork_h
#define neuralnetwork_h

#include <Matrix.h>
#include <Vector.h>

#include <vector>



extern double NN_SIGMOID(double d);
extern double NN_SIGMOID_INVERSE(double d);

class NeuralNetwork
{
	using activationFn = double (*)(double d);
	using activationFn_inv = double (*)(double d);

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

	void setActivationFn(activationFn activation, activationFn_inv activation_inv);

	/* helper functions */
	friend void swap(NeuralNetwork &nn1, NeuralNetwork &nn2);

  private:
	std::vector<Vector> _biases;
	std::vector<Matrix> _weights;

	activationFn activation = NN_SIGMOID;
	activationFn_inv activation_inv = NN_SIGMOID_INVERSE;
};

#endif
