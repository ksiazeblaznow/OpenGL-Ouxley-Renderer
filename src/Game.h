//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//#include <stdio.h>
//
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//#include <GL/gl3w.h>    // Initialize with gl3wInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//#include <GL/glew.h>    // Initialize with glewInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//#include <glad/glad.h>  // Initialize with gladLoadGL()
//#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#endif
//
//#include <GLFW/glfw3.h>
//
//#include "Shader.h"
//#include "Mesh.h"
//#include "Model.h"
//#include "Camera.h"
//#include "GameObject.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//static void glfw_error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//namespace oux {
//    class Game
//    {
//    public:
//        float deltaTime = 0.0f;	// time between current frame and last frame
//        float lastFrame = 0.0f;
//
//        const char* glsl_version = "#version 430";
//        const unsigned int screen_width = 1280;
//        const unsigned int screen_height = 720;
//        const char* window_name = "OUXLEY OpenGL Renderer";
//
//        GLFWwindow* window;
//        //Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//        float lastX = screen_width / 2.0f;
//        float lastY = screen_height / 2.0f;
//        bool firstMouse = true;
//
//        Game();
//    };
//}
