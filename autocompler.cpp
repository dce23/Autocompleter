#include "autocompler.h"

Autocompleter::Autocompleter(string filename)
{
  root = nullptr;
	vector<Entry> E;
	string lines, times;
	ifstream text;
	
  string words = "";    //Text inputString
  //int times = 0;		    //Text inputFrequency

	text.open(filename);
	
	while(text >> words >> times) {
		//Create a new Entry object
		Entry newAC;
		newAC.s = words;            //Resets string input
		newAC.freq = stoi(times);   //Resets int input

		//Puts all the stuff from the file in vector E
		E.push_back(newAC);
	}

  text.close();

	root = construct_recurse(E, 0, E.size() - 1);
}

int Autocompleter::size()
{
  if (root == nullptr) {	//Base Case
		return 0;
	}

	return size_recurse(root);
}

void Autocompleter::completions(string x, vector<string> &T)
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

Autocompleter::Node* Autocompleter::construct_recurse(vector<Entry>& E, int l, int r)
{
	//Base Case if the portion of the vector to build a corresponding BST for. is empty.
	if (l > r) {
		return nullptr;
  }

  Entry cs;

  int mid = (l+r) / 2;
	cs.s = E[mid].s;
	cs.freq = E[mid].freq;

  //Allocate a new Node to be the root of the tree
	Node* node = new (struct Node);
	//Setting its Entry to be the Entry halfway between indices l and r in vector<Entry>
	Node* newBST = new Node(cs);

  /*if (newBST->e.s == newBST->e.s) {
		return newBST;
	}*/

	//Recursively construct a left sub tree from the elements of the vector<Entry> from l to m-1.
	//Point the left pointer of the root at the root of this subtree.
  if (r > mid) {          //Left Case
    newBST->left = nullptr;
    root = newBST;
    newBST->left = construct_recurse(E, l, mid - 1);
  }
	
  //Recursively construct a right sub tree from the elements of the vector<Entry> from m+1 to r.
	//Point the right pointer of the root at the root of this subtree.
  if (r > l) {                //Right Case
    newBST->right = nullptr;
		root = newBST;
	  newBST->right = construct_recurse(E, mid + 1, r);
  }
	
  //Special case where l, r havent moved. l = E.begin(); r = E.end(); set root

	return newBST;
}

int Autocompleter::size_recurse(Node* root)
{
	if (root == nullptr) {   //Base Case
		return 0;
	}

	return size_recurse(root->left) + size_recurse(root->right) + 1;
}

void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &T)
{
  if (root == nullptr) {    //Base Case
    return;
  }

	//Put into vector T when the string is the same
	else if (root != nullptr) {
		if (root->e.s.substr(0, x.size()) == x) {
			T.push_back(root->e);
		}		
		if (root->e.s > x) {
      completions_recurse(x, root->left, T);    //Recurse on left subtree
    }
    completions_recurse(x, root->right, T);     //Recurse on right subtree
	}
}