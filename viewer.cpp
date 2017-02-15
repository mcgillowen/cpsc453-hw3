

#include "Loader.hpp"
#include "Program.hpp"
#include "IndexedVertexArray.hpp"

#include <cmath>

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

float pitchAngle = 0.0f;
glm::vec3 pitchAxis = glm::vec3(1,0,0);
glm::mat4 pitchMatrix = glm::rotate(pitchAngle, pitchAxis);

float rollAngle = 0.0f;
glm::vec3 rollAxis = glm::vec3(0,0,1);
glm::mat4 rollMatrix = glm::rotate(rollAngle, rollAxis);

float yawAngle = 0.0f;
glm::vec3 yawAxis = glm::vec3(0,1,0);
glm::mat4 yawMatrix = glm::rotate(yawAngle, yawAxis);

float xValue = 0.0;
float yValue = 0.0;
float zValue = 0.0;

void render(Program& program, IndexedVertexArray& va)
{
	// enable depth test and clear screen to a dark grey colour
	glEnable( GL_DEPTH_TEST );
	glDepthFunc(GL_LESS);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program.id);

	GLuint m_handle = glGetUniformLocation(program.id, "M");
	GLuint v_handle = glGetUniformLocation(program.id, "V");
	GLuint p_handle = glGetUniformLocation(program.id, "P");

	// modeling matrix to rotate. Rotation angle is specified in degrees
  glm::mat4 rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;
  glm::mat4 translationMatrix = glm::translate(glm::vec3(xValue, yValue, zValue));
  glm::mat4 inverseTranslation = glm::inverse(translationMatrix);
	glm::mat4 model = translationMatrix * rotationMatrix;
	glm::mat4 view = glm::lookAt(
	  glm::vec3(0,0,5), // Camera is here in world Space
	  glm::vec3(0,0,0), // and looks at the origin
	  glm::vec3(0,1,0)  // Up direction is the y axis
	);

	// specify a perspective projection. Parameters are
	// fov in degrees, aspect ratio, distance to near plane, distance to far plane
	glm::mat4 projection = glm::perspective(45.f, 1.f, 1.f, 10.f);

	glUniformMatrix4fv(m_handle, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(v_handle, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(p_handle, 1, GL_FALSE, &projection[0][0]);

	glBindVertexArray(va.id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, va.elementbuffer);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawElements(GL_TRIANGLES, va.indices.size(), GL_UNSIGNED_INT, (void*)0);


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

}

void pitchUp() {


  pitchAngle += 1.0f;
  pitchMatrix = glm::rotate(pitchAngle, pitchAxis);

}

void pitchDown() {

  pitchAngle -= 1.0f;
  pitchMatrix = glm::rotate(pitchAngle, pitchAxis);

}

void rollClockwise() {

  rollAngle -= 1.0f;
  rollMatrix = glm::rotate(rollAngle, rollAxis);

}

void rollCounterClockwise() {

  rollAngle += 1.0f;
  rollMatrix = glm::rotate(rollAngle, rollAxis);

}

void yawRight() {

  yawAngle += 1.0f;
  yawMatrix = glm::rotate(yawAngle, yawAxis);

}

void yawLeft() {

  yawAngle -= 1.0f;
  yawMatrix = glm::rotate(yawAngle, yawAxis);

}

void increaseX() {
  xValue += 1.0f;
}
void decreaseX() {
  xValue -= 1.0f;
}

void increaseY() {
  yValue += 1.0f;
}
void decreaseY() {
  yValue -= 1.0f;
}

void increaseZ() {
  zValue += 1.0f;
}
void decreaseZ() {
  zValue -= 1.0f;
}

int main(int argc, char *argv[])
{
	// initialize the GLFW windowing system
	if (!glfwInit()) {
		cout << "ERROR: GLFW failed to initialize, TERMINATING" << endl;
		return -1;
	}
	glfwSetErrorCallback([](int error, const char* description){
    cout << "GLFW ERROR " << error << ":" << endl;
    cout << description << endl;
  });

  // Use OpenGL 4.1
	GLFWwindow *window = 0;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(512, 512, "OBJ Viewer", 0, 0);
	if (!window) {
		cout << "Program failed to create GLFW window, TERMINATING" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window,
    [](GLFWwindow* window, int key, int scancode, int action, int mode){
        //Rotation controls
        if (key == GLFW_KEY_W && action == GLFW_PRESS) {
          pitchUp();
        }
        if (key == GLFW_KEY_S && action == GLFW_PRESS) {
          pitchDown();
        }
        if (key == GLFW_KEY_D && action == GLFW_PRESS) {
          rollClockwise();
        }
        if (key == GLFW_KEY_A && action == GLFW_PRESS) {
          rollCounterClockwise();
        }
        if (key == GLFW_KEY_E && action == GLFW_PRESS) {
          yawRight();
        }
        if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
          yawLeft();
        }
        //Translation controls
        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
          increaseZ();
        }
        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
          decreaseZ();
        }
        if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
          decreaseX();
        }
        if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
          increaseX();
        }
        if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS) {
          increaseY();
        }
        if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS) {
          decreaseY();
        }

    });
  	Program p("vertex.glsl","fragment.glsl");
  	IndexedVertexArray* va = Loader::loadObjFile("buddha.obj");

	cout << "Finished reading" << endl;

	// run an event-triggered main loop
	while (!glfwWindowShouldClose(window))
	{
    // render
		render(p, (*va));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	cout << "The End" << endl;
	return 0;
}
