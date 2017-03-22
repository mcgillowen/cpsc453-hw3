

#include "Loader.hpp"
#include "Program.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"

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

glm::mat4 rotation = glm::mat4(1.0f);
glm::mat4 scaling = glm::mat4(1.0f);
glm::mat4 translation = glm::mat4(1.0f);
float scalar = 1.0f;

int width;
int height;

void computeBoundingBox(Loader l) {
  glm::vec3 min = glm::vec3(l.minX, l.minY, l.minZ);
  glm::vec3 max = glm::vec3(l.maxX, l.maxY, l.maxZ);

  float radius = glm::length(max - min) * 0.5f;
  scaling = glm::scale(glm::mat4 (1.0f), glm::vec3 (0.95f / radius));

  glm::vec3 center = (max + min) * 0.5f;

  translation = glm::translate(glm::mat4(1.0f), -center);

}

VertexArray* va;
Texture tex;

void render(Program& program, VertexArray& va, Texture& tex)
{
	// enable depth test and clear screen to a dark grey colour
	glEnable( GL_DEPTH_TEST );
	glDepthFunc(GL_LESS);
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program.id);

	GLuint m_handle = glGetUniformLocation(program.id, "M");
	GLuint v_handle = glGetUniformLocation(program.id, "V");
	GLuint p_handle = glGetUniformLocation(program.id, "P");

	//Scale based on input
  scaling = glm::scale (glm::mat4(1.0f), glm::vec3 (scalar)) * scaling;

  //Create and pass model view matrix
  glm::mat4 modelView = glm::lookAt (glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  modelView *= rotation * scaling * translation;

  //Create and pass projection matrix
  glm::mat4 proj = glm::perspective (45.0f, (float)width / (float)height, 0.1f, 100.0f);

	glUniformMatrix4fv(m_handle, 1, GL_FALSE, &modelView[0][0]);
	glUniformMatrix4fv(p_handle, 1, GL_FALSE, &proj[0][0]);

	glBindVertexArray(va.id);
  glBindTexture(tex.target, tex.id);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

  GLsizei count = va.count;
  //cout << count << endl;
	glDrawArrays(GL_TRIANGLES, 0, count);

	glBindVertexArray(0);

	glUseProgram(0);

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
	window = glfwCreateWindow(800, 800, "OBJ Viewer", 0, 0);
	if (!window) {
		cout << "Program failed to create GLFW window, TERMINATING" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window,
    [](GLFWwindow* window, int key, int scancode, int action, int mode){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
          glfwSetWindowShouldClose(window, GL_TRUE);

        if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (1.0f, 0.0f, 0.0f)) ;
        if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (-1.0f, 0.0f, 0.0f));

        if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (0.0f, 1.0f, 0.0f));
        if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (0.0f, -1.0f, 0.0f));

        if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (0.0f, 0.0f, 1.0f));
        if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT))
          rotation = rotation * glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3 (0.0f, 0.0f, -1.0f));
  });

  glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
      scalar = 1.1f;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
      scalar = 1.0f;

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
      scalar = 1.0f / 1.1f;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
      scalar = 1.0f;
  });

  glfwGetFramebufferSize(window, &width, &height);


  Program p("vertex.glsl","fragment.glsl");
  Loader l;
  if (argc > 1) {
    va = l.loadObjFile(argv[1]);
    tex = Texture(argv[2], p);
  } else {
    va = l.loadObjFile("buddha2/buddha2.obj");
    //va = l.loadObjFile("test.obj");
    tex = Texture("buddha2/buddha2-atlas.jpg", p);
  }

  computeBoundingBox(l);

	// run an event-triggered main loop
	while (!glfwWindowShouldClose(window)){
    // render
		render(p, (*va), tex);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	cout << "The End" << endl;
	return 0;
}
