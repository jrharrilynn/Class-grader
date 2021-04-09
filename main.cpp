/-----------------------------------------------------------//
//CS 215 - 011–Project 2
//-----------------------------------------------------------// 
//Author: Jason Harrison
//Date:   03/22/2020
//Description: This application assists teachers in their grading process by modifying an array of students
//Assistance: I received help from no one.



#include <iostream>;
#include <iomanip>;
#include <fstream>;
#include <string>;
#include <sstream>>;
using namespace std;



const int MAX_STUDENTS = 5; // constant used for maximum number of students to an array
const int MAX_SCORES_PER_STUDENTS = 5; //constant used for maximum number of scores per student in an array
const int NOT_FOUND = -1; //used for searching


//creates a structure of type score that holds points made and points possible
struct score {
	int pointsMade;
	int pointsPossible;
};


//creates a structure of type Student, which holds the values for an ID number, first and last name, and the scores made from the student, with a max array size of 5
struct Student {
	int idNumber;
	string lastName;
	string firstName;
	int numScores;
	score P[MAX_SCORES_PER_STUDENTS];

};


//this function inializes the array for students to be empty
void init(Student s[], int& numStudents) {
	int i;
	int j;
	for (i = 0; i < numStudents; ++i) {
		s[i].idNumber = 0000;
		s[i].firstName = "";
		s[i].lastName = "";
		s[i].numScores = MAX_SCORES_PER_STUDENTS;
		for (j = 0; j < MAX_SCORES_PER_STUDENTS; ++j) {
			s[i].P[j].pointsMade = 0;
			s[i].P[j].pointsPossible = 0;
		};

	};

}

//this function loads up the "grades.txt" file, if no file exists, it will start with an empty class.
int load(Student S[], int& numStudents) {
	int i;
	int numofScores;
	int j;
	ifstream fin;
	fin.open("grades.txt");
	if (fin.fail()) {
		cout << "No data file found....starting new class" << endl;
	}
	else {
		fin >> numStudents;
		for (i = 0; i < numStudents; ++i) {
			fin >> S[i].idNumber;
			fin >> S[i].firstName;
			fin >> S[i].lastName;
			fin >> S[i].numScores;
			for (j = 0; j < S[i].numScores; ++j) {
				fin >> S[i].P[j].pointsMade;
				fin >> S[i].P[j].pointsPossible;
			};




		};


	};
	return numStudents;

};


// this function displays the logo to the user
void displayMenu() {
	cout << setw(25) << left << "*--------------------------------------------------*\n"
		<< "|                   Jason Harrison                 |\n"
		<< "|                     Grade-ient                   |\n"
		<< "*--------------------------------------------------*\n";
	cout << setw(25) << left << "A - Add a Student" << "D - Drop a Student\n";
	cout << setw(25) << left << "V - View Student" << "P - Print Class\n";
	cout << setw(25) << left << "S - Sort By Average" << "N - Sort by Name\n";
	cout << setw(25) << left << "E - Enter new Scores" << "X - Exit\n";
};

//this function looks throiugh a user input of strings and returns the first character of that string to be used
char getOption(string validOptions) {
	string userChoice;
	char choice;
	int indexer;
	do {
		cout << "Enter option: ";
		if (cin.peek() == '\n')cin.ignore();
		getline(cin, userChoice);

		choice = toupper(userChoice[0]);

		indexer = validOptions.find(choice);
		if (indexer == -1) {
			cout << "Invalid Option, choose one of 'ADNVEPSX' Please" << endl;
		}

	} while (indexer == -1);

	return choice;

};


//this function totals up the points made in some students array of points, and divied by that arrays total points to get that students average
float getAvg(score P[], int numStudents, int& sizeofScores) {
	float totalPointsPossible = 0;
	float totalMadePoints = 0;
	int i;
	float Avg;
	float returnNumber;

	for (i = 0; i < sizeofScores; ++i) {
		totalMadePoints = P[i].pointsMade + totalMadePoints;
		totalPointsPossible = P[i].pointsPossible + totalPointsPossible;
	};

	Avg = (totalMadePoints / totalPointsPossible) * 100;

	if (sizeofScores == 0) {
		returnNumber = 100.0;
	}
	else
		returnNumber = Avg;

	return returnNumber;
};

//uses the average grade to calculate a letter grade
char getGrade(float AVG) {
	char letterGrade = 'A';
	if (AVG >= 90)
		letterGrade = 'A';
	else if (AVG >= 80)
		letterGrade = 'B';
	else if (AVG >= 70)
		letterGrade = 'C';
	else if (AVG >= 60)
		letterGrade = 'D';
	else if (AVG < 60)
		letterGrade = 'E';

	return letterGrade;
};

//allows the user to input information for a student to add them to the class
void addStudent(Student s[], score p[], int& NumStudents)
{
	int i, j;
	if (NumStudents >= MAX_STUDENTS)
	{
		cout << "No more students can be added." << endl;
		i = MAX_STUDENTS;
	}
	else
	{

		cout << "Enter student ID number." << endl;
		cin >> s[NumStudents + 1].idNumber;
		cout << "Enter First and Last name." << endl;
		cin >> s[NumStudents + 1].firstName >> s[NumStudents + 1].lastName;

		do
		{

			cout << "Enter number of scores." << endl;
			cin >> s[NumStudents + 1].numScores;

			if (s[NumStudents+1].numScores < 0 || s[NumStudents].numScores > 5)
			{
				cout << "Invalid amount of scores, it must be between 0 and 5." << endl;
			}
		} while (s[NumStudents+1].numScores < 0 || s[NumStudents+1].numScores > 5);

		for (i = 0; i < s[NumStudents+1].numScores; i++)
		{

			cin >> s[NumStudents+1].P[i].pointsMade >> s[NumStudents+1].P[i].pointsPossible;
		}
	}




}

//writes out the current list of students to a file "gradesout.txt"
void write(Student S[], score P[], int numStudents) {
	int i;
	int j;
	ofstream fout;
	fout.open("gradsout.txt");
	if (fout.fail()) {
		cout << "Unable to open output File" << endl;
	}
	else {
		fout << numStudents << endl;
		for (i = 0; i < numStudents; ++i) {
			fout << S[i].idNumber << " " << setw(7) << left
				<< S[i].firstName << " " << setw(10) << left
				<< S[i].lastName << " "
				<< S[i].numScores << " ";
			for (j = 0; j < S[i].numScores; ++j) {
				fout << S[i].P[j].pointsMade << " ";
				fout << S[i].P[j].pointsPossible << " ";
			}
			fout << endl;



		}
	}
	cout << "File Written!\n";
};


//shows the user a report of the students at a given time
int printReport(Student s[], score p[], int& numStudents) {
	int i;
	int j;
	float avg;
	char grd;
	cout << " ID  " << "Name                 " << "   avg " << "  GRD " << " Scores                                  " << endl;
	cout << setw(4) << "---- " << setw(20) << left << "---------------------- " << setw(5) << right << "----- " << setw(5) << right << "--- " << "----------------------------------------" << endl;
	for (i = 0; i < numStudents; ++i) {
		avg = getAvg(s[i].P, numStudents, s[i].numScores);
		grd = getGrade(avg);
		cout << setw(4) << s[i].idNumber << " "
			<< setw(20) << left << (s[i].lastName + ", " + s[i].firstName)
			<< setw(7) << right << fixed << setprecision(1) << avg
			<< setw(5) << grd << " ";
		for (j = 0; j < s[i].numScores; ++j) {
			cout << setw(3) << right << s[i].P[j].pointsMade << "/" << setw(3) << right << s[i].P[j].pointsPossible << " ";
		}
		cout << endl;


	};
	system("pause");
	return(numStudents);
};


//a function to search an array for a given ID
int search(Student S[], int IDsearch) {
	int i;
	int index = -1;


	for (i = 0; i < MAX_STUDENTS; ++i) {

		if (S[i].idNumber == IDsearch) {
			index = i;
		}
	};

	return index;
};

//a function that will find a student with an ID, gotten from Cin, put into the "Search()" function to retrieve the student
int findStudent(Student S[]) {
	int idNumber;
	int index;
	cout << "enter an ID to search for: ";
	cin >> idNumber;
	index = search(S, idNumber);
	if (index == -1) {
		cout << "student id " << idNumber << " not found!" << endl;
	}
	return index;


}

//a functiont that removes a student from a given index
Student removeStudent(Student S[], int& index, int& numStudents) {
	Student rem;
	if (index >= 0 && index < numStudents) {
		rem = S[index];
		numStudents--;
		for (int i = index; i < numStudents; i++)
			S[i] = S[i + 1];
		S[numStudents].idNumber = 0;
		S[numStudents].firstName = "";
		S[numStudents].lastName = "";
		S[numStudents].numScores = 0;
	}
	return rem;
}

//this function invokes findstudent and remove student to remove a student from the class
void dropStudent(Student S[], int& numStudents) {
	int index;
	Student rem;

	index = findStudent(S);
	if (index != -1) {
		rem = removeStudent(S, index, numStudents);
		cout << rem.firstName << " " << rem.lastName << " dropped." << endl;
	}

};


//this allows the user to see a report of a certain user
void viewStudent(Student S[], int& numStudents) {

	int index = findStudent(S);

	if (index >= 0) {
		int Avg = getAvg(S[index].P, numStudents, S[index].numScores);
		char Grd = getGrade(Avg);
		cout << endl;
		cout << "ID: " << S[index].idNumber << " Name: " << S[index].lastName << ", " << S[index].firstName << endl;
		cout << "Avg: " << fixed << setprecision(1) << Avg << "   Grade:   " << Grd << endl;
		cout << "Number of Scores:  " << S[index].numScores << endl;
		cout << "Scores:                     ";

		for (int i = 0; i < S[index].numScores; ++i) {
			cout << S[index].P[i].pointsMade << "/" << S[index].P[i].pointsPossible << " ";

		}
		cout << endl;

	}
}

//this is a swap function
void Swap(Student S[], int& index1, int& index2) {
	Student temp = S[index1];
	S[index1] = S[index2];
	S[index2] = temp;
}

//this sorts the class by name
void sortByName(Student S[], int& numStudents) {

	for (int i = 1; i < numStudents - 1; i++) {
		for (int j = i + 1; j < numStudents; j++)
			if ((S[i].firstName + S[i].lastName) > (S[j].firstName + S[j].lastName)) {
				Swap(S, i, j);
			};
	}
	cout << "class Sorted by name" << endl;
	system("pause");
};


//this sorts the class by average
void sortByAverage(Student S[], int& numStudents) {
	for (int i = 0; i < numStudents - 1; i++) {
		for (int j = i + 1; j < numStudents; j++) {
			float Avg1 = getAvg(S[i].P, numStudents, S[i].numScores);
			float Avg2 = getAvg(S[j].P, numStudents, S[j].numScores);
			if (Avg1 < Avg2) {
				Swap(S, i, j);
			}

		};
	}
	cout << "class sorted by Average" << endl;
	system("pause");
}

//this function allows the user to enter scores
void enterScores(Student S[], score P[], int& numStudents) {
	sortByName(S, numStudents);
	int pointsPossible;
	cout << "Enter total points possible for this assignment: ";
	cin >> pointsPossible;

	cout << "Enter the points made for each student" << endl;

	for (int i = 0; i < numStudents; i++) {
		cout << setw(4) << left << S[i].idNumber << " " << setw(10) << left << S[i].lastName << "," << setw(15) << left << S[i].firstName;
		if (S[i].numScores == MAX_SCORES_PER_STUDENTS) {
			cout << "Max Scores Reached for student" << endl;
		}
		else {
			S[i].numScores = S[i].numScores + 1;
			cin >> S[i].P[S[i].numScores].pointsMade;
			S[i].P[S[i].numScores].pointsPossible = pointsPossible;
		}



	}
	cout << endl;
};
int main() {
	Student S[MAX_STUDENTS];
	score P[MAX_SCORES_PER_STUDENTS];
	string validOptions = "ADNVEPSX";
	char userChoice;
	float avg;
	int numStudents=0;
	int i;
	



	init(S, numStudents);
	//load(S, numStudents);

	for (i = 0; i < MAX_STUDENTS; ++i) {
		if (S[i].firstName == "") {
			numStudents = i;
		}
		else
			numStudents = MAX_STUDENTS;
	};

	do {
		displayMenu();
		userChoice = getOption(validOptions);
		if (userChoice == 'a' || userChoice == 'A') {
			addStudent(S, P, numStudents);
			++numStudents;
		}
		else if (userChoice == 'p' || userChoice == 'P') {
			for (i = 0; i < MAX_STUDENTS; ++i) {
				if (S[i].firstName == "") {
					numStudents = i;
				}
				else
					numStudents = MAX_STUDENTS;
			};
			numStudents = printReport(S, P, numStudents);
		}
		else if (userChoice == 'D' || userChoice == 'd') {
			dropStudent(S, numStudents);
			numStudents = numStudents - 1;

		}
		else if (userChoice == 'v' || userChoice == 'V') {
			for (i = 0; i < MAX_STUDENTS; ++i) {
				if (S[i].firstName == "") {
					numStudents = i;
				}
				else
					numStudents = MAX_STUDENTS;
			};
			viewStudent(S, numStudents);
		}
		else if (userChoice == 'N' || userChoice == 'n') {

			for (i = 0; i < MAX_STUDENTS; ++i) {
				if (S[i].firstName == "") {
					numStudents = i;
				}
				else
					numStudents = MAX_STUDENTS;


			};
			sortByName(S, numStudents);

		}
		else if (userChoice == 'S' || userChoice == 's') {
			for (i = 0; i < MAX_STUDENTS; ++i) {
				if (S[i].firstName == "") {
					numStudents = i;
				}
				else
					numStudents = MAX_STUDENTS;


			};
			sortByAverage(S, numStudents);
		}
		else if (userChoice == 'E' || userChoice == 'e') {


			for (i = 0; i < MAX_STUDENTS; ++i) {
				if (S[i].firstName == "") {
					numStudents = i;
				}
				else
					numStudents = MAX_STUDENTS;


			};
			enterScores(S, P, numStudents);

		}






	} while (userChoice != 'x' && userChoice != 'X');

	for (i = 0; i < MAX_STUDENTS; ++i) {
		if (S[i].firstName == "") {
			numStudents = i;
		}
		else
			numStudents = MAX_STUDENTS;
	};
	write(S, P, numStudents);
	cout << "Thank you for using Grad-ient" << endl;




	system("pause");
	return(0);
}
