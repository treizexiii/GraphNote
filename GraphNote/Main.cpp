#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "GL/glut.h"


using namespace std;

const int MAXSTRING = 16;
int MAXSTUDENTS;

struct Student {
	char firstName[MAXSTRING];
	char lastName[MAXSTRING];
	float score;
};

Student* classRoom = NULL;

void addStudent(Student& student);
void studentToString(Student student);
void graphique();
void graphiqueAffichage();
void graphiqueRedim(int x, int y);
float averageScore(Student* student);


int main() {
	cout << "***GraphNote***" << endl;

	bool run = true;

	while (run) {
		system("cls");
		cout << "********** Menu **********" << endl;
		cout << "1 - Créer une classe " << endl;
		cout << "2 - Afficher la classe " << endl;
		cout << "3 - Afficher un graphique" << endl;
		cout << "4 - quitter le programme" << endl;

		int choice = 0;
		cin >> choice;

		//while (choice < 1 || choice > 4) {
		//	cout << "Erreur de saisie" << endl;
		//	cout << "Merci de refaire votre choix." << endl;
		//	cin >> choice;
		//}

		switch (choice)
		{
		case 1: {
			system("cls");
			cout << "Saisir le nombre d'eleves dans la classe :";

			cin >> MAXSTUDENTS;

			while (MAXSTUDENTS < 1)
			{
				cout << "Erreur, la classe doit compter au moins un eleve : ";
				cin >> MAXSTUDENTS;
			}

			classRoom = new Student[MAXSTUDENTS];

			if (classRoom == NULL) {
				cout << "Erreur lors de l'allocation du tableau." << endl;
				system("pause");
				exit(0);
			}

			for (int i = 0; i < MAXSTUDENTS; i++)
			{
				addStudent(classRoom[i]);
				studentToString(classRoom[i]);
				system("pause");
			}

			cout << "Fin de la saisie." << endl;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			if (classRoom == NULL) {
				cout << "Erreur, la classe n'a pas ete cree." << endl;
				system("pause");
				break;
			}
			else
			{
				for (int i = 0; i < MAXSTUDENTS; i++)
				{
					cout << setfill(' ')
						<< setw(2) << i + 1 << " : "
						<< setw(20) << classRoom[i].lastName
						<< setw(20) << classRoom[i].firstName
						<< "\t" << classRoom[i].score << endl;
				}
				system("pause");
				break;
			}
		}
		case 3: {
			graphique();
			break;
		}
		case 4: {
			run = false;
			break;
		}
		default:
			cout << "Erreur de saisie" << endl;
			system("pause");
			break;
		}
	}

	cout << "Fin du programme." << endl;
	system("pause");

	delete[] classRoom;

	return EXIT_SUCCESS;
}

void addStudent(Student& student)
{
	cout << "Entrez un nom :";
	cin >> ws;
	cin.get(student.lastName, MAXSTRING);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear  cin's buffer

	cout << "Entrez un prenom :";
	cin >> ws;
	cin.get(student.firstName, MAXSTRING);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear  cin's buffer

	cout << "Entrez une moyenne :";
	cin >> student.score;
	while (student.score < 0 || student.score > 20)
	{
		cout << "La moyenne doit être compris entre 0 et 20 :";
		cin >> student.score;
	}
}

void studentToString(Student student)
{
	cout << "L'eleve " << student.lastName << " " << student.firstName << " a " << student.score << " de moyenne." << endl;
}

void graphique() {
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Graphique");

	glutDisplayFunc(graphiqueAffichage);
	glutReshapeFunc(graphiqueRedim);

	glutMainLoop();
}

void graphiqueAffichage() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Instruction here

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < MAXSTUDENTS; i++)
	{
		glVertex2d(i, classRoom[i].score);
	}
	glEnd();

	glColor3d(0.3, 0.3, 1);
	glBegin(GL_LINES);
	for (int i = 0; i <= 20; i += 5)
	{
		glVertex2d(0, i);
		glVertex2d(MAXSTUDENTS - 1, i);
	}
	glEnd();

	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	float average = averageScore(classRoom);
	glVertex2d(0, average);
	glVertex2d(MAXSTUDENTS - 1, average);

	glEnd();

	// Instruction end

	glFlush(); // flush the pipeline
}

void graphiqueRedim(int x, int y) {
	glViewport(10, 10, x - 20, y - 20);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAXSTUDENTS - 1, 0, 20.1);
}

float averageScore(Student* student)
{
	int total = 0;
	for (int i = 0; i < MAXSTUDENTS; i++)
	{
		total += classRoom[i].score;
	}
	return total / MAXSTUDENTS;
}
