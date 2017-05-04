//Colin Vaughan, Noah Berman, Alfred Fernandez
//November 2016.

#include "Engine/Engine.h"
#include "NeuralNet.h"

//choose parental influence & mutate
float Genetic(float& mom, float& dad, float mutation)
{
	static float child;
	child = CoinToss(mom, dad);
	child += Random(-1.0f, 1.0f) * mutation;
	return Clamp(child, -1.0f, 1.0f);
}

/*Neuron Class Methods*/
//////////////////////////////////////////////////////////
Neuron::Neuron(unsigned int inputs)
{
	for(int i=  0; i < inputs; ++i)
	{
		w.push_back(Random(-1.0f, 1.0f)); //Give random weightings
	}

}

//Set output based on weighted input values
void Neuron::Update(float* input, float* output)
{
	float total = 0.0f;

	for(int i = 0; i < w.size(); ++i)
	{
		total += input[i] * w[i];
	}
	*output = 1.0f / (1.0f + pow(2.7183f, total * -4.0f));
}

//Create child with other neuron parent with a mutation
Neuron Neuron::Procreate(Neuron& other, float mutation)
{
	Neuron child(w.size());
	for(int i =0; i< w.size(); ++i)
	{
		child.w[i] = Genetic(w[i], other.w[i], mutation);
	}

	return child;
}

/*Neuron Layer Class Methods*/
///////////////////////////////////////////////////
NeuronLayer::NeuronLayer(int inputs, int outputs)
{
	for(int i=  0; i< inputs; ++i)
	{
		input.push_back(0.0f);
	}

	for(int i = 0; i < outputs; ++i)
	{
		neurons.push_back(Neuron(inputs));
	}
}

//send inputs and get outputs from each neuron
void NeuronLayer::Update(float* output)
{
	for(int i =0; i< neurons.size(); ++i)
	{
		neurons[i].Update(&input[0], &output[i]);
	}
}

/*NeuralNet Class Methods*/
/////////////////////////////////////////////////////
NeuralNet::NeuralNet(int numLayers, int* sizes)
{
	score = 0.0f;
	layers.push_back(NeuronLayer(sizes[0], sizes[0]));

	for(int i =1; i < numLayers; ++i)
	{
		layers.push_back(NeuronLayer(sizes[i - 1], sizes[i]));
	}
}

//Transfer inputs to layers and get the output from the final layer
void NeuralNet::Update(float* input, float* output)
{
	//transfer input to first layer
	for(int i = 0; i<layers[0].input.size(); ++i)
	{
		layers[0].input[i] = input[i];
	}

	//transfer input to middle layers
	for (int i = 0; i<layers.size() - 1; ++i)
	{
		layers[i].Update(&layers[i + 1].input[0]);
	}
	//transfer output from final layer
	layers[layers.size() - 1].Update(output);
}

//Combine neural nets to create child with mutation.
NeuralNet NeuralNet::Procreate(NeuralNet& other, float mutation)
{
	NeuralNet child(other);

	//Iterate through neurons.
	for(int i = 0; i<layers.size(); ++i)
	{
		for(int j = 0; j <layers[i].neurons.size(); ++j)
		{
			child.layers[i].neurons[j] = layers[i].neurons[j].Procreate(other.layers[i].neurons[j], mutation);
		}
	}

	return child;
}