#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <trying-into-opengl.h>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0"; // TODO aren't they null-terminated by default?

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0"; // TODO aren't they null-terminated by default?

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__ // TODO do I even need this?
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        (void) fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate(); // TODO maybe not needed if completely shutting down
        exit(1);
    }
    glfwMakeContextCurrent(window);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     fprintf(stderr, "%s\n", "Failed to initialize GLAD");
    //     return -1;
    // }
    glfwSetKeyCallback(window, key_callback);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        (void) fprintf(stderr, "Failed to initialize OpenGL context\n");
        glfwTerminate(); // TODO maybe not needed if completely shutting down
        exit(1);
    }

    // Successfully loaded OpenGL
    printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5F, -0.5F, 0.0F,
         0.5F, -0.5F, 0.0F,
         0.0F,  0.5F, 0.0F
    };

    float quad_vertices[] = {
         0.5F,  0.5F, 0.0F,  // top right
         0.5F, -0.5F, 0.0F,  // bottom right
        -0.5F, -0.5F, 0.0F,  // bottom left
        -0.5F,  0.5F, 0.0F   // top left
    };

    GLuint indices[] = {
        // 0, 1, 3,   // first triangle
        // 1, 2, 3    // second triangle
        0, 1, 1, 2, 2, 3, 3, 0
    };

    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // TODO does this do anything?
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // TODO where do I put these?
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(posAttrib);

    // TODO should I also do this in the render loop?
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window))
    {
        // Clear the colorbuffer
        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        // glUseProgram(shaderProgram);
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers
        glfwSwapBuffers(window);

        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        // glfwPollEvents();
        glfwWaitEvents();
    }

    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    exit(0);
}
