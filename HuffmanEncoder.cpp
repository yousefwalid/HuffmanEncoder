#include <queue>
#include <map>
#include <string>
#include "HuffmanTree.cpp"

class HuffmanEncoder
{
private:
	std::map<char, std::string> codes;

	void
	recurseHuffmanCode(HuffmanTree *node, std::string code = "0")
	{
		if (node->left != nullptr)
			recurseHuffmanCode(node->left, code + "1");

		if (node->right != nullptr)
			recurseHuffmanCode(node->right, code + "0");

		if (node->symbol != '\0')
			codes[node->symbol] = code;

		return;
	}

	struct PriorityQueueComparator
	{
		bool operator()(HuffmanTree const &p1, HuffmanTree const &p2)
		{
			return p1.frequency > p2.frequency;
		}
	};

public:
	HuffmanEncoder(const std::map<char, int> &frequency)
	{

		// 1) Push all alphabet in priority queue

		std::priority_queue<HuffmanTree, std::vector<HuffmanTree>, PriorityQueueComparator> Nodes;

		for (auto letter : frequency)
		{
			if (letter.second != 0)
			{
				HuffmanTree node((char)letter.first, letter.second);
				Nodes.push(node);
			}
		}

		// 2) Pop two letters, merge them together, then push them back into PQ

		while (Nodes.size() > 1)
		{
			HuffmanTree *node1 = new HuffmanTree();
			*node1 = Nodes.top();
			Nodes.pop();

			HuffmanTree *node2 = new HuffmanTree();
			*node2 = Nodes.top();
			Nodes.pop();

			HuffmanTree newNode('\0', (*node1).frequency + (*node2).frequency);
			newNode.left = node1;
			newNode.right = node2;
			Nodes.push(newNode);
		}

		HuffmanTree headNode = Nodes.top();
		Nodes.pop();

		// 3) Get the codes

		recurseHuffmanCode(&headNode);

		// 4) Output the encoded file
	}

	std::map<char, std::string> getCodes() { return codes; }
};