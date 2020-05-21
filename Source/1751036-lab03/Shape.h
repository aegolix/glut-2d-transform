#ifndef _SHAPE_
#define _SHAPE_

#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>
#include <set>

#define PI 3.14159265
#define WIDTH 500
#define HEIGHT 500

bool isDrawing;
std::vector<std::vector<std::set<int>>> myMap(HEIGHT + 1, std::vector<std::set<int>>(WIDTH + 1, std::set<int>()));

class Shape {
public:
	float *px1, *px2, *py1, *py2;

	Shape() {
		;
	}

	Shape(float* _x1, float* _x2, float* _y1, float* _y2) : px1(_x1), px2(_x2), py1(_y1), py2(_y2) {
		;
	}

	virtual void draw() = 0;

	virtual void rotate(int d) = 0;

	virtual void translate(float dx, float dy) = 0;

	virtual void scale(int d) = 0;

	virtual void clear() = 0;

	virtual void drawLastStroke() = 0;

	virtual void setID(int gID) = 0;

	virtual int getID() = 0;

	~Shape() {
		;
	}
};

class Line : public Shape {
public:
	int shapeID;

	Line(float *_x1, float *_x2, float *_y1, float *_y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {
		if (*px1 < -1 || *px2 < -1 || *py1 < -1 || *py2 < -1 || *px1 > WIDTH || *px2 > WIDTH || *py1 > HEIGHT || *py2 > HEIGHT) {
			return;
		}

		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			float x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;
			float x = x1, y = y1;
			int w = x2 - x;
			int h = y2 - y;
			int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
			if (w < 0) dx1 = -1; else if (w > 0) dx1 = 1;
			if (h < 0) dy1 = -1; else if (h > 0) dy1 = 1;
			if (w < 0) dx2 = -1; else if (w > 0) dx2 = 1;
			int longest = abs(w);
			int shortest = abs(h);
			if (!(longest > shortest)) {
				longest = abs(h);
				shortest = abs(w);
				if (h < 0) dy2 = -1; else if (h > 0) dy2 = 1;
				dx2 = 0;
			}
			int numerator = longest >> 1;

			glBegin(GL_POINTS);
			glColor3ub(145, 83, 58);
			for (int i = 0; i <= longest; i++) {

				glVertex2i(x, y);

				myMap[y][x].insert(shapeID);

				numerator += shortest;
				if (!(numerator < longest)) {
					numerator -= longest;
					x += dx1;
					y += dy1;
				}
				else {
					x += dx2;
					y += dy2;
				}
			}
			glEnd();	
		}
	}

	void clear() {
		if (*px1 < -1 || *px2 < -1 || *py1 < -1 || *py2 < -1 || *px1 > WIDTH || *px2 > WIDTH || *py1 > HEIGHT || *py2 > HEIGHT) {
			return;
		}

		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			float x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;
			float x = x1, y = y1;
			int w = x2 - x;
			int h = y2 - y;
			int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
			if (w < 0) dx1 = -1; else if (w > 0) dx1 = 1;
			if (h < 0) dy1 = -1; else if (h > 0) dy1 = 1;
			if (w < 0) dx2 = -1; else if (w > 0) dx2 = 1;
			int longest = abs(w);
			int shortest = abs(h);
			if (!(longest > shortest)) {
				longest = abs(h);
				shortest = abs(w);
				if (h < 0) dy2 = -1; else if (h > 0) dy2 = 1;
				dx2 = 0;
			}
			int numerator = longest >> 1;

			glBegin(GL_POINTS);
			glColor3ub(255, 255, 255);
			for (int i = 0; i <= longest; i++) {

				if (myMap[y][x].size() == 1 && myMap[y][x].count(shapeID) > 0) {
					glVertex2i(x, y);
				}

				myMap[y][x].erase(shapeID);

				numerator += shortest;
				if (!(numerator < longest)) {
					numerator -= longest;
					x += dx1;
					y += dy1;
				}
				else {
					x += dx2;
					y += dy2;
				}
			}
			glEnd();
		}
	}

	void drawLastStroke() {
		;
	}

	void rotate(int d) {
		;
	}

	void translate(float dx, float dy) {
		;
	}

	void scale(int d) {
		;
	}

	void setID(int gID) {
		shapeID = gID;
	}

	int getID() {
		return shapeID;
	}
};

class Rectanglee : public Shape {
private:
	float x1, y1, x2, y2, xA, xB, yA, yB;
	int shapeID, degree;
public:
	Rectanglee(float* _x1, float* _x2, float* _y1, float* _y2) : Shape(_x1, _x2, _y1, _y2) {
		xA = xB = yA = yB = x1 = y1 = x2 = y2 = -1;
	}

	void draw() {
		if (*px1 < -1 || *px2 < -1 || *py1 < -1 || *py2 < -1 || *px1 > WIDTH || *px2 > WIDTH || *py1 > HEIGHT || *py2 > HEIGHT) {
			return;
		}

		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			if (*px1 <= *px2)
				x1 = *px1, x2 = *px2;
			else
				x1 = *px2, x2 = *px1;

			if (*py1 <= *py2)
				y1 = *py1, y2 = *py2;
			else
				y1 = *py2, y2 = *py1;

			if (isDrawing) {
				xA = x2;
				xB = x1;
				yA = y1;
				yB = y2;
			}

			Shape* l = new Line(&x1, &xB, &y1, &yB);
			l->setID(shapeID);
			l->draw();

			Shape* r = new Line(&xA, &x2, &yA, &y2);
			r->setID(shapeID);
			r->draw();

			Shape* t = new Line(&x1, &xA, &y1, &yA);
			t->setID(shapeID);
			t->draw();

			Shape* b = new Line(&xB, &x2, &yB, &y2);
			b->setID(shapeID);
			b->draw();

			delete l, r, t, b;
		}
	}

	void redraw() {
		Shape* l = new Line(&x1, &xB, &y1, &yB);
		l->setID(shapeID);
		l->draw();

		Shape* r = new Line(&xA, &x2, &yA, &y2);
		r->setID(shapeID);
		r->draw();

		Shape* t = new Line(&x1, &xA, &y1, &yA);
		t->setID(shapeID);
		t->draw();

		Shape* b = new Line(&xB, &x2, &yB, &y2);
		b->setID(shapeID);
		b->draw();

		delete l, r, t, b;
	}

	void clear() {
		Shape* l = new Line(&x1, &xB, &y1, &yB);
		l->setID(shapeID);
		l->clear();

		Shape* r = new Line(&xA, &x2, &yA, &y2);
		r->setID(shapeID);
		r->clear();

		Shape* t = new Line(&x1, &xA, &y1, &yA);
		t->setID(shapeID);
		t->clear();

		Shape* b = new Line(&xB, &x2, &yB, &y2);
		b->setID(shapeID);
		b->clear();

		delete l, r, t, b;
	}

	void drawLastStroke() {
		;
	}

	void rotate(int d) {
		clear();

		degree += d;

		float alpha = d * PI / 180;

		float cX = (x1 + x2 + xA + xB) / 4;
		float cY = (y1 + y2 + yA + yB) / 4;

		x1 = cos(alpha) * (x1 - cX) - sin(alpha) * (y1 - cY) + cX;
		x2 = cos(alpha) * (x2 - cX) - sin(alpha) * (y2 - cY) + cX;
		xA = cos(alpha) * (xA - cX) - sin(alpha) * (yA - cY) + cX;
		xB = cos(alpha) * (xB - cX) - sin(alpha) * (yB - cY) + cX;
						  			   
		y1 = sin(alpha) * (x1 - cX) + cos(alpha) * (y1 - cY) + cY;
		y2 = sin(alpha) * (x2 - cX) + cos(alpha) * (y2 - cY) + cY;
		yA = sin(alpha) * (xA - cX) + cos(alpha) * (yA - cY) + cY;
		yB = sin(alpha) * (xB - cX) + cos(alpha) * (yB - cY) + cY;

		this->redraw();
	}

	void rotateNoRender(int d) {

		float alpha = d * PI / 180;

		float cX = (x1 + x2 + xA + xB) / 4;
		float cY = (y1 + y2 + yA + yB) / 4;

		x1 = cos(alpha) * (x1 - cX) - sin(alpha) * (y1 - cY) + cX;
		x2 = cos(alpha) * (x2 - cX) - sin(alpha) * (y2 - cY) + cX;
		xA = cos(alpha) * (xA - cX) - sin(alpha) * (yA - cY) + cX;
		xB = cos(alpha) * (xB - cX) - sin(alpha) * (yB - cY) + cX;

		y1 = sin(alpha) * (x1 - cX) + cos(alpha) * (y1 - cY) + cY;
		y2 = sin(alpha) * (x2 - cX) + cos(alpha) * (y2 - cY) + cY;
		yA = sin(alpha) * (xA - cX) + cos(alpha) * (yA - cY) + cY;
		yB = sin(alpha) * (xB - cX) + cos(alpha) * (yB - cY) + cY;
	}

	void translate(float dx, float dy) {
		clear();

		x1 += dx;
		x2 += dx;
		xA += dx; 
		xB += dx; 
			  
		y1 += dy; 
		y2 += dy; 
		yA += dy; 
		yB += dy; 

		redraw();
	}

	void translateNoRender(float dx, float dy) {
		x1 += dx;
		x2 += dx;
		xA += dx;
		xB += dx;

		y1 += dy;
		y2 += dy;
		yA += dy;
		yB += dy;
	}

	void scale(int d) {
		clear();
		float cX = (x1 + x2 + xA + xB) / 4;
		float cY = (y1 + y2 + yA + yB) / 4;

		x1 = x1 * (1 + d * 0.1);
		x2 = x2 * (1 + d * 0.1);
		xA = xA * (1 + d * 0.1);
		xB = xB * (1 + d * 0.1);
		y1 = y1 * (1 + d * 0.1);
		y2 = y2 * (1 + d * 0.1);
		yA = yA * (1 + d * 0.1);
		yB = yB * (1 + d * 0.1);

		float ccX = (x1 + x2 + xA + xB) / 4;
		float ccY = (y1 + y2 + yA + yB) / 4;

		translateNoRender(- ccX + cX, - ccY + cY);

		redraw();
	}

	void setID(int gID) {
		shapeID = gID;
	}

	int getID() {
		return shapeID;
	}
};

class Circle : public Shape {
private:
	GLfloat cX, cY, radius;

	int shapeID;
public:
	Circle(float* _x1, float* _x2, float* _y1, float* _y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {
		if (*px1 < -1 || *px2 < -1 || *py1 < -1 || *py2 < -1 || *px1 > WIDTH || *px2 > WIDTH || *py1 > HEIGHT || *py2 > HEIGHT) {
			return;
		}

		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			float x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;

			cX = (x1 + x2) / 2;
			cY = (y1 + y2) / 2;
			radius = sqrt((x2 - cX) * (x2 - cX) + (y2 - cY) * (y2 - cY));

			if (cX - radius < -1 || cX + radius > WIDTH || cY - radius < -1 || cY + radius > HEIGHT) {
				return;
			}

			float x = radius, y = 0, error = 0;

			glBegin(GL_POINTS);
			glColor3ub(145, 83, 58);

			while (x >= y) {
				glVertex2i(cX + x, cY + y);
				glVertex2i(cX + y, cY + x);
				glVertex2i(cX - y, cY + x);
				glVertex2i(cX - x, cY + y);
				glVertex2i(cX - x, cY - y);
				glVertex2i(cX - y, cY - x);
				glVertex2i(cX + y, cY - x);
				glVertex2i(cX + x, cY - y);

				myMap[cY + y][cX + x].insert(shapeID);
				myMap[cY + x][cX + y].insert(shapeID);
				myMap[cY + x][cX - y].insert(shapeID);
				myMap[cY + y][cX - x].insert(shapeID);
				myMap[cY - y][cX - x].insert(shapeID);
				myMap[cY - x][cX - y].insert(shapeID);
				myMap[cY - x][cX + y].insert(shapeID);
				myMap[cY - y][cX + x].insert(shapeID);

				if (error <= 0) {
					y = y + 1;
					error = error + 2 * y + 1;
				}
				else {
					x = x - 1;
					error = error - 2 * x + 1;
				}
			}
			glEnd();
		}
	}

	void drawLastStroke() {
		;
	}

	void clear() {
		if (cX - radius < -1 || cX + radius > WIDTH || cY - radius < -1 || cY + radius > HEIGHT) {
			return;
		}

		float x = radius, y = 0, error = 0;

		glBegin(GL_POINTS);
		glColor3ub(255, 255, 255);

		while (x >= y) {
			if (myMap[cY+y][cX+x].size() == 1 && myMap[cY + y][cX + x].count(shapeID) > 0) {
				glVertex2i(cX + x, cY + y);
			}
			myMap[cY + y][cX + x].erase(shapeID);

			if (myMap[cY + x][cX + y].size() == 1 && myMap[cY + x][cX + y].count(shapeID) > 0) {
				glVertex2i(cX + y, cY + x);
			}
			myMap[cY + x][cX + y].erase(shapeID);

			if (myMap[cY + x][cX - y].size() == 1 && myMap[cY + x][cX - y].count(shapeID) > 0) {
				glVertex2i(cX - y, cY + x);
			}
			myMap[cY + x][cX - y].erase(shapeID);

			if (myMap[cY + y][cX - x].size() == 1 && myMap[cY + y][cX - x].count(shapeID) > 0) {
				glVertex2i(cX - x, cY + y);
			}
			myMap[cY + y][cX - x].erase(shapeID);

			if (myMap[cY - y][cX - x].size() == 1 && myMap[cY - y][cX - x].count(shapeID) > 0) {
				glVertex2i(cX - x, cY - y);
			}
			myMap[cY - y][cX - x].erase(shapeID);

			if (myMap[cY - x][cX - y].size() == 1 && myMap[cY - x][cX - y].count(shapeID) > 0) {
				glVertex2i(cX - y, cY - x);
			}
			myMap[cY - x][cX - y].erase(shapeID);

			if (myMap[cY - x][cX + y].size() == 1 && myMap[cY - x][cX + y].count(shapeID) > 0) {
				glVertex2i(cX + y, cY - x);
			}
			myMap[cY - x][cX + y].erase(shapeID);

			if (myMap[cY - y][cX + x].size() == 1 && myMap[cY - y][cX + x].count(shapeID) > 0) {
				glVertex2i(cX + x, cY - y);
			}
			myMap[cY - y][cX + x].erase(shapeID);


			if (error <= 0) {
				y = y + 1;
				error = error + 2 * y + 1;
			}
			else {
				x = x - 1;
				error = error - 2 * x + 1;
			}
		}
		glEnd();
	}

	void rotate(int d) {
		;
	}

	void redraw() {
		if (cX - radius < -1 || cX + radius > WIDTH || cY - radius < -1 || cY + radius > HEIGHT) {
			return;
		}
		
		float x = radius, y = 0, error = 0;

		glBegin(GL_POINTS);
		glColor3ub(145, 83, 58);

		while (x >= y) {

			glVertex2i(cX + x, cY + y);
			glVertex2i(cX + y, cY + x);
			glVertex2i(cX - y, cY + x);
			glVertex2i(cX - x, cY + y);
			glVertex2i(cX - x, cY - y);
			glVertex2i(cX - y, cY - x);
			glVertex2i(cX + y, cY - x);
			glVertex2i(cX + x, cY - y);

			myMap[cY + y][cX + x].insert(shapeID);
			myMap[cY + x][cX + y].insert(shapeID);
			myMap[cY + x][cX - y].insert(shapeID);
			myMap[cY + y][cX - x].insert(shapeID);
			myMap[cY - y][cX - x].insert(shapeID);
			myMap[cY - x][cX - y].insert(shapeID);
			myMap[cY - x][cX + y].insert(shapeID);
			myMap[cY - y][cX + x].insert(shapeID);

			if (error <= 0) {
				y = y + 1;
				error = error + 2 * y + 1;
			}
			else {
				x = x - 1;
				error = error - 2 * x + 1;
			}
		}
		glEnd();
			
	}

	void translate(float dx, float dy) {
		clear();
		cX += dx;
		cY += dy;
		redraw();
	}

	void scale(int d) {
		clear();
		radius = radius + d * radius * 0.1;
		redraw();
	}

	void setID(int gID) {
		shapeID = gID;
	}

	int getID() {
		return shapeID;
	}
};

class Ellip : public Shape {
private:
	float cX, cY, a, b, degree;
	int x1, x2, y1, y2;
	int shapeID;
public:
	Ellip(float* _x1, float* _x2, float* _y1, float* _y2) : Shape(_x1, _x2, _y1, _y2) {
		degree = 0;
	}

	void draw() {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			if (*px2 < *px1) {
				float* t = px1;
				px1 = px2;
				px2 = t;
			}
			if (*py2 < *py1) {
				float* t = py1;
				py1 = py2;
				py2 = t;
			}				

			float x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;

			cX = (x1 + x2) / 2;
			cY = (y1 + y2) / 2;

			if (isDrawing) {
				a = (x2 - cX);
				b = (y2 - cY);
			}

			glBegin(GL_POINTS);
			glColor3ub(145, 83, 58);

			float alpha = 0;

			int x, y;

			for (float theta = 0; theta < 2 * PI; theta += 0.005) {
				x = cX + a * cos(theta) * cos(alpha) - b * sin(theta) * sin(alpha);
				y = cY + a * cos(theta) * sin(alpha) + b * sin(theta) * cos(alpha);

				myMap[y][x].insert(shapeID);

				glVertex2i(x, y);
			}

			glEnd();

		}
	}

	void drawLastStroke() {
		;
	}

	void redraw() {
		if (cX - a < -1 || cX + a > WIDTH || cY - b < -1 || cY + b > HEIGHT) {
			return;
		}

		glBegin(GL_POINTS);
		glColor3ub(145, 83, 58);

		float alpha = degree * PI / 180;

		int x, y;

		for (float theta = 0; theta < 2 * PI; theta += 0.005) {
			x = cX + a * cos(theta) * cos(alpha) - b * sin(theta) * sin(alpha);
			y = cY + a * cos(theta) * sin(alpha) + b * sin(theta) * cos(alpha);

			myMap[y][x].insert(shapeID);

			glVertex2i(x, y);
		}

		glEnd();
	}

	void clear() {
		glBegin(GL_POINTS);
		glColor3ub(255, 255, 255);

		float alpha = degree * PI / 180;

		int x, y;

		for (float theta = 0; theta < 2 * PI; theta += 0.005) {
			x = cX + a * cos(theta) * cos(alpha) - b * sin(theta) * sin(alpha);
			y = cY + a * cos(theta) * sin(alpha) + b * sin(theta) * cos(alpha);

			if (myMap[y][x].size() == 1 && myMap[y][x].count(shapeID) > 0) {
				glVertex2i(x, y);
			}

			myMap[y][x].erase(shapeID);
		}

		glEnd();
	}

	void rotate(int d) {
		clear();

		degree += d;
		float alpha = degree * PI / 180;

		redraw();
	}

	void translate(float dx, float dy) {
		clear();

		cX += dx;
		cY += dy;

		redraw();
	}

	void scale(int d) {
		clear();

		a *= (1 + (d) * 0.1);
		b *= (1 + (d) * 0.1);

		redraw();
	}

	void setID(int gID) {
		shapeID = gID;
	}

	int getID() {
		return shapeID;
	}
};

class Polygonn : public Shape {
private:
	float sX, sY, mX, mY, eX, eY, cX, cY;
	int shapeID;
	std::vector<float> vertices;
public:

	Polygonn(float* _x1, float* _x2, float* _y1, float* _y2) : Shape(_x1, _x2, _y1, _y2) {
		mX = -1;
		mY = -1;
	}

	void draw() {
		if (*px1 < -1 || *px2 < -1 || *py1 < -1 || *py2 < -1 || *px1 > WIDTH || *px2 > WIDTH || *py1 > HEIGHT || *py2 > HEIGHT) {
			return;
		}

		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			if (mX == -1) {
				mX = *px1;
				sX = mX;
				vertices.push_back(sX);
			}
			if (mY == -1) {
				mY = *py1;
				sY = mY;
				vertices.push_back(sY);
			}

			eX = *px2, eY = *py2;
			
			Shape * l = new Line(&mX, &eX, &mY, &eY);
			if (eX != vertices[vertices.size() - 2]) vertices.push_back(eX);
			if (eY != vertices[vertices.size() - 1]) vertices.push_back(eY);
			
			l->setID(shapeID);
			l->draw();
			delete l;
			glEnd();
			mX = eX;
			mY = eY;
		}
	}

	void drawLastStroke() {
		vertices.push_back(sX);
		vertices.push_back(sY);

		Shape* l = new Line(&sX, &eX, &sY, &eY);

		l->setID(shapeID);
		l->draw();
		delete l;

		cX = 0;
		cY = 0;
		for (int i = 0; i < vertices.size() - 1; i+=2) {
			cX += vertices[i];
			cY += vertices[i + 1];
		}
		cX = cX / vertices.size() * 2;
		cY = cY / vertices.size() * 2;
	}

	void clear() {
		for (int i = 0; i < vertices.size() - 2; i += 2) {
			Shape* l = new Line(&vertices[i], &vertices[i + 2], &vertices[i + 1], &vertices[i + 3]);
			l->setID(shapeID);
			l->clear();
			delete l;
		}
	}

	void redraw() {
		for (int i = 0; i < vertices.size() - 2; i += 2) {
			Shape* l = new Line(&vertices[i], &vertices[i + 2], &vertices[i + 1], &vertices[i + 3]);
			l->setID(shapeID);
			l->draw();
			delete l;
		}
	}

	void rotate(int d) {

		clear();

		float alpha = d * PI / 180;
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			vertices[i] = cos(alpha) * (vertices[i] - cX) - sin(alpha) * (vertices[i + 1] - cY) + cX;
			vertices[i + 1] = sin(alpha) * (vertices[i] - cX) + cos(alpha) * (vertices[i + 1] - cY) + cY;
		}

		redraw();
	}

	void translate(float dx, float dy) {
		clear();

		for (int i = 0; i < vertices.size() - 1; i+=2) {
			vertices[i] += dx;
			vertices[i + 1] += dy;
		}

		cX = 0;
		cY = 0;
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			cX += vertices[i];
			cY += vertices[i + 1];
		}
		cX = cX / vertices.size() * 2;
		cY = cY / vertices.size() * 2;

		redraw();
	}

	void translateNoRender(float dx, float dy) {
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			vertices[i] += dx;
			vertices[i + 1] += dy;
		}
	}

	void scale(int d) {
		clear();

		cX = 0;
		cY = 0;
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			cX += vertices[i];
			cY += vertices[i + 1];
		}
		cX = cX / vertices.size() * 2;
		cY = cY / vertices.size() * 2;

		for (int i = 0; i < vertices.size() - 1; i += 2) {
			vertices[i] *= (1 + (d) * 0.1);
			vertices[i + 1] *= (1 + (d) * 0.1);
		}

		float ccX = 0;
		float ccY = 0;

		ccX = 0;
		ccY = 0;
		for (int i = 0; i < vertices.size() - 1; i += 2) {
			ccX += vertices[i];
			ccY += vertices[i + 1];
		}
		ccX = ccX / vertices.size() * 2;
		ccY = ccY / vertices.size() * 2;

		translateNoRender(-ccX + cX, -ccY + cY);

		redraw();
	}

	void setID(int gID) {
		shapeID = gID;
	}

	int getID() {
		return shapeID;
	}
};

#endif // !_SHAPE_