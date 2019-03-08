/*
 * main.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: trance
 */


#include "BTree.h"
#include "Student.h"
#include "seqstack.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>

using namespace std;




int main () {
	int swt(0);
	BTree t;
	string s;
	int num;
	size_t size;

	fstream  f("log");
	if( f.is_open() ) {
//		cout << "open" << endl;

		while( !f.eof() ) {
			f >> s;
			f >> num;
			f.get();
			if( f.peek()  == EOF  )
				break;
			t.insert(new Student(num, s));
		}


		/**
		 *  g: 	instream
		 *  p:	outstream
		 *
		 *  fstream is the same!!
		 *  但是输入输出分开一类管理的时候估计不一样。

			cout << "gpos: " << f.tellg() << endl;
			cout << "ppos: " << f.tellp() << endl;
			f.seekp(0, ios::end);
			f.seekg(1, ios::beg);
			cout << "gpos: " << f.tellg() << endl;
			cout << "ppos: " << f.tellp() << endl;
			a[99] = 0;
			cout << a << endl;
		 */

	}

	while( 1 ) {
		cout<<"请输入您要进行的操作："<<endl;
		cout<<"1------添加数据(空则创建树)"<<endl
			<<"2------前序递归遍历二叉树"<<endl
			<<"3------中序递归遍历二叉树"<<endl
			<<"4------后序递归遍历二叉树"<<endl
			<<"5------前序非递归遍历二叉树"<<endl
			<<"6------中序非递归遍历二叉树"<<endl
			<<"7------后序非递归遍历二叉树"<<endl
			<<"8------求树高"<<endl
			<<"9------求叶子总数"<<endl
			<<"10-----输出二叉树"<<endl
			<<"0-----退出"<<endl << endl << endl;
		cout << "选择: ";
		cin >> swt;
		switch( swt ) {
			default:
			case 0:
				goto out;
				break;
			case 1:
				t.insert(Student::newStudent());
				cout << "successfully!" << endl;
				break;
			case 2:
				t.rPreorder(t.getRoot());
				break;
			case 3:
				t.rInorder(t.getRoot());
				break;
			case 4:
				t.rPostorder(t.getRoot());
				break;
			case 5:
				t.preorder(t.getRoot());
				break;
			case 6:
				t.inorder(t.getRoot());
				break;
			case 7:
				t.postorder(t.getRoot());
				break;
			case 8:
				cout << "height: " << t.measure(t.getRoot()) << endl;
				break;
			case 9:
				cout << "leaves: " << t.countLeaves(t.getRoot()) << endl;
				break;
			case 10:
				t.show(t.getRoot());
				break;
		}
		sleep(2);
		cout << endl << endl;

	}
	f.close();
out:
	return 0;
}






/**
 * @NOTE:
 * 	 递归前序遍历数组完全二叉树
 */
void preInorder(Student * list, int pos, int length, BTree * t) {
	// assumes the root is non null
	if( t )
		t->insert(&list[pos-1]);
	if( pos * 2 <= length )
		preInorder(list, pos * 2, length, t); //child
	if( pos * 2 + 1 <= length)
		preInorder(list, pos*2 + 1, length, t);
}


/**
 * @NOTE：
 * 		非递归前序遍历数组完全二叉树
 */
void inorder(Student * list, int pos, int length) {
	SeqStack<int> s;
	while( pos <= length || !s.isEmpty()) {
		while( pos <= length ) {
			s.push(pos);
			pos*=2;
		}
		if( !s.isEmpty() ) {
			pos = s.pop();
			list[pos-1].show();
			pos = pos * 2 + 1; // to right
		}
	}
}
