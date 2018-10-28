
#include <TestSuite.h>

#include <NeuralNetwork.h>

class NNTestAssistant : public TestAssistant
{
	NeuralNetwork nn;

  public:
	void SetUp() override
	{
		vector<int> const layerDepths = {2, 3, 1};
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

			nn.setActivationFn(NN_IDENTITY, NN_IDENTITY_INV);
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
		.runTests();
}
