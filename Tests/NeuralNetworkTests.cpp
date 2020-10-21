
#include <TestSuite.h>

#include <NeuralNetwork.h>

#include <iomanip>
#include <algorithm>
#include <random>
#include <iostream>
#include <cmath>

class NNTestAssistant : public TestAssistant
{
	NeuralNetwork nn;

  public:
	void SetUp() override
	{
		vector<int> const layerDepths = {2, 16, 1};
		nn = NeuralNetwork(layerDepths);
	}
	void *getData() override
	{
		return &nn;
	}

	static double testNNactivationFn(double d)
	{
		return 0.0;
	}
};

void testNeuralNetwork()
{
	TestSuite_t<NNTestAssistant, TestCase> NNTests;

	NNTests
		.addTest("Creation", [](TestAssistant &t) {
			std::vector<int> const layerSpec{2, 2};

			NeuralNetwork n1(layerSpec);

			t.Assert(n1.numLayers() == layerSpec.size());
			for (int i = layerSpec.size() - 1; i >= 0; --i)
			{
				t.Assert(layerSpec[i] == n1.layerSize(i));
			}

			NeuralNetwork n2(n1);
			t.Assert(n1.numLayers() != 0);
			t.Assert(n2.numLayers() == layerSpec.size());
			for (int i = layerSpec.size() - 1; i >= 0; --i)
			{
				t.Assert(layerSpec[i] == n2.layerSize(i));
			}

			NeuralNetwork n3(std::move(n1));
			t.Assert(n1.numLayers() == 0);
			t.Assert(n3.numLayers() == layerSpec.size());
			for (int i = layerSpec.size() - 1; i >= 0; --i)
			{
				t.Assert(layerSpec[i] == n3.layerSize(i));
			}
		})
		.addTest("Assignment", [](TestAssistant &t) {
			NeuralNetwork &nn = *(NeuralNetwork *)t.getData();
			NeuralNetwork nn2, nn3;

			nn2 = nn;

			t.Assert(&nn != &nn2);
			t.Assert(nn.numLayers() == nn2.numLayers());
			for (int i = nn.numLayers() - 1; i >= 0; --i)
			{
				t.Assert(nn.layerSize(i) == nn2.layerSize(i));
			}

			nn3 = std::move(nn);

			t.Assert(nn.numLayers() != nn3.numLayers());

			t.Assert(&nn2 != &nn3);
			t.Assert(nn2.numLayers() == nn3.numLayers());
			for (int i = nn2.numLayers() - 1; i >= 0; --i)
			{
				t.Assert(nn2.layerSize(i) == nn3.layerSize(i));
			}
		})
		.addTest("set Activation Func", [](TestAssistant &t) {
			NeuralNetwork &nn = *(NeuralNetwork *)t.getData();

			nn.setActivationFn(NN_IDENTITY, NN_IDENTITY_DER);
			nn.setActivationFn([](double d) { return d; }, NNTestAssistant::testNNactivationFn);
		})
		.addTest("forward propagation", [](TestAssistant &t) {
			NeuralNetwork &nn = *(NeuralNetwork *)t.getData();

			int inputSize = nn.layerSize(0);
			std::vector<double> input(inputSize, 1.0);
			std::vector<double> result;

			result = nn.forward(input);
			t.Assert(std::all_of(result.begin(), result.end(), [](double d) { return d == 0.0; }));

			nn.generateRandomConfiguration();

			result = nn.forward(input);
			t.Assert(std::none_of(result.begin(), result.end(), [](double d) { return d == 0.0; }));
		})
		.addTest("getError mse", [](TestAssistant &t) {
			NeuralNetwork &nn = *(NeuralNetwork *)t.getData();

			nn.generateRandomConfiguration();

			int inputSize = nn.layerSize(0);
			std::vector<double> input(inputSize, 1.0);

			std::vector<double> result = nn.forward(input);
			double error1 = nn.getError(input, result);
			t.Assert(-0.000001 < error1 && error1 < 0.000001);

			std::transform(result.begin(), result.end(), result.begin(), [](double d) { return d + 1.0; });
			double error2 = nn.getError(input, result);
			t.Assert(error1 < error2);

			std::transform(result.begin(), result.end(), result.begin(), [](double d) { return d + 1.0; });
			double error3 = nn.getError(input, result);
			t.Assert(error2 < error3);
		})
		.addTest("train", [](TestAssistant &t) {
			NeuralNetwork &nn = *(NeuralNetwork *)t.getData();
			nn.generateRandomConfiguration(-1.0, 1.0, 0.0, 0.0);
			nn.setActivationFn(NN_SIGMOID, NN_SIGMOID_DER);
			NN_SIGMOID_GAIN = 1.0;
			nn.setLearningRate(0.05);

			const int numSamples = 400;
			const int numTraining = 10000;

			std::mt19937 rng;
			rng.seed(std::random_device()());
			std::uniform_real_distribution<double> getDouble(-30.0, 70.0);
			std::uniform_int_distribution<int> getInt(0, numSamples);

			std::vector<std::vector<double>> input(numSamples);
			std::vector<std::vector<double>> correctResult(numSamples);

			for (int i = 0; i < numSamples; i++)
			{
				input[i] = std::vector<double>(2);
				correctResult[i] = std::vector<double>(1);
				input[i][0] = getDouble(rng);
				input[i][1] = getDouble(rng);
				correctResult[i][0] = (input[i][0] < 0 || input[i][1] < 0) ? 1.0 : 0.0;
			}

			double initialError = nn.getError(input, correctResult);
			nn.print();

			for (int i = 0; i < numTraining; i++)
			{
				nn.train(input, correctResult);
			}

			double trainedError = nn.getError(input, correctResult);
			nn.print();
			std::cout << "initialError: " << initialError << std::endl;
			std::cout << "trainedError: " << trainedError << std::endl;

			for (int i = 0; i < 10; i++)
			{
				int index = getInt(rng);

				std::cout << "(" << input[index][0] << "|" << input[index][1] << ") => ";
				std::cout << nn.forward(input[index])[0] << std::endl;
			}

			t.Assert(initialError > trainedError);
		})
		.runTests();
}
