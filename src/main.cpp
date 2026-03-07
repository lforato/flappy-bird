#include <cstdlib>
#include <fstream>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

// clang-format off
float vertices[] = {
   0.0f, 0.5f, // top
  -0.5f, -0.5f, // left
   0.5f, -0.5f, // right
};
// clang-format on 

std::string loadFile(std::string filepath) {
  std::fstream file(filepath);

  if (!file.is_open()) 
  {
    std::cout << "File failed to open" << '\n';
    exit(EXIT_FAILURE);
  }
  std::string result;
  std::string line;

  while(std::getline(file, line))
  {
    result += line + '\n';
  }

  return result;
}

unsigned int compileShader(std::string source, GLenum type) {
  const char* str = source.c_str();

  unsigned int shader = glCreateShader(type);
  glShaderSource(shader, 1, &str, 0);
  glCompileShader(shader);

  int success;
  char log[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    const char* shaderType = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
    glGetShaderInfoLog(shader, 512, nullptr, log);
    std::cerr << "failed to compile shader::" << shaderType << ":: " << log << '\n';
    exit(EXIT_FAILURE);
  }

  return shader;
}

unsigned int linkProgram(std::string vertexPath, std::string fragmentPath) {
  unsigned int program = glCreateProgram(); 
  unsigned int vertex = compileShader(vertexPath, GL_VERTEX_SHADER);
  unsigned int fragment = compileShader(fragmentPath, GL_FRAGMENT_SHADER);

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  int success;
  char log[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(program, 512, nullptr, log);
    std::cerr << "failed to link program::" << log << '\n';
    exit(EXIT_FAILURE);
  }

  glDeleteShader(vertex); 
  glDeleteShader(fragment);

  return program;
}

int main()
{
  // --- init GLFW ---
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // --- create window ---
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flappy Bird", NULL, NULL);
  if (window == nullptr)
  {
    std::cout << "FAILED TO CREATE WINDOW" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // --- creating the context for opengl functions ---
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  // Vertex Arrays
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Vertex Buffer
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  std::string vertexShader = loadFile("../src/res/shader/vertex.glsl");
  std::string fragmentShader = loadFile("../src/res/shader/fragment.glsl");
  unsigned int program = linkProgram(vertexShader, fragmentShader);

  // --- rendering ---
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glUseProgram(program);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
