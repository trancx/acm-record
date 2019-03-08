/*
 * BTree.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: trance
 */

#include "BTree.h"
#include "seqstack.h"
#include <iostream>

BTree::BTree( BNode * root ) {
	this->root = root;
}

BTree::BTree() : root(NULL) {
	// TODO Auto-generated constructor stub

}

BTree::~BTree() {
	// TODO Auto-generated destructor stub
	SeqStack<const BNode *> s;
		const BNode *pre = NULL, * p = root;
		while( p!=NULL || !s.isEmpty()) {
			while( p != NULL ) {
				s.push(p);
				p = p->left;
			}
			if( !s.isEmpty() ) {
				p = s.pop();
				pre = p;
				p = p->right;
				delete pre;
			}
		}
}

void BTree::insert(BNode * b) {
	BNode ** pre(&root);
	while( *pre ) {
		if( b->compare() > (*pre)->compare()) {
			pre = &(*pre)->right;
		} else {
			pre = &(*pre)->left;
		}
	}
	*pre = b;
}



void BTree::inorder(const BNode * b) const {
	SeqStack<const BNode *> s;
	const BNode * p = b;
	while( p!=NULL || !s.isEmpty()) {
		while( p != NULL ) {
			s.push(p);
			p = p->left;
		}
		if( !s.isEmpty() ) {
			p = s.pop();
			p->show();
			p = p->right;
		}
	}
}

void BTree::postorder(const BNode * b) const {
	rPostorder(b);
}

void BTree::preorder(const BNode * b) const {
	SeqStack<const BNode *> s;
	while( b != NULL || !s.isEmpty() ) {
		while( b != NULL) {
			b->show();
			s.push(b);
			b = b->left;
		}
		if( !s.isEmpty() ) {
			b = s.pop();
			// already show!
			b = b->right;
		}
	}
}

void BTree::rInorder(const BNode * b) const {
	if( b ) {
		if( b->left )
			rInorder(b->left);
		b->show();
		if( b->right )
			rInorder(b->right);
	}

}

void BTree::rPostorder(const BNode * b) const {
	if( b ) {
		if( b->left )
			rPostorder(b->left);
		if( b->right )
			rPostorder(b->right);
		b->show();
	}

}

void BTree::rPreorder(const BNode * b) const {
	if( b ) {
		b->show();
		if( b->left )
			rPreorder(b->left);
		if( b->right )
			rPreorder(b->right);
	}
}

BNode * BTree::duplicate(const BNode * src) const {
	BNode * ret(NULL);

	if( src ) {
		ret = src->duplicate();
		if( src->left )
			ret->left = duplicate(src->left);
		if( src->right)
			ret->right = duplicate(src->right);
	}

	return ret;
}

void BTree::show(const BNode * b ) const {
	if( b ) {
			b->show();
			cout << " my child { \n";
			if( b->left )
				show(b->left);
			if( b->right )
				show(b->right);
			cout << " } \n";
		}
}

int BTree::countLeaves(const BNode * b) const {
	int left(0), right(0);
	// assumes the root is non-null
	if( !b->left && !b->right )
		return 1;
	if( b->left)
		left = countLeaves(b->left);
	if( b-> right )
		right = countLeaves(b->right);

	return left + right;
}

int BTree::measure(const BNode * b) const {
	int right(0), left(0);

	if( !b->right && !b->left )
		return 1;
	if( b->right )
		right = measure(b->right);
	if( b->left )
		left = measure(b->left);

	return  left++ > right++ ? left: right;
}

void BTree::swap(BNode * b) {
	BNode * tmp(NULL);
	if( b ) {
		if( b->left )
			swap(b->left);
		if( b->right )
			swap(b->right);
		tmp = b->left;
		b->left = b->right;
		b->right = tmp;
	}
}

bool BTree::isEquivalent(const BNode * lhs,
		const BNode * rhs) const {
	bool lret(false), rret(false), ret(false);

	if( lhs && rhs )
		ret = lhs->equivalent(rhs);
	if( !ret )
		goto done;


	if( lhs->left && rhs->left) {
		lret = isEquivalent(lhs->left, rhs->left);
	} else if( lhs->left == rhs->left ) {
		lret = true;
	} // both are NULL
	if( !lret )
		goto done;

	if( lhs->right && rhs->right ) {
		rret = isEquivalent(lhs->right, rhs->right);
	} else if( lhs->right == rhs->right ) {
		rret = true;
	}

	// easily to induce short-circuit
done:
	return ret && lret && rret;
}

void BTree::makeSequential(BNode ** head, BNode * begin ) {
	// assumes the root is non-null
//	begin->show(); debug.
	if( !begin->left && !begin->right  ) {
		begin->right = *head;
		*head = begin;
		return; // if commented out , infinite loop
	}

	if( begin->right )
		makeSequential(head, begin->right);
	if( begin->left )
		makeSequential(head, begin->left);
}

void BTree::makeListed(BNode ** array,  BNode * node ) const {
	if( node ) {
		array[node->compare()-1] = node;
//		node->show();
		makeListed(array, node->left);
		makeListed(array, node->right);
	}
}
