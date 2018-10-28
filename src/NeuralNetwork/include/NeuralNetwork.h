
#ifndef neuralnetwork_h
#define neuralnetwork_h

#include <Matrix.h>
#include <Vector.h>

#include <vector>


extern double NN_IDENTITY(double d);
extern double NN_IDENTITY_INV(double d);

extern double NN_SIGMOID(double d);
extern double NN_SIGMOID_INV(double d);

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

	/* neural network operations */
	void generateRandomConfiguration(double weightMin = -1.0, double weightMax = 1.0, double biasMin = 0.0, double biasMax = 1.0);
	std::vector<double> forward(std::vector<double> const &input);

	/* helper functions */
	friend void swap(NeuralNetwork &nn1, NeuralNetwork &nn2);
	void print();

  private:

	/* private functions */
	Vector &activate(Vector &v);

	/* members */
	std::vector<Vector> _biases;
	std::vector<Matrix> _weights;

	activationFn _activation = NN_SIGMOID;
	activationFn_inv _activation_inv = NN_SIGMOID_INV;
};

#endif
