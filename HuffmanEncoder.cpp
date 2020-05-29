#include <queue>
#include <stack>
#include <unordered_map>
#include <string>
#include "HuffmanTree.cpp"

class HuffmanEncoder
{
private:
	std::unordered_map<char, std::string> codes;

	void iterativeHuffmanCode(HuffmanTree *node)
	{
		std::string code = "";
		std::stack<HuffmanTree *> parentNodes;
		std::unordered_map<HuffmanTree *, bool> visitedNode;

		HuffmanTree *currentNode = node;
		parentNodes.push(node);

		while (!parentNodes.empty())
		{
			visitedNode[currentNode] = true;

			if (currentNode->left != nullptr && !visitedNode.count(currentNode->left))
			{
				currentNode = currentNode->left;
				parentNodes.push(currentNode);
				code += "1";
				continue;
			}

			if (currentNode->right != nullptr && !visitedNode.count(currentNode->right))
			{
				currentNode = currentNode->right;
				parentNodes.push(currentNode);
				code += "0";
				continue;
			}

			if (currentNode->left == nullptr && currentNode->right == nullptr)
				codes[currentNode->symbol] = code;

			code.pop_back();
			parentNodes.pop();
			if (parentNodes.empty())
				break;
			currentNode = parentNodes.top();
		}
	}

	void
	recurseHuffmanCode(HuffmanTree *node, std::string code = "0")
	{
		if (node->left != nullptr)
			recurseHuffmanCode(node->left, code + "1");

		if (node->right != nullptr)
			recurseHuffmanCode(node->right, code + "0");

		if (node->left == nullptr && node->right == nullptr)
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
	HuffmanEncoder(const std::unordered_map<char, int> &frequency)
	{

		// 1) Push all alphabet in priority queue

		std::priority_queue<HuffmanTree, std::vector<HuffmanTree>, PriorityQueueComparator> Nodes;

		for (auto letter : frequency)
		{
			HuffmanTree node((char)letter.first, letter.second);
			Nodes.push(node);
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

			HuffmanTree newNode(0, (*node1).frequency + (*node2).frequency);
			newNode.left = node1;
			newNode.right = node2;
			Nodes.push(newNode);
		}

		HuffmanTree headNode = Nodes.top();
		Nodes.pop();

		// 3) Get the codes

		//recurseHuffmanCode(&headNode);

		iterativeHuffmanCode(&headNode);
	}

	std::unordered_map<char, std::string> getCodes() { return codes; }
};