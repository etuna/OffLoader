
#include "Angel.h"
#include "OffModel.h"


using namespace std;

//-------------
const float ANGLE = 45.f;
const float FOV = 70.f;
const float NCP = 0.05f;
const float FCP = 50.f;

OffModel* off_object;

float angle;
float spin;



bool init() {

	off_object = new OffModel();
	if (!off_object->load("sphere.off"))
	{
		std::cout << "error" << std::endl;
		return false;
	}


	angle = 0; spin = 0.1;	//5 degrees
	glEnable(GL_DEPTH_TEST);

	return true;

}


void draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	vec3 _v1, _v2, _v3;
	glTranslatef(0, 0, -1);
	glRotatef(angle += spin, 0, 1, 0); if (++angle > 360) angle -= 360;
	glScalef(off_object->scale, off_object->scale, off_object->scale);
	glTranslatef(-off_object->center.x, -off_object->center.y, -off_object->center.z);
	for (size_t k = 0; k < off_object->num_triangles; k++)
	{

		_v1 = off_object->points[(unsigned int)off_object->triangles[k][v1]];
		_v2 = off_object->points[(unsigned int)off_object->triangles[k][v2]];
		_v3 = off_object->points[(unsigned int)off_object->triangles[k][v3]];

		glBegin(GL_TRIANGLES);
		glColor3f(_v1.x, _v1.y, _v1.z);
		glVertex3f(_v1.x, _v1.y, _v1.z);
		glColor3f(_v2.x, _v2.y, _v2.z);
		glVertex3f(_v2.x, _v2.y, _v2.z);
		glColor3f(_v3.x, _v3.y, _v3.z);
		glVertex3f(_v3.x, _v3.y, _v3.z);
		glEnd();
	}
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (height == 0) ? 1 : (GLfloat)width / (GLfloat)height;
	gluPerspective(FOV, ratio, NCP, FCP);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
enum { Xax = 0, Yax = 1, Zax = 2, NumAx = 3 };
int      Axis = Xax;
GLfloat  Theta[NumAx] = { 0.0, 0.0, 0.0 };
void
idle(void)
{
	Theta[Axis] += 0.01;

	if (Theta[Axis] > 360.0) {
		Theta[Axis] -= 360.0;
	}

	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	int id = glutCreateWindow("OffLoader");
	if (!init())
	{
		glutDestroyWindow(id);
		return EXIT_FAILURE;
	}
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return EXIT_SUCCESS;
}



