#include "emp.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// validation functions
int get_number(const std::string& prompt){
	int number;
	while (true)
	{
		cout << prompt;
		if (cin >> number && number > 0){
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return number; //valid number
		}

		cout << "Please enter a valid positive number\n";

		if (cin.eof()){
			throw runtime_error("Input stream closed!");
		}

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}
}
int get_menu_choice(){
	cout << "\nEMPLOYEE DIRECTORY\n"
		<< "========================\n"
		<< "1. Display all employees\n"
		<< "2. Searcb by employee id\n"
		<< "3. Add employee\n"
		<< "4. Update employee\n"
		<< "5. Remove employe\n"
		<< "6. Exit\n\n";

		int choice;
		while (true){
			choice = get_number("Choice: ");

			if (choice >= 1 && choice <= 6){
				return choice;
			}

			cout << "Please choose an option between 1 to 6!\n";
		}
}

std::string get_required_text(const std::string& prompt){
	string text;

	while (true){
		cout << prompt;

		if (!getline(cin, text)){
			throw runtime_error("Input stream closed!\n");
		}

		if (text.find_first_not_of("\t") != string::npos){
			return text;
		}

		cout << "This field cannot be empty!\n";
	}
}

// display and search functions
void display_all(const std::map<int, Employee>& employees){
	cout << "EMPLOYEE DIRECTORY\n"
		<< "=========================\n";

		if (employees.empty()){
			cout << "No employees found!\n";
			return;
		}

		int length = 25;

		cout << left << setw(5) << "ID" << setw(length) << "Name" << setw(length) 
		<< "Deparment" << setw(length) << "Email\n\n";

		for (const auto& employee : employees){
			cout << left << setw(5) << employee.first << setw(length) << employee.second.name << setw(length) 
			<< employee.second.department << setw(length) << employee.second.email << endl;
		}
}
void search_employees(const std::map<int, Employee>& employees){
	int id = get_number("Enter an employee id: ");
	auto it = employees.find(id);

	if (it == employees.end()){
		cout << "Employee not found!\n";
		return;
	}

	cout << "\nEmployee Found:\n"
		<< "ID: " << it->first << endl
		<< "Name: " << it->second.name << endl
		<< "Department: " << it->second.department << endl
		<< "Email: " << it->second.email << endl;

	}

void add_employee(std::map<int, Employee>& employees){
	int id = get_number("Enter a new employee id: ");

	if (employees.contains(id)){
		cout << "That employee id already exists!\n";
		return;
	}

	Employee employee;

	employee.name = get_required_text("Enter employee name: ");
	employee.department = get_required_text("Enter their department: ");
	employee.email = get_required_text("Enter their email: ");

	employees.insert({id, employee});
	cout << "Employee was added successfully!\n";
}

void update_employee(std::map<int, Employee>& employees){
	int id = get_number("Enter employee id to update: ");

	if (!employees.contains(id)){
                cout << "That employee doesn't exist!\n";
                return;
        }

        cout << "\nCurrent employee: " << employees.at(id).name << endl;
        cout << "\nCurrent department: " << employees.at(id).department << endl;
        cout << "\nCurrent email: " << employees.at(id).email << endl;

        employees.at(id).department = get_required_text("Enter new department: ");
        employees.at(id).email = get_required_text("Enter new email: ");

        cout << "Employee updated successfully!\n";

}

void remove_employee(std::map<int, Employee>& employees){
	int id = get_number("Enter employee id to remove: ");
	int removed = employees.erase(id);

	if (removed > 0){
		cout << "Employee removed successfully!\n";
	} else {
	cout << "Employee was not found or erased!\n";
	}
}

