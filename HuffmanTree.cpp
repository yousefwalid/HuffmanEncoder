class HuffmanTree
{
public:
	char symbol;
	int frequency;
	HuffmanTree *left = nullptr, *right = nullptr;

	bool operator<(const HuffmanTree &t)
	{
		return this->frequency > t.frequency;
	}

	HuffmanTree(char symbol // Symbol of the node
				,
				int frequency // Frequency of the symbol
	)
	{
		this->symbol = symbol;
		this->frequency = frequency;
	}

	HuffmanTree()
	{
	}
};
