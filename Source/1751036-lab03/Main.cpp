#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <iostream>
#include <vector>

#include "Shape.h"

// Global variables
int shapeType = 1;
bool startDraw, polygonOn, polygonDone;
float* startX = new float, * startY = new float, * endX = new float, * endY = new float;
Shape* currentShape = NULL;
std::vector<Shape*> shapePool;

void setIsDrawing(bool draw) {
	isDrawing = draw;
}

void setStartDraw(bool sDraw) {
	startDraw = sDraw;
}

Shape* getShape() {
	Shape* r = NULL;
	switch (shapeType) {
	case 1:
		r = new Rectanglee(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 2:
		r = new Circle(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 3:
		r = new Ellip(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 4:
		r = new Polygonn(startX, endX, startY, endY);
		polygonOn = true;
		polygonDone = false;
		setIsDrawing(true);
		break;
	}
	return r;
}

void brushing(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_CTRL) {
			//choose shape to tranform
			if (myMap[y][x].size() == 0) {
				std::cout << "No shape selected! Pls, retry!" << std::endl;
				return;
			}
			else {
				int sID = *myMap[y][x].rbegin();
				std::cout << "Choose shape ID: " << sID << std::endl;
				if (currentShape->getID()!=sID) delete currentShape;

				currentShape = shapePool[*myMap[y][x].rbegin()];
			}
		}

		else {
			setStartDraw(true);
			if (!polygonOn || polygonDone) currentShape = getShape();
			*startX = x;
			*startY = y;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		*endX = x;
		*endY = y;

		if (*endX > WIDTH) *endX = WIDTH;
		if (*endY > HEIGHT) *endY = HEIGHT;

		if (startDraw && !polygonOn) {
			//a shape finishes drawing
			currentShape->setID(shapePool.size());
			currentShape->draw();
			shapePool.push_back(currentShape);
		}

		if (startDraw && polygonOn) {
			currentShape->setID(shapePool.size());
			currentShape->draw();
		}

		setStartDraw(false);

		if (!polygonOn)
			*startX = *startY = *endX = *endY = -1;

		glutPostRedisplay();
	}
}

void drawing(int x, int y) {
	if (startDraw && !polygonOn) {
		*endX = x;
		*endY = y;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			if (polygonOn) {
				//a shape finishes drawing
				currentShape->setID(shapePool.size());
				currentShape->drawLastStroke();
				glutPostRedisplay();
				shapePool.push_back(currentShape);

				*startX = *startY = *endX = *endY = -1;
				polygonDone = true;
			}
			break;

		case 'l':
		case 'L':
			currentShape->rotate(-1);
			glutPostRedisplay();
			break;

		case 'r':
		case 'R':
			currentShape->rotate(1);
			glutPostRedisplay();
			break;

		case '+':
			currentShape->scale(1);
			glutPostRedisplay();
			break;

		case '-':
			currentShape->scale(-1);
			glutPostRedisplay();
			break;
	}
}

void specialKeyboard(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_UP:
		currentShape->translate(0, -1);
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		currentShape->translate(0, 1);
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		currentShape->translate(-1, 0);
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		currentShape->translate(1, 0);
		glutPostRedisplay();
		break;
	}

}

void render(void) {
	glPointSize(1.0);
	glColor3ub(255, 255, 255);

	glFlush();
}


void freeShapePool() {
	for (int i = 0; i < shapePool.size(); ++i) {
		if (shapePool[i]) delete shapePool[i];
		std::cout << shapePool[i]->getID() << std::endl;
	}
}

void mainMenuHandler(int choice) {
	shapeType = choice;
	switch (choice) {
	case 1:
	case 2:
	case 3:
		polygonOn = false;
		break;
	case 4:
		currentShape = new Polygonn(startX, endX, startY, endY);
		polygonOn = true;
		polygonDone = false;
		break;

	case 5:	// Exit
		delete startX, startY, endX, endY, currentShape;
		freeShapePool();
		exit(0);
		break;
	}
}

void prepareMenu() {
	glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);
	glutAddMenuEntry("Ellipse", 3);
	glutAddMenuEntry("Polygon", 4);
	glutAddMenuEntry("Exit", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void welcomeMessage() {
	std::cout << "WELCOME TO 2D TRANSFORMER" << std::endl << std::endl; 
	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%% Instruction %%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
	std::cout << "---- Default shape is RECTANGLE" << std::endl;
	std::cout << "--------- Other shapes are: CIRCLE, ELLIPSE, POLYGON" << std::endl << std::endl;
	std::cout << "---- Right mouse click: choose other shapes" << std::endl << std::endl;
	std::cout << "---- Draw RECTANGLE, CIRCLE and ELLIPSE: click and drag left mouse" << std::endl << std::endl;
	std::cout << "---- Draw POLYGON: click to place vertices, don't need to drag, press Esc to close the shape" << std::endl << std::endl;
	std::cout << "---- Ctrl + Left mouse click on shape's boundary to select shape for transformation:" << std::endl;
	std::cout << "--------- R/r/L/l key: Rotating clockwise/counter-clockwise" << std::endl;
	std::cout << "--------- Left/Right/Up/Down arrows: translating by 1 pixel" << std::endl;
	std::cout << "--------- +/-: Scale up/down by 10%" << std::endl;
	std::cout << "--------- You can also transform a newly drawn shape without having t0 click on it" << std::endl << std::endl;

	std::cout << "%%%%%%%%%%%%%%%%%%%%%%%% Program Log %%%%%%%%%%%%%%%%%%%%%%%%" << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(600, 100);
    glutInitWindowSize(WIDTH, HEIGHT);

	glewInit();

    glutCreateWindow("AnhThu Painter");
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	glClearColor(255, 255, 255, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	currentShape = new Rectanglee(startX, endX, startY, endY);
	polygonOn = false;
	setIsDrawing(true);

    glutDisplayFunc(render);

	setStartDraw(false);

	prepareMenu();
    glutMouseFunc(brushing);
	glutMotionFunc(drawing);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	welcomeMessage();

    glutMainLoop();

	delete startX, startY, endX, endY, currentShape;
	freeShapePool();

    return 0;
}