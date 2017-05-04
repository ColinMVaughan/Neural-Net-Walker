//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.
#pragma once
#include <vector>

//Neuron combines inputs into a weighted output.
class Neuron
{
public:
	Neuron(unsigned int inputs);
	void Update(float* input, float* output);
	Neuron Procreate(Neuron& other, float mutation);

	std::vector<float> w; //weights for each input
};

//Neuron layer holds variable number of Neurons.
//Each layer takes in n inputs, and outputs one value per neuron.
class NeuronLayer
{
public:
	NeuronLayer(int inputs, int outputs);
	void Update(float* output);

	std::vector<Neuron> neurons;
	std::vector<float> input;
};

//Neural net holds variable number of layers
class NeuralNet
{
public:
	NeuralNet(int numLayers, int* sizes);
	void Update(float* input, float* output);
	NeuralNet Procreate(NeuralNet& other, float mutation);

	std::vector<NeuronLayer> layers;
	float score;	//score to benchmark fitness
};
