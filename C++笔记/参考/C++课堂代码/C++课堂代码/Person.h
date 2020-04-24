#pragma once


class Person
{
	void SetPerson(char* name, char* gender, int age);
	void PrintPerson();

	// 用来描述类属性的成员变量信息
	char* _name;
	char* _gender;
	int _age;
};