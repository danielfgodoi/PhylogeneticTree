/**
 *
 * Author: Daniel de Faria Godoi
 * Subject: Introduction to Bioinformatics (Introdução à Bioinformática)
 * Title: Phylogenetic Trees (Árvores Filogenéticas)
 * Description: Check if a given matrix admits perfect phylogeny, and if it admits, build a phylogenetic tree.
 *
 * To compile, use
 * g++ *.cpp -Wall -pedantic -ansi
 * g++ -o PhylogeneticTree PhylogeneticTree.cpp -Wall -pedantic -ansi
 * 
 * Example to execute
 * ./a.out
 * ./PhylogeneticTree
 *
 */

#ifndef __PhylogeneticTree_h
#define __PhylogeneticTree_h

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

class Vertex
{
public:
	Vertex()
	{
		// cout << "I'm the Vertex constructor!" << endl;
		right = 0;
		left = 0;
		rightEdge = 0;
		leftEdge = 0;
		object = 0;
	}

	~Vertex(){}

	void insert(string name)
	{

	}

	Vertex *right;
	Vertex *left;

	int rightEdge;
	int leftEdge;
	int tag;
	int object;
};

/**
 *
 * PhylogeneticTree class that contains all the data.
 *
 */
class PhylogeneticTree
{
public:
	PhylogeneticTree(int n, int m)
	{
		this->n = n;
		this->m = m;
		this->k = 0;

		V.resize(m);

		M.resize(n);
		for (int i = 0; i < n; ++i)
		{
			M[i].resize(m);
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				cin >> M[i][j];
			}
		}
	}

	/**
	 *
	 * Default destructor for SequenceAlignment Class.
	 * Vector C++ STL has its own destructor so no need to manually destruct it.
	 *
	 */
	~PhylogeneticTree(){}

	bool admitsPerfectPhylogeny();
	void sort();
	void buildPerfectPhylogeny();
	void printPerfectPhylogeny();

	int n; // Number of rows
	int m; // Number of columns
	int k; // Number of nodes

	// Vector representing characteristics
	vector<int> V;

	// Vector representing nodes by tags
	vector<Vertex*> T;
	
	// Multidimensional STL vector from <vector> library
	vector< vector<int> > M;
};

/**
 *
 * Method that checks if the matrix admits perfect phylogeny.
 *
 */
bool PhylogeneticTree::admitsPerfectPhylogeny()
{
	// Sort method to sort the matrix columns by number of 1s
	sort();

	int k, l;
	vector< vector<int> > L;

	L.resize(n);

	for (int i = 0; i < n; ++i)
	{
		L[i].resize(m);
	}

	// This algorithm was based on the class notes of Zanoni Dias (Unicamp)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			L[i][j] = 0;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		k = -1;
		for (int j = 0; j < m; ++j)
		{
			if (M[i][j] == 1)
			{
				L[i][j] = k;
				// Here we add 1 to j because the author considers that the array starts at position 1
				k = j + 1;
			}
		}
	}

	for (int j = 0; j < m; ++j)
	{
		l = 0;
		for (int i = 0; i < n; ++i)
		{
			if (L[i][j] != 0)
			{
				if (l == 0)
				{
					l = L[i][j];
				}

				else if (L[i][j] != l)
				{
					return false;
				}
			}
		}
	}

	return true;
}

/**
 *
 * Sort method to sort the matrix columns by number of 1s.
 * Own implementation!
 * This algorithm uses a bucket to put the column's values
 * and then copy the entire column to the original matrix.
 *
 * Complexity:
 * O(N x M) to put the values in the bucket.
 * O(N² x M) to browse the bucket and copy the columns.
 *
 */
void PhylogeneticTree::sort()
{
	int numberOfOnes;

	// Bucket
	vector< vector<int> > B(n+1);

	// Auxiliary matrix
	vector< vector<int> > A;	

	for (int j = 0; j < m; ++j)
	{
		// Characteristics vector
		V[j] = j + 1;

		numberOfOnes = 0;
		for (int i = 0; i < n; ++i)
		{
			if (M[i][j] == 1)
				numberOfOnes++;
		}

		B[numberOfOnes].push_back(j+1);
	}

	// Matrix A <- M and auxiliary index
	A = M;
	int x = 0;

	for (int i = B.size() - 1; i >= 0; --i)
	{
		vector<int>::iterator it = B[i].end();
		int j = 0;

		while (it != B[i].begin())
		{
			for (int y = 0; y < n; ++y)
			{
				M[y][x] = A[y][B[i][j]-1];
			}

			V[x] = B[i][j];

			++x;
			++j;
			--it;
		}
	}

	// Only for debugging.

	// cout << endl;
	// for (int i = 0; i < n; ++i)
	// {
	// 	for (int j = 0; j < m; ++j)
	// 	{
	// 		cout << M[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	// cout << endl;

	// for (int i = 0; i < m; ++i)
	// {
	// 	cout << V[i] << " ";
	// }

	// cout << endl;
}

/**
 *
 * Method that builds a perfect phylogeny.
 *
 */
void PhylogeneticTree::buildPerfectPhylogeny()
{
	// Create Phylogenetic Tree
	Vertex *root = new Vertex();
	Vertex *current;
	k++;

	bool cameFromLeft = 0;

	for (int i = 0; i < n; ++i)
	{
		current = root;
		for (int j = 0; j < m; ++j)
		{
			if (M[i][j] == 1)
			{
				if (current->rightEdge == V[j])
				{
					current = current->right;
					cameFromLeft = 0;
				}

				else if (current->leftEdge == V[j])
				{
					current = current->left;
					cameFromLeft = 1;
				}

				else if (!cameFromLeft)
				{
					if (current->right == 0)
					{
						current->right = new Vertex();
						current->rightEdge = V[j];
						current = current->right;
						k++;
					}

					else if (current->left == 0)
					{
						cameFromLeft = 1;
						current->left = new Vertex();
						current->leftEdge = V[j];
						current = current->left;
						k++;
					}
				}

				else
				{
					if (current->left == 0)
					{
						current->left = new Vertex();
						current->leftEdge = V[j];
						current = current->left;
						k++;
					}

					else if (current->right == 0)
					{
						current->right = new Vertex();
						current->rightEdge = V[j];
						current = current->right;
						k++;
					}
				}
			}
		}
		current->object = i+1;
	}

	// Breadth-first search to read the tree and add a new vertex for each internal vertex that has an object.
	// Note: Some code are only for debugging purpose.
	queue<Vertex*> q;
	int tag = 0;
	// vector<Vertex*> a;
	
	q.push(root);
	// a.push_back(root);

	while (!q.empty())
	{
		Vertex *v = q.front();
		T.push_back(v);
		q.pop();
		
		v->tag = tag++;

		if (v->object != 0)
		{
			if (v->right != 0 || v->left != 0)
			{
				if (v->right == 0)
				{
					v->right = new Vertex();
					v->right->object = v->object;
					v->object = 0;
					k++;
				}

				else if (v->left == 0)
				{
					v->left = new Vertex();
					v->left->object = v->object;
					v->object = 0;
					k++;
				}
			}
		}

		if (v->left != 0)
		{
			q.push(v->left);
			// a.push_back(v->left);
		}

		if (v->right != 0)
		{
			q.push(v->right);
			// a.push_back(v->right);
		}
	}

	// for (int i = 0; i < a.size(); ++i)
	// {
	// 	cout << a[i]->leftEdge << " " << a[i]->rightEdge << endl << endl;
	// }
}

/**
 *
 * Method that prints the tree.
 *
 */
void PhylogeneticTree::printPerfectPhylogeny()
{
	vector< vector<int> > R;

	R.resize(k);
	for (int i = 0; i < k; ++i)
	{
		R[i].resize(k);
	}

	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			R[i][j] = -1;
		}
	}

	for (int i = 0; i < k; ++i)
	{
		if (T[i]->left != 0)
		{
			R[T[i]->tag][T[i]->left->tag] = T[i]->leftEdge;
			// cout << T[i]->tag << endl;
			// cout << T[i]->left->tag << endl;
			// cout << T[i]->leftEdge << endl;
			// cout << endl;
		}

		if (T[i]->right != 0)
		{
			R[T[i]->tag][T[i]->right->tag] = T[i]->rightEdge;
			// cout << T[i]->tag << endl;
			// cout << T[i]->right->tag << endl;
			// cout << T[i]->rightEdge << endl;
			// cout << endl;
		}
	}

	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			cout << R[i][j] << " ";
		}
		cout << endl;
	}
}

/**
 *
 * Main method to call the SequenceAlignment methods.
 *
 */
int main(int argc, char const *argv[])
{
	int n, m;
	// cout << "Please enter the matrix size: ";
	cin >> n >> m;

	while (n != 0 && m != 0)
	{
		if (n <= 100 && m <= 50)
		{
			PhylogeneticTree* phylogeneticTree = new PhylogeneticTree(n, m);
			if (phylogeneticTree->admitsPerfectPhylogeny())
			{
				// cout << "Filogenia perfeita existe!" << endl;
				phylogeneticTree->buildPerfectPhylogeny();
				phylogeneticTree->printPerfectPhylogeny();
			}

			else cout << "filogenia perfeita nao existe" << endl;

			cout << endl;
		}

		// cout << "Please enter the matrix size: ";
		cin >> n >> m;
	}

	return 0;
}

#endif