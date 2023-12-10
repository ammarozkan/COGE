// GL/glew.h
// GLFW/glfw3.h
// is included.

{
	LOG("OPENGL INITIALIZATION");
	GLFWwindow* window;
	if(!glfwInit()) return nullptr;

	window = glfwCreateWindow(WIDTH,HEIGHT,"COGE",NULL,NULL);

	if(!window)
	{
		WARN("GLFW WINDOW CREATION FAILED.");
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) 
	{
		WARN("GLEW IS NOT OK:"); PRINT(glewGetString(err));
		//return err;
		return nullptr;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	return window;
}