
#ifndef neuralnetwork_h
#define neuralnetwork_h

#include <Matrix.h>
#include <Vector.h>

#include <vector>


extern double NN_IDENTITY(double d);
extern double NN_IDENTITY_DER(double d);

extern double NN_SIGMOID_GAIN;
extern double NN_SIGMOID(double d);
extern double NN_SIGMOID_DER(double d);

class NeuralNetwork
{
	using activationFn = double (*)(double d);
	using activationFn_der = double (*)(double d);

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

	void setLearningRate(double d);
	void setActivationFn(activationFn activation, activationFn_der activation_inv);

	/* neural network operations */
	void generateRandomConfiguration(double weightMin = -1.0, double weightMax = 1.0, double biasMin = 0.0, double biasMax = 1.0);
	std::vector<double> forward(std::vector<double> const &input);
	double getError(std::vector<double> const input, std::vector<double> const expectedResult);
	double getError(std::vector<std::vector<double>> const input, std::vector<std::vector<double>> const expectedResult);
	void train(std::vector<std::vector<double>> const &trainingData, std::vector<std::vector<double>> const &trainingResults);

	/* helper functions */
	friend void swap(NeuralNetwork &nn1, NeuralNetwork &nn2);
	void print();

  private:

	/* private functions */
	void activate(Matrix &m) const;
	Matrix getActivated(Matrix const &m) const;
	void addBias(Matrix &m, Vector const &bias) const;

	Vector forward_v(Vector const& input) const;
	Matrix forward_m(Matrix const& input) const;

	double calculateLoss(Matrix const &result, Matrix const &expectedResult) const;

	Matrix vecToMatrix(std::vector<std::vector<double>> const &vec) const;

	/* members */
	std::vector<Vector> _biases;
	std::vector<Matrix> _weights;

	double _learningRate = 0.1;

	activationFn _activation = NN_SIGMOID;
	activationFn_der _activation_der = NN_SIGMOID_DER;
};

#endif
