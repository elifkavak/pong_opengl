#include <GL/freeglut_std.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>

#define WINDOW_W 800
#define WINDOW_H 500

static GLfloat screenLeft = -49.5;
static GLfloat screenRight = 49.5;
static const int FPS = 60;
static GLfloat stick1Position = 0.0;
static GLfloat stick2Position = 0.0;
static GLfloat stickThick = 1.0;
static GLfloat stickSize = 15;
static GLfloat moveXFactor = 0.2;
static GLfloat moveYFactor = 0.1;
int scr = 0;
int scr2 = 0;

int ball_size = 8;
int ball_speed = 1;

bool gameOver = false;

struct _ball{

	GLfloat radius = 1;
	GLfloat X = 0.0;
	GLfloat Y = 0.0;
	float directionX = -1;
	float directionY = 1;

}ball;

std::string int2str(int x) {
	// converts int to string
	std::stringstream ss;
	ss << x;
	return ss.str();
}

void drawText(float x, float y, std::string text) {
	
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, -1.0, 1.0);
}

void draw_circle(float x, float y, float radius) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius * sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1,0.3,0.1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRectf(screenLeft, stick1Position, screenLeft + stickThick, stick1Position + stickSize);
	glRectf(screenRight, stick2Position, screenRight - stickThick , stick2Position + stickSize);
	drawText(-25, 25 , "Player 1 : " + int2str(scr) );
	drawText(10, 25, "Player 2 : " + int2str(scr2));
	draw_circle(ball.X, ball.Y, ball.radius);
	glFlush();
	glutSwapBuffers();
	if (gameOver) {
		if (scr > scr2) {
			MessageBox(NULL, L"Player 1 win.", L"Game Over!", 0);
			exit(0);
		}
		else if (scr2>scr){
			MessageBox(NULL, L"Player 1 win.", L"Game Over!", 0);
			exit(0);
		}
		else {
			MessageBox(NULL, L"The players finished in a draw.", L"Game Over!", 0);
			exit(0);
		}
	}
}
void vec2_norm(float& a, float& b) {
	// sets a vectors length to 1 (which means that x + y == 1)
	float length = sqrt((a * a) + (b *b));
	if (length != 0.0f) {
		length = 1.0f / length;
		a *= length;
		b *= length;
	}
}

void timer(int v)
{
	glutPostRedisplay();

	ball.X += ball.directionX * ball_speed;
	ball.Y += ball.directionY * ball_speed;
	/*if (ball.X < - 47.5 || ball.X > 47.5) {
		ball.directionX = ball.directionX * -1;
	}*/
	if (ball.X < screenLeft + stickThick 
		&& ball.Y < stick1Position + stickSize && ball.Y > stick1Position) {
		ball.directionX = ball.directionX * -1;
		ball.X += ball.directionX * ball_speed;
		scr++;
	}
	if (ball.X < screenRight && ball.X > screenRight - stickThick
		&& ball.Y < stick2Position + stickSize && ball.Y > stick2Position){
		ball.directionX = ball.directionX * -1;
		ball.X += ball.directionX * ball_speed;
		scr2++;
	}
	

	if (ball.X < -49.5 || ball.X > 49.5) {
		gameOver = true;
	}


	
	if (ball.Y > 29.5 || ball.Y < -29.5)
	{
		ball.directionY = ball.directionY * -1;
	}


	glutTimerFunc(3000 / FPS, timer, v);
} 




void kbSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (stick2Position + stickSize < 31)
		{
			stick2Position = stick2Position + 3;

		}
		break;
	case GLUT_KEY_DOWN:
		if (stick2Position > -31)
		{
			stick2Position = stick2Position - 3;
		}
		break;
	}
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
		if (stick1Position + stickSize < 31)
		{
			stick1Position = stick1Position + 3;
			
		}
		break;
	case 'w':
		if (stick1Position + stickSize < 31)
		{
			stick1Position = stick1Position + 3;
			
		}
		break;
	case 's':
		if (stick1Position > -31)
		{
			stick1Position = stick1Position - 3;
			
		}
		break;
	case 'S':
		if (stick1Position > -31)
		{
			stick1Position = stick1Position - 3;
			
		}
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(260, 140);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("PONG GAME");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutTimerFunc(100, timer, 0);
	glutSpecialFunc(kbSpecial);
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();
}