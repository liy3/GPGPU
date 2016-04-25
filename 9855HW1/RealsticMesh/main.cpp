#include <iostream>
#include <memory>
#include <gl/glew.h>
#include <gl/freeglut.h>

#include <MouseCamera.h>
#include <Mesh.h>
#include <Shader.h>
#include <Texture.h>

const char* WINDOW_TITLE = "[CSCI-4800/5800] Shader and GPU Programming";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
GLint g_glutWindowIdentifier;

std::shared_ptr<MouseCameraf> camera = nullptr;
std::shared_ptr<Mesh> mesh1 = nullptr;
std::shared_ptr<Mesh> mesh2 = nullptr;
std::shared_ptr<Mesh> mesh3 = nullptr;
std::shared_ptr<Mesh> mesh4 = nullptr;
std::shared_ptr<Texture> texture = nullptr;

float phi = 0.001f;
float r = 10.0f;
float x, y;

void g_init() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glewInit();

    camera = std::make_shared<MouseCameraf>(3.0f);
    mesh1 = std::make_shared<Mesh>();
	mesh2 = std::make_shared<Mesh>();
	mesh3 = std::make_shared<Mesh>();
	mesh4 = std::make_shared<Mesh>();


	/* Loading first object, shader and textures */
	mesh1->load("models/Teapot.obj");
	mesh1->loadShader("shaders/TextureShader1.vert", "shaders/TextureShader1.frag");
	mesh1->setDiffuseTexture("textures/cleanwood_diffuse.png");
	mesh1->setNormalTexture("textures/cleanwood_normal.png");
	mesh1->setSpecularTexture("textures/cleanwood_specular.png");

	/* Loading second object, shader and textures */
	mesh2->load("models/sphere.obj");
	mesh2->loadShader("shaders/TextureShader2.vert", "shaders/TextureShader2.frag");
	mesh2->setDiffuseTexture("textures/jupiter_diffuse.png");
	mesh2->setNormalTexture("textures/jupiter_normal.png");
	mesh2->setSpecularTexture("textures/jupiter_specular.png");

	/* Loading third object, shader and textures */
	mesh3->load("models/torus.obj");
	mesh3->loadShader("shaders/TextureShader3.vert", "shaders/TextureShader3.frag");
	mesh3->setDiffuseTexture("textures/brick_diffuse.png");
	mesh3->setNormalTexture("textures/brick_normal.png");
	mesh3->setSpecularTexture("textures/brick_specular.png");

	/* Loading fourth object, shader and textures */
	mesh4->load("models/minionMike.obj");
	mesh4->loadShader("shaders/TextureShader4.vert", "shaders/TextureShader4.frag");
	mesh4->setDiffuseTexture("textures/rustymetal_diffuse.png");
	mesh4->setNormalTexture("textures/rustymetal_normal.png");
	mesh4->setSpecularTexture("textures/rustymetal_specular.png");

    camera->setPosition(18.0f, 1.5707f, 1.570f * 0.7f);
}

void g_glutReshapeFunc(int width, int height) {
	glViewport(0, 0, width, height);
    camera->setPerspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
	glutPostRedisplay();
}

void g_glutDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    x = r * std::cos(phi);
    y = r * std::sin(phi);

	mesh1->beginRender();
	mesh1->getShader()->uniformMatrix("projectionMatrix", camera->getProjectionMatrix());
	mesh1->getShader()->uniformMatrix("modelViewMatrix", camera->getViewMatrix());
	mesh1->getShader()->uniformMatrix("normalMatrix", Matrix4f::Transpose(camera->getViewMatrix().toInverse()));
	mesh1->getShader()->uniformVector("lightPosition", Vector3f(x, 5.0f, y));
	mesh1->endRender();

	mesh2->beginRender();
	mesh2->getShader()->uniformMatrix("projectionMatrix", camera->getProjectionMatrix());
	mesh2->getShader()->uniformMatrix("modelViewMatrix", camera->getViewMatrix());
	mesh2->getShader()->uniformMatrix("normalMatrix", Matrix4f::Transpose(camera->getViewMatrix().toInverse()));
	mesh2->getShader()->uniformVector("lightPosition", Vector3f(x, 5.0f, y));
	mesh2->endRender();

	mesh3->beginRender();
	mesh3->getShader()->uniformMatrix("projectionMatrix", camera->getProjectionMatrix());
	mesh3->getShader()->uniformMatrix("modelViewMatrix", camera->getViewMatrix());
	mesh3->getShader()->uniformMatrix("normalMatrix", Matrix4f::Transpose(camera->getViewMatrix().toInverse()));
	mesh3->getShader()->uniformVector("lightPosition", Vector3f(x, 5.0f, y));
	mesh3->endRender();

	mesh4->beginRender();
	mesh4->getShader()->uniformMatrix("projectionMatrix", camera->getProjectionMatrix());
	mesh4->getShader()->uniformMatrix("modelViewMatrix", camera->getViewMatrix());
	mesh4->getShader()->uniformMatrix("normalMatrix", Matrix4f::Transpose(camera->getViewMatrix().toInverse()));
	mesh4->getShader()->uniformVector("lightPosition", Vector3f(x, 5.0f, y));
	mesh4->endRender();

    glFlush();
}

void g_glutMotionFunc(int x, int y) {
	camera->onMouseMove(x, y);
	glutPostRedisplay();
}

void g_glutMouseFunc(int button, int state, int x, int y) {
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) camera->onMouseButton(LB_DOWN, x, y);
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) camera->onMouseButton(RB_DOWN, x, y);
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) camera->onMouseButton(LB_UP, x, y);
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_UP ) camera->onMouseButton(RB_UP, x, y);
}

/* 0.25 degrees every frame = 15 degree rotation per second */
void g_glutIdleFunc() {
    phi += 0.004363323;
    glutPostRedisplay();
    Sleep(16);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	g_glutWindowIdentifier = glutCreateWindow(WINDOW_TITLE);

	glutDisplayFunc(g_glutDisplayFunc);
	glutReshapeFunc(g_glutReshapeFunc);
    glutMotionFunc(g_glutMotionFunc);
    glutMouseFunc(g_glutMouseFunc);
    glutIdleFunc(g_glutIdleFunc);

	g_init();

	glutMainLoop();
	return 0;
}

