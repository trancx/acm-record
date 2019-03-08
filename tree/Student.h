/*
 * Student.h
 *
 *  Created on: Nov 15, 2017
 *      Author: trance
 */

#ifndef SRC_STUDENT_H_
#define SRC_STUDENT_H_

#include "BTree.h"
#include <string>

using namespace std;

class Student: public BNode {
public:
	Student(int , string );
	virtual ~Student();
	virtual void show() const;
	virtual int compare() const;
	virtual BNode * duplicate() const;
	virtual bool equivalent(const BNode *) const;
	static Student * newStudent();
private:
	int num;
	string name;
};

#endif /* SRC_STUDENT_H_ */
