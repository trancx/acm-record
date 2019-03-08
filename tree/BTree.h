/*
 * BTree.h
 *
 *  Created on: Nov 15, 2017
 *      Author: trance
 */

#ifndef SRC_BTREE_H_
#define SRC_BTREE_H_

#include <string>

using namespace std;

class BNode {
public:
	BNode() : left(NULL), right(NULL) {}
	virtual ~BNode() {}
	virtual  void show() const = 0;
	virtual int compare() const = 0;
	virtual BNode * duplicate() const = 0;
	virtual bool equivalent(const BNode * ) const = 0;
	BNode * left;
	BNode * right;
};

class BTree {
public:
	BTree( BNode * root);
	BTree();
	virtual ~BTree();
	void search(int num) const;
	void insert( BNode * b);
	void _delete(string name);
	void preorder(const BNode *) const;
	void inorder(const BNode *) const;
	void postorder(const BNode *) const;
	// recursive...
	void rPreorder(const BNode *) const;
	void rInorder(const BNode *) const;
	void rPostorder(const BNode *) const;
	int measure(const BNode * ) const;

	//datastructure.
	int countLeaves(const BNode * ) const;
	void show(const BNode *) const ;
	void swap(BNode * b);
	BNode * duplicate( const BNode * src) const;
	void makeListed(BNode ** , BNode * head) const;
	void makeSequential(BNode ** , BNode *);
	bool isEquivalent(const BNode * , const BNode * ) const;
	BNode * getRoot() const {
		return root;
	}
	void toArray() const;
private:
	BNode * root;
};


#endif /* SRC_BTREE_H_ */
