//#include "Game.h"
//
//oux::Game::Game()
//{
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    window = glfwCreateWindow(screen_width, screen_height, window_name, NULL, NULL);
//    if (window == NULL)
//        fprintf(stderr, "Failed to initialize GLFW Window!\n");
//
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1); // Enable vsync
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // Initialize OpenGL loader
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//    bool err = gl3wInit() != 0;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
//    bool err = glewInit() != GLEW_OK;
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//    bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//#endif
//    if (err)
//    {
//        fprintf(stderr, "Failed to initialize (GLAD) OpenGL loader!\n");
//    }
//
//    // Enable depth test
//    glEnable(GL_DEPTH_TEST);
//
//
//}