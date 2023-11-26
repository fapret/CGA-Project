#include <windows.h>

#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <Windows.h> //Para obtener metricas
#include <string>
#include <sstream>
#endif

#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "FreeImage.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>


#include <assimp/ai_assert.h>
#include <assimp/Importer.hpp>

#include "Mesh.h"
#include "mundo.h"

#include "Hierarchy.h"
#include "Entity.h"
#include "CameraComponent.h"

using namespace std;

// global variables - normally would avoid globals, using in this demo
GLuint shaderprogram; // handle for shader program
GLuint vao, vbo[2]; // handles for our VAO and two VBOs
float r = 0;

Hierarchy& hierarchy = Hierarchy::getInstance();
#ifdef USE_IMGUI
int selectedItem = -1;
#endif

std::string cameraName = "MainCamera";
Entity* camara = new Entity(cameraName);
CameraComponent* cameraComponent = new CameraComponent();//Se agrega en el main

#ifdef USE_IMGUI
GLuint framebuffer;
GLuint texture;
bool checkboxValue = false;

// Redirect standard output (stdout) to a string
class StdoutRedirect {
public:
	StdoutRedirect() {
		original_stdout = std::cout.rdbuf();
		std::cout.rdbuf(buffer.rdbuf());
	}

	~StdoutRedirect() {
		// Restore original stdout when the object goes out of scope
		std::cout.rdbuf(original_stdout);
	}

	// Get the content of the redirected stdout
	std::string GetOutput() const {
		return buffer.str();
	}

private:
	std::ostringstream buffer;
	std::streambuf* original_stdout;
};

void initFramebuffer()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create texture to render into
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Attach the texture to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Framebuffer is not complete!" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
}
#endif

// loadFile - loads text file into char* fname
// allocates memory - so need to delete after use
const char* loadFile(char* fname)
{
	int size;
	char* memblock = NULL;

	// file read based on example in cplusplus.com tutorial
	// ios::ate opens file at the end
	ifstream file(fname, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		size = (int)file.tellg(); // get location of file pointer i.e. file size
		memblock = new char[size + 1]; // create buffer with space for null char
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();
		memblock[size] = 0;
		cout << "file " << fname << " loaded" << endl;
	}
	else
	{
		cout << "Unable to open file " << fname << endl;
		// should ideally set a flag or use exception handling
		// so that calling function can decide what to do now
	}
	return memblock;
}


// Something went wrong - print SDL error message and quit
void exitFatalError(char* message)
{
	cout << message << " ";
	cout << SDL_GetError();
	SDL_Quit();
	exit(1);
}



// printShaderError
// Display (hopefully) useful error messages if shader fails to compile or link
void printShaderError(GLint shader)
{
	int maxLength = 0;
	int logLength = 0;
	GLchar* logMessage;

	// Find out how long the error message is
	if (glIsShader(shader))
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	else
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

	if (maxLength > 0) // If message has length > 0
	{
		logMessage = new GLchar[maxLength];
		if (glIsShader(shader))
			glGetProgramInfoLog(shader, maxLength, &logLength, logMessage);
		else
			glGetShaderInfoLog(shader, maxLength, &logLength, logMessage);
		cout << "Shader Info Log:" << endl << logMessage << endl;
		delete[] logMessage;
	}
}


GLuint initShaders(char* vertFile, char* fragFile)
{
	GLuint p, f, v;	// Handles for shader program & vertex and fragment shaders

	v = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader handle
	f = glCreateShader(GL_FRAGMENT_SHADER);	// " fragment shader handle

	const char* vertSource = loadFile(vertFile); // load vertex shader source
	const char* fragSource = loadFile(fragFile);  // load frag shader source

	// Send the shader source to the GPU
	// Strings here are null terminated - a non-zero final parameter can be
	// used to indicate the length of the shader source instead
	glShaderSource(v, 1, &vertSource, 0);
	glShaderSource(f, 1, &fragSource, 0);

	GLint compiled, linked; // return values for checking for compile & link errors

	// compile the vertex shader and test for errors
	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		cout << "Vertex shader not compiled." << endl;
		printShaderError(v);
	}

	// compile the fragment shader and test for errors
	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		cout << "Fragment shader not compiled." << endl;
		printShaderError(f);
	}

	p = glCreateProgram(); 	// create the handle for the shader program
	glAttachShader(p, v); // attach vertex shader to program
	glAttachShader(p, f); // attach fragment shader to program

	glBindAttribLocation(p, 0, "in_Position"); // bind position attribute to location 0
	glBindAttribLocation(p, 1, "in_Color"); // bind color attribute to location 1

	glLinkProgram(p); // link the shader program and test for errors
	glGetProgramiv(p, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		cout << "Program not linked." << endl;
		printShaderError(p);
	}

	glUseProgram(p);  // Make the shader program the current active program

	delete[] vertSource; // Don't forget to free allocated memory
	delete[] fragSource; // We allocated this in the loadFile function...

	return p; // Return the shader program handle
}

void init(SDL_Window* window, SDL_GLContext gl_context)
{
	const GLfloat pyramid[18] = {     // a simple pyramid
		0.0, 0.5, 0.0, // top
		-1.0,  -0.5, 1.0, // front bottom left
		1.0, -0.5, 1.0, // front bottom right
		1.0,  -0.5, -1.0, // back bottom right
		-1.0, -0.5, -1.0, // back bottom left
		-1.0, -0.5, 1.0 }; // front bottom left
	const GLfloat colors[18] = {
		0.0,  0.0,  0.0, // black
		1.0,  0.0,  0.0, // red
		0.0,  1.0,  0.0, // green
		0.0,  0.0,  1.0, // blue
		1.0,  1.0,  0.0,
		1.0,  0.0,  0.0 }; // yellow


	shaderprogram = initShaders("../simple.vert", "../simple.frag"); // Create and start shader program
	glGenVertexArrays(1, &vao); // allocate & assign a Vertex Array Object (VAO)
	glBindVertexArray(vao); // bind VAO as current object
	glGenBuffers(2, vbo); // allocate two Vertex Buffer Objects (VBO)

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // bind first VBO as active buffer object
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), pyramid, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);     // Enable attribute index 0 (position)

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // bind second VBO as active buffer object
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);    // Enable attribute index 1 (color)

	glEnable(GL_DEPTH_TEST); // enable depth testing
	glEnable(GL_CULL_FACE); // enable back face culling - try this and see what happens!

#ifdef USE_IMGUI
	initFramebuffer();

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Setup ImGui for SDL and OpenGL
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 400");

	// Setup ImGui style
	ImGui::StyleColorsDark();
#endif
}


void draw(SDL_Window* window, Mundo * mundo, Vector3** jugador, int vert)
{
#ifdef USE_IMGUI
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
#endif
	glClearColor(1.0, 1.0, 1.0, 1.0); // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window

	// Create perspective projection matrix

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 100.f);
	projection = glm::rotate(projection, glm::radians(cameraComponent->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::rotate(projection, glm::radians(cameraComponent->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	//projection = glm::translate(projection, glm::vec3(cameraX, 0.0f, cameraZ));

	// Create view matrix for the camera
	glm::mat4 view(1.0);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	view = glm::translate(view, glm::vec3(cameraComponent->getX(), 0.0f, cameraComponent->getZ()));

	// Create model matrix for model transformations
	glm::mat4 model(1.0);

	mundo->draw(jugador, vert);



	// pass model as uniform into shader
	int projectionIndex = glGetUniformLocation(shaderprogram, "projection");
	glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projection));
	// pass model as uniform into shader
	int viewIndex = glGetUniformLocation(shaderprogram, "view");
	glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(view));
	// pass model as uniform into shader
	int modelIndex = glGetUniformLocation(shaderprogram, "model");
	glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLE_FAN, 0, 6); // draw the pyramid

	// Swap buffers and present
	//SDL_GL_SwapWindow(window);
#ifdef USE_IMGUI
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}


void cleanup(void)
{
	glUseProgram(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	// could also detach shaders
	glDeleteProgram(shaderprogram);
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, &vao);

	// Cleanup ImGui
#ifdef USE_IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif
}


int main(int argc, char* argv[]) {
	camara->addComponent(cameraComponent);//Agrego componente de camara a la camara
	camara->addComponent(cameraComponent->getTransform());
	hierarchy.addEntity(camara);

	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// Set OpenGL version and profile for SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_Window* window = NULL;
	SDL_GLContext gl_context;


	int vertAmountJugador = 0;
	Vector3** jugador = DoTheImportThing("models/jugador.obj", vertAmountJugador);//mesh.h
	Mundo* mundo = new Mundo(4.0, 0.3, 0.2);


#ifdef USE_IMGUI
	StdoutRedirect stdoutRedirect;
	window = SDL_CreateWindow("Ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
#else
	window = SDL_CreateWindow("Ventana", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 800, SDL_WINDOW_OPENGL);
#endif

	gl_context = SDL_GL_CreateContext(window);
	//disable limit of 60fps
	SDL_GL_SetSwapInterval(0);
	// Check OpenGL properties
	cout << "App Started" << endl;
	gladLoadGLLoader(SDL_GL_GetProcAddress);
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "Version: " << glGetString(GL_VERSION) << endl;

	init(window, gl_context);

	bool running = true; // set running to true
	SDL_Event sdlEvent;  // variable to detect SDL events

	while (running)		// the event loop
	{


		while (SDL_PollEvent(&sdlEvent)) {
#ifdef USE_IMGUI
			ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
#endif
			switch (sdlEvent.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch (sdlEvent.key.keysym.sym) {
				case SDLK_ESCAPE:
					exit(0);
					break;
				case SDLK_w:
					cameraComponent->setZ(cameraComponent->getZ() + cameraComponent->getSpeed());
					cout << "W" << endl;
					break;
				case SDLK_s:
					cameraComponent->setZ(cameraComponent->getZ() - cameraComponent->getSpeed());

					cout << "S" << endl;
					break;
				case SDLK_a:
					cameraComponent->setX(cameraComponent->getX() + cameraComponent->getSpeed());

					cout << "A" << endl;
					break;
				case SDLK_d:
					cameraComponent->setX(cameraComponent->getX() - cameraComponent->getSpeed());

					cout << "D" << endl;
					break;
				}
				break;

			case SDL_MOUSEMOTION:
				// Handle mouse movement to update camera direction
				cameraComponent->setYaw(cameraComponent->getYaw() + sdlEvent.motion.xrel * 0.1f);
				cameraComponent->setPitch(cameraComponent->getPitch() + sdlEvent.motion.yrel * 0.1f);
				cameraComponent->setPitch(glm::clamp(cameraComponent->getPitch(), -89.0f, 89.0f));

				break;
			}
			
		}


#ifdef USE_IMGUI
		glClearColor(0.231, 0.231, 0.329, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Render ImGui
		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		// ImGui UI elements
		int windowWidth, windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowWidth) * 0.15, static_cast<float>(windowHeight) * 0.75));
		ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		char** namesAsChar = new char* [hierarchy.getAllEntities().size()];
		int i = 0;
		for (auto& entity : hierarchy.getAllEntities()) {
			namesAsChar[i] = new char[entity->getName().size() + 1];
			strcpy_s(namesAsChar[i], entity->getName().size() + 1, entity->getName().c_str());
			i++;
		}

		if (ImGui::ListBox("##Listbox", &selectedItem, namesAsChar, hierarchy.getAllEntities().size())) {
			// Handle item selection here
			// 'selectedItem' contains the index of the selected item
		}

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(static_cast<float>(windowWidth) * 0.15, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowWidth) * 0.7, static_cast<float>(windowHeight) * 0.75));
		ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar);
#endif
		//update();
		draw(window, mundo, jugador, vertAmountJugador); // call the draw function
#ifdef USE_IMGUI
		ImGui::Image((void*)(intptr_t)texture, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(0, static_cast<float>(windowHeight) * 0.75), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowWidth) * 0.85, static_cast<float>(windowHeight) * 0.25));
		ImGui::Begin("Information", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar);
		if (ImGui::BeginTabBar("Tabs")) {
			if (ImGui::BeginTabItem("Statistics")) {
				ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
				ImGui::Text("Frame Time: %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
				ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);

				MEMORYSTATUSEX memoryStatus;
				memoryStatus.dwLength = sizeof(memoryStatus);
				GlobalMemoryStatusEx(&memoryStatus);
				ImGui::Text("Total Physical Memory: %llu MB", memoryStatus.ullTotalPhys / (1024 * 1024));
				ImGui::Text("Available Physical Memory: %llu MB", memoryStatus.ullAvailPhys / (1024 * 1024));

				FILETIME idleTime, kernelTime, userTime;

				if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
					ULARGE_INTEGER idle, kernel, user;
					idle.LowPart = idleTime.dwLowDateTime;
					idle.HighPart = idleTime.dwHighDateTime;
					kernel.LowPart = kernelTime.dwLowDateTime;
					kernel.HighPart = kernelTime.dwHighDateTime;
					user.LowPart = userTime.dwLowDateTime;
					user.HighPart = userTime.dwHighDateTime;

					ULONGLONG totalTime = (kernel.QuadPart - idle.QuadPart) + (user.QuadPart - idle.QuadPart);
					double usage = (static_cast<double>(totalTime - idle.QuadPart) / totalTime) * 100.0;

					ImGui::Text("CPU Usage: %.2f%%", usage);
				}
				else {
					ImGui::Text("Failed to retrieve CPU usage");
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("OpenGL Configuration")) {
				if (ImGui::Checkbox("Limit FPS", &checkboxValue)) {
					SDL_GL_SetSwapInterval(checkboxValue);  // Disable vsync
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Console")) {
				// Display redirected stdout content in ImGui
				ImGui::Text("%s", stdoutRedirect.GetOutput().c_str());
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(static_cast<float>(windowWidth) * 0.85, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowWidth) * 0.15, static_cast<float>(windowHeight)));
		ImGui::Begin("Inspect", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		// Add ImGui UI elements here
		if (ImGui::BeginTabBar("Tabs")) {
			if (ImGui::BeginTabItem("Properties")) {
				if (selectedItem >= 0) {
					Entity* selectedEntity = hierarchy.getAllEntities().at(selectedItem);
					selectedEntity->drawProperties();
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::End();
		ImGui::Render();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		// Swap buffers and present
		SDL_GL_SwapWindow(window);
	}

	cleanup();

	//FIN LOOP PRINCIPAL
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}