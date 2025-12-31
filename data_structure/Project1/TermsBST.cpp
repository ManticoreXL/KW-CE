#include "TermsBST.h"

// Constructor
TermsBST::TermsBST()
{
	m_root = nullptr;
}

// Destructor
// using recursivedelete function to delete every node.
TermsBST::~TermsBST()
{
	recursivedelete(m_root);
}

// Delete every node by inorder traverse. (LVR)
void TermsBST::recursivedelete(TermsBSTNode* root)
{
	if (root != nullptr)
	{
		recursivedelete(root->getLeft());
		TermsBSTNode* temp = root->getRight(); // stock node to move right.
		delete root; 
		recursivedelete(temp->getRight());
	}
}

// Insert data into NameBST.
void TermsBST::recursiveprint(TermsBSTNode* root, stringstream& ss)
{
	if (root != nullptr)
	{
		recursiveprint(root->getLeft(), ss);
		ss << *root;
		recursiveprint(root->getRight(), ss);
	}
}

void TermsBST::insert(string& name, int age, Date& date, Date& exdate)
{
	// When TermsBST is empty.
	// create a new TermsBSTNode.
	if (m_root == nullptr)
	{
		m_root = new TermsBSTNode(name, age, date, exdate);
		return;
	}

	// Find the pit location in TermsBST.
	TermsBSTNode* temp = nullptr;
	for (TermsBSTNode* curr = m_root; 
		curr; 
		curr = (curr->getExdate() > exdate) ? curr->getLeft() : curr->getRight())
		temp = curr;

	// Create a new NameBSTNode.
	if (temp->getExdate() > exdate)
		temp->setLeft(new TermsBSTNode(name, age, date, exdate));
	else
		temp->setRight(new TermsBSTNode(name, age, date, exdate));
}

// Print every node.
// using recursive print function to print every node.
stringstream& TermsBST::print()
{
	static stringstream sss;
	sss = stringstream();
	recursiveprint(m_root, sss);
	return sss;
}

// Remove a node
// using recursive call.
bool TermsBST::remove(TermsBSTNode* root, TermsBSTNode* parent, string& name)
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
			TermsBSTNode* succ = root->getRight();
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
			TermsBSTNode* child = (root->getLeft() != nullptr)
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

// Remove function for DELETE.
bool TermsBST::remove(string& name)
{
	return remove(m_root, nullptr, name);
}