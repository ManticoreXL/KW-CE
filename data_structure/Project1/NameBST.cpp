#include "NameBST.h"

// Constructor
NameBST::NameBST()
{
	m_root = nullptr;
}

// Destructor
// using recursivedelete function to delete every node.
NameBST::~NameBST()
{
	recursivedelete(m_root);
}

// Delete every node by inorder traverse (LVR)
void NameBST::recursivedelete(NameBSTNode* root)
{
	if (root != nullptr)
	{
		recursivedelete(root->getLeft());
		NameBSTNode* temp = root->getRight(); // stock node to move right.
		delete root;
		recursivedelete(temp->getRight());
	}
}

// Print every node by inorder traverse (LVR)
void NameBST::recursiveprint(NameBSTNode* root, stringstream& s)
{
	if (root != nullptr)
	{
		recursiveprint(root->getLeft(), s);
		s << *root;
		recursiveprint(root->getRight(), s);
	}
}

// Insert data into NameBST.
void NameBST::insert(string& name, int age, Date& date, Date& exdate)
{
	// When NameBST is empty.
	// create a new NameBSTNode.
	if (m_root == nullptr)
	{
		m_root = new NameBSTNode(name, age, date, exdate);
		return;
	}

	// Find the pit location in NameBST.
	NameBSTNode* temp = nullptr;
	for (NameBSTNode* curr = m_root;
		curr; 
		curr = (curr->getExdate() > exdate) ? curr->getLeft() : curr->getRight())
		temp = curr;

	// create a new NameBSTNode.
	if (temp->getExdate() > exdate)
		temp->setLeft(new NameBSTNode(name, age, date, exdate));
	else
		temp->setRight(new NameBSTNode(name, age, date, exdate));
}

// Print every node
// using recursive print function to print every node.
stringstream& NameBST::print()
{
	static stringstream sss;
	sss = stringstream();
	recursiveprint(m_root, sss);
	return sss;
}

// Print function for SEARCH instruction.
stringstream& NameBST::print(string& name)
{
	static stringstream sss;
	sss = stringstream();

	// Find node
	NameBSTNode* node = nullptr;
	for (NameBSTNode* curr = m_root;
		curr;
		curr = (curr->getName() > name) ? curr->getLeft() : curr->getRight()) {
		node = curr;
		if (curr->getName() == name)
			break;
	}

	// If the node to be printed does not exist, throw error
	if (node == nullptr)
		throw "NameBST::print(string& name)";

	// return static stringstream
	sss << *node;
	return sss;
}

// Remove a node
// using recursive call.
bool NameBST::remove(NameBSTNode* root, NameBSTNode* parent, string& name)
{
	// If TermsBST is empty.
	if (root == nullptr)
		return false;

	// Find the node that name matches.
	if (root->getName() > name)
		return remove(root->getLeft(), root, name);
	else if (root->getName() < name)
		return remove(root->getRight(), root, name);
	// Found the node to be removed.
	else
	{
		// Case 1: node has two children
		if (root->getLeft() && root->getRight())
		{
			// Find the smallest node
			NameBSTNode* succ = root->getRight();
			while (succ->getLeft() != nullptr)
				succ = succ->getLeft();

			// Get succ's value
			root->setName(succ->getName());
			root->setAge(succ->getAge());
			root->setDate(succ->getDate());
			root->setExdate(succ->getExdate());

			// Recursive remove
			return remove(succ, root, succ->getName());
		}
		// Case 2: node has a child or no child
		else
		{
			NameBSTNode* child = (root->getLeft() != nullptr)
				? root->getLeft() : root->getRight();

			// Case 2-1 : head is node to be removed
			// Case 2-2 : swap left child and node.
			// Case 2-3 : swap right child and node.
			if (parent == nullptr)
				m_root = child;
			else if (parent->getLeft() == root)
				parent->setLeft(child);
			else
				parent->setRight(child);

			// Delete node and return true.
			delete root;
			return true;
		}
	}
}

// Remove function for DELETE instruction.
bool NameBST::remove(string& name)
{
	return remove(m_root, nullptr, name);
}