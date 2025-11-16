#include "Scene.h"
#include <unordered_map>
#include <string>

Scene::Scene(Controller* controller, Camera* camera, std::vector<Light*> lights, Skybox* skybox)
{
	this->camera = camera;
	this->controller = controller;
	this->lights = lights;
	this->skybox = skybox;
}

Scene::~Scene()
{
	for (DrawableObject* object : dObjects)
	{
		if (object)
		{
			delete object;
		}
	}

	for (Light* light : lights)
	{
		if (light)
		{
			delete light;
		}
	}

	delete controller;
	delete camera;
}

void Scene::addDrawableObjects(std::vector<DrawableObject*> dObjects)
{
	this->dObjects = dObjects;
	int id = 1;
	for (DrawableObject* object : dObjects)
	{
		object->addSubjects(this->camera, this->lights);
		object->setID(id++);
	}
}

void Scene::drawObjects()
{
	if (this->controller->getMouseX() != this->mouseX || this->controller->getMouseY() != this->mouseY || this->controller->getMovementVector() != glm::vec3(0.0f))
	{
		this->mouseX = this->controller->getMouseX();
		this->mouseY = this->controller->getMouseY();
		camera->updateCamera(this->mouseX, this->mouseY);
		camera->setPosition(this->controller->getMovementVector());
	}

	if (this->controller->getWindowSize() != this->windowSize)
	{
		this->windowSize = this->controller->getWindowSize();
		camera->updateProjectionMatrix(this->windowSize.x, this->windowSize.y, this->scrollY);
	}

	if (this->controller->getScrollY() != 0)
	{
		this->scrollY = this->controller->getScrollY();
		camera->updateProjectionMatrix(this->windowSize.x, this->windowSize.y, this->scrollY);
		this->controller->resetScrollY();
		this->scrollY = 0;
	}

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (DrawableObject* object : dObjects)
	{
		object->DrawObject();
	}


	if (skybox)
		skybox->draw(camera->getCamera(), camera->getProjectionMatrix());


	for (Light* light : lights)
	{
		light->updateLight();
	}

	for (DrawableObject* object : dObjects)
	{
		object->Notify(SubjectType::LIGHT);
	}


	if (this->selectedObjectIndex >= 0)
	{
		dObjects[this->selectedObjectIndex]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		if (this->controller->wasClicked(GLFW_KEY_DELETE))
		{
			delete dObjects[this->selectedObjectIndex];
			dObjects.erase(dObjects.begin() + this->selectedObjectIndex);
			this->selectedObjectIndex = -1;
			this->selectedObjectId = 0;
		}
	}

	if (this->controller->wasClicked(GLFW_MOUSE_BUTTON_LEFT))
	{
		GLubyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)this->mouseX;
		GLint y = (GLint)this->mouseY;

		int newy = this->windowSize.y - y;

		glEnable(GL_STENCIL_TEST);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glDisable(GL_STENCIL_TEST);

		this->selectedObjectId = (int)index;

		if (this->selectedObjectIndex != this->selectedObjectId - 1 && this->selectedObjectIndex >= 0)
			dObjects[this->selectedObjectIndex]->resetOrigColor();

		if (this->selectedObjectId > 0 && this->selectedObjectId <= dObjects.size())
		{
			this->selectedObjectIndex = this->selectedObjectId - 1;

			/*if (dObjects.size() > 1 && this->selectedObjectIndex > 0) 
			{
				delete dObjects[this->selectedObjectIndex];
				dObjects.erase(dObjects.begin() + this->selectedObjectIndex);
				this->selectedObjectIndex = -1;
				this->selectedObjectId = 0;
			}*/

		}
		else {
			this->selectedObjectId = 0;
			this->selectedObjectIndex = -1;
		}

		glm::vec3 screenCoord = glm::vec3((float)x, (float)newy, depth);

		glm::mat4 view = camera->getCamera();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, this->windowSize.x, this->windowSize.y);
		glm::vec3 worldPos = glm::unProject(screenCoord, view, projection, viewPort);

		this->controller->resetClicks();
	}
}
