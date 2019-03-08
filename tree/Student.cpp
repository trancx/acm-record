/*
 * Student.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: trance
 */

#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student(int num, string name) {
	this->num = num, this->name  = name;

	// TODO Auto-generated constructor stub

}

Student::~Student() {
	// TODO Auto-generated destructor stub
}

int Student::compare() const {

	return num;
}

void Student::show() const {
	cout << "name: " << name << endl;
	cout << "num: " << num << endl;
}

BNode * Student::duplicate() const {
	Student * tmp =  new Student(num, name);

	return (BNode *)tmp;
}

bool Student::equivalent(const BNode * b) const {

	return num == b->compare();
}

Student * Student::newStudent() {
	int num(0);
	string s;
	cout << "number of student: ";
	cin >> num;
	cout << "name of student: ";
	cin >> s;

	return new Student(num, s);
}
