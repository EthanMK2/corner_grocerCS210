#include <Python.h>  // not sure why this is acting up
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

// Functions to help call python functions
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("pythonFunctions");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonFunctions");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

void callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonFunctions");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

}


void main()
{
	int userOption = -1;  // user input
	string userItem;
	
	while (userOption != 4) {
		cout << "1: Display a list of item frequency" << endl;  // menu
		cout << "2: Display frequency of a specific item" << endl;
		cout << "3: Write .dat file and display histogram" << endl;
		cout << "4: Exit" << endl;
		cout << "Enter your option as a number 1, 2, 3, or 4." << endl;

		cin >> userOption;  // menu input validation
		if (cin.fail() == true) {
			cout << "Enter valid integer option." << endl;
			cin.clear();
			cin.ignore();
			continue;
		}

		if (userOption == 1) {  // option 1
			callIntFunc("FrequencyList", "nothing");  // does nothing with string parameter, but cpp needs one 
		}

		if (userOption == 2) {  // option 2
			cout << "Enter an item:" << endl;
			cin >> userItem;

			cout << callIntFunc("ItemFrequency", userItem) << endl;
		}

		if (userOption == 3) {  // option 3
			callIntFunc("DataFileAndHistogram", userItem);

			fstream datFile;
			datFile.open("frequency.dat", ios::in);  // open dat file in read mode
			
			if (datFile.is_open()) {
				string item;
				int frequency;
				while (!datFile.eof()) {  // each iteration is a item and its frequency
					datFile >> item;
					datFile >> frequency;
					cout << item << " ";
					for (int i = 0; i < frequency; i++) {
						cout << "|";
					}
					cout << endl;
				}

			}
			datFile.close();

		}

	}
}
