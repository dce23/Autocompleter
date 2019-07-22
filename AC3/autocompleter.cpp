#include "autocompleter.h"
#include <iostream>

using namespace std;

Autocompleter::Autocompleter()
{
	root = new Node();
}

void Autocompleter::insert(string x, int freq)
{
	Entry newAC3;
	newAC3.s = x;
	newAC3.freq = freq;
	Node *curr = root;

	for (int i = 0; i <= x.length(); i++) {
		//UPDATE Top[]
		/*if (curr->top[0].freq < freq) {
			swap(curr->children[2], curr->children[1]);
			swap(curr->children[1], curr->children[0]);
			curr->top[0] = newAC3;
		}
		else if (curr->top[1].freq < freq) {
			swap(curr->children[2], curr->children[1]);
			curr->top[1] = newAC3;
		}
		else if (curr->top[2].freq < freq) {
			curr->top[2] = newAC3;
		}*/

		//Move to new Node. If non-existent, create one. Move down to next Node.
		int next_s_index = static_cast<int>(x[i]);

		if (curr->children[next_s_index] == nullptr) {
			curr->children[next_s_index] = new Node();
		}
		curr = curr->children[next_s_index];
	}
	//---------------------------------------------------
	if (!(curr->marked)) {
		count++;
	}
	curr->marked = true;
	//---------------------------------------------------
	/*Node *temp = root;
	for (int i = 0; i < x.length(); i++) {
		cout << x[i] << endl;
		int next_s_index = static_cast<int>(x[i]);
		temp = temp->children[next_s_index];
		cout << "Top 3 Matches of Letter: " << x[i];
		for (int y = 0; y < 3; y++) {
			cout << " || " << temp->top[y].s << " | ";
		}
		cout << "____" << endl;
	}
	cout << "------------" << endl;*/
	/*
	int i = 0;

	while (i < x.length())
	{
		if (i == x.length())
			break;

		//int next_idx = static_cast<int>(x[i]);
		if (curr->children[x[i]] == nullptr)
			curr->children[x[i]] = new Node();

		curr = curr->children[x[i]];
		++i;
	}
	if (curr->marked == false) {
		curr->marked = true;
	}*/
	
}

int Autocompleter::size()
{
	cout << count << endl;
	return count;
}

void Autocompleter::completions(string x, vector<string>& T)
{/*
	T.clear();
	Node *curr = root;

	for (int i = 0; i < x.length(); i++) {
		int index = static_cast<int>(x[i]);
		if (curr->children[index] == nullptr) {
			return;
		}
		curr = curr->children[index];
		if (!curr) {
			return;
		}
	}

	for (int i = 0; i < x.length(); i++) {
		if (curr->top[i].freq == -1) {
			break;
		}
		if (i > 0) {
			if (curr->top[i - 1].s == curr->top[i].s) {
				break;
			}
		}
		T.push_back(curr->top[i].s);
	}*/
}