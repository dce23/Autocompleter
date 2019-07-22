#include "autocompleter.h"

Autocompleter::Autocompleter()
{
  root = nullptr;

	Entry newAc;

	newAc.freq = 0;
	newAc.s = "";
}

void Autocompleter::insert(string x, int freq)
{
	Entry create;

	create.s = x;
	create.freq = freq;

	if (root == nullptr) {
		root = new Node(create);
		root->height = height(root) + 1;
		//cout << "Root: " << root->e.s << "\t\tHeight: " << root->height << endl;
		return;
	}
	
	insert_recurse(create, root);
	//cout << root->e.s << endl;
	//cout << "Height of Root After: " << root->height << endl;
}

int Autocompleter::size()
{
  if (root == nullptr) {	//Base Case
		return 0;
	}

	return size_recurse(root);
}

void Autocompleter::completions(string x, vector<string>& T)
{

  vector<Entry> Top3Freq;
	completions_recurse(x, root, Top3Freq);

	int comps = 1;

	if (Top3Freq.size() > 1) {
		while (comps < Top3Freq.size()) {
			int ACcomp = comps;
			while (ACcomp > 0 && Top3Freq[ACcomp - 1].freq < Top3Freq[ACcomp].freq) {
				Entry temp = Top3Freq[ACcomp];
				Top3Freq[ACcomp] = Top3Freq[ACcomp - 1];
				Top3Freq[ACcomp - 1] = temp;
				ACcomp -= 1;
			}
			comps += 1;
		}
	}

	T.clear();
	if (Top3Freq.size() == 1) {
		T.push_back(Top3Freq[0].s);
	}
	else if (Top3Freq.size() == 2) {
		T.push_back(Top3Freq[0].s);
		T.push_back(Top3Freq[1].s);
	}
	else if (Top3Freq.size() >= 3) {
		T.push_back(Top3Freq[0].s);
		T.push_back(Top3Freq[1].s);
		T.push_back(Top3Freq[2].s);
	}

	Top3Freq.clear();
}

int Autocompleter::size_recurse(Node * root)
{
	if (root == nullptr) {    //Base Case
		return 0;
	}
	return size_recurse(root->left) + size_recurse(root->right) + 1;
}

void Autocompleter::completions_recurse(string x, Node * root, vector<Entry>& C)
{
	if (root == nullptr) {    //Base Case
		return;
	}

	//Put into vector C when the string is the same
	else if (root != nullptr) {
		if (root->e.s.substr(0, x.size()) == x) {
			C.push_back(root->e);
		}
		if (root->e.s > x) {
			completions_recurse(x, root->left, C);    //Recurse on left subtree
		}
		completions_recurse(x, root->right, C);     //Recurse on right subtree
	}
}

void Autocompleter::insert_recurse(Entry e, Node * root)
{
	if (root->e.s == e.s) {
		//cout << "Already Exists" << endl;
		return;
	}
	else if (root->e.s < e.s) {
		if (root->right != nullptr) {
			insert_recurse(e, root->right);
		}
		else {
			//cout << "New Right Node: ";
			root->right = new Node(e);
			root->right->height = 0;
			//cout << root->right->e.s << endl;
		}
	}
	else {
		if (root->left != nullptr) {
			insert_recurse(e, root->left);
		}
		else {
			//cout << "New Left Node: ";
			root->left = new Node(e);
			root->left->height = 0;
			//cout << root->left->e.s << endl;
		}
	}
	//cout << root->e.s << endl;
	int leftH = height(root->left);
	int rightH = height(root->right);

  ////Returns the max of two integers
	int max = ((leftH > rightH) ? leftH:rightH);
	root->height = max + 1;
	
	//cout << root->e.s << ": " << root->height << endl;
	rebalance(root);
}

void Autocompleter::rebalance(Node * root)
{
	int leftH = height(root->left);
	int rightH = height(root->right);
	int rotate = leftH - rightH;

	//Left Rotation
	if (rotate > 1) {
		right_rotate(root);
	}
	//Right Rotation
	else if (rotate < -1) {
		left_rotate(root);
	}
}

void Autocompleter::right_rotate(Node * root)
{
	Node *leftChild = root->left;
	root->left = leftChild->left;
	leftChild->left = leftChild->right;
	leftChild->right = root->right;
	root->right = leftChild;

	swap(root->e, leftChild->e);
}

void Autocompleter::left_rotate(Node * root)
{
 //Left rotation on a node x, we assume that its right child y is non-nil. 
	Node *rightChild = root->right;
	root->right = rightChild->right;
  //Turn right child's left subtree into roots right subtree
	rightChild->right = rightChild->left;
	rightChild->left = root->left;
	root->left = rightChild;

	swap(root->e, rightChild->e);
}