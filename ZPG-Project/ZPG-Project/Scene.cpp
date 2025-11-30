#include "Scene.h"
#include <unordered_map>
#include <string>

Scene::Scene(Controller* controller, Camera* camera, std::vector<Light*> lights, Skybox* skybox, int sceneState)
{
	this->sceneState = sceneState;
	this->camera = camera;
	this->controller = controller;
	this->lights = lights;
	this->skybox = skybox;
	this->timer = 8000;

	bezierSpline = new BezierSplineTransform();
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
		if(flashlight)
			object->setFlashlight(this->flashlight);
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

		if(flashlight)
			this->flashlight->updateDirection(camera->getFront());
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

	if (this->sceneState == 0)
	{
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
		glDisable(GL_STENCIL_TEST);

		this->selectedObjectId = (int)index;

		if (this->selectedObjectIndex != this->selectedObjectId - 1 && this->selectedObjectIndex >= 0)
			dObjects[this->selectedObjectIndex]->resetOrigColor();

		if (this->selectedObjectId > 0 && this->selectedObjectId <= dObjects.size())
		{
			this->selectedObjectIndex = this->selectedObjectId - 1;

			if (sceneState == 1)
			{
				if (dObjects[this->selectedObjectIndex]->objectType == "target")
				{
					delete dObjects[this->selectedObjectIndex];
					dObjects.erase(dObjects.begin() + this->selectedObjectIndex);
					this->selectedObjectIndex = -1;
					this->selectedObjectId = 0;
					this->score++;
					this->timer += 500;
					std::cout << "Score: " << this->score << " Time remaining: " << this->timer << std::endl;
				}
			}

		}
		else 
		{
			this->selectedObjectId = 0;
			this->selectedObjectIndex = -1;
		}

		this->controller->resetClicks();
	}

	if (this->controller->wasClicked(GLFW_KEY_C) || this->controller->wasClicked(GLFW_KEY_B))
	{
		std::cout << "Creating object" << std::endl;

		GLubyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)this->mouseX;
		GLint y = (GLint)this->mouseY;

		int newy = this->windowSize.y - y;

		glEnable(GL_STENCIL_TEST);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glDisable(GL_STENCIL_TEST);

		glm::vec3 screenCoord = glm::vec3((float)x, (float)newy, depth);

		glm::mat4 view = camera->getCamera();
		glm::mat4 projection = camera->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, this->windowSize.x, this->windowSize.y);
		glm::vec3 worldPos = glm::unProject(screenCoord, view, projection, viewPort);

		if(this->controller->wasClicked(GLFW_KEY_C))
		{
			Transformation* transform = new Transformation();
			transform->transforms.push_back(new Translate(worldPos));
			transform->transforms.push_back(new Scale(glm::vec3(0.02f, 0.02f, 0.02f)));

			DrawableObject* dObject;

			if (this->defTexture)
				dObject = new DrawableObject(this->defModel, this->defShaderProgram, this->defColor, this->defTexture);
			else
				dObject = new DrawableObject(this->defModel, this->defShaderProgram, this->defColor);

			dObject->addTransform(transform);

			vector<DrawableObject*> newObjects = this->dObjects;
			newObjects.push_back(dObject);

			this->addDrawableObjects(newObjects);
		}
		else if(this->controller->wasClicked(GLFW_KEY_B))
		{
			bezierSpline->addPoint(worldPos);

			Transformation* bezTrans = new Transformation();
			
			bezTrans->transforms.push_back(bezierSpline);
			bezTrans->transforms.push_back(new Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90));
			bezTrans->transforms.push_back(new Scale(glm::vec3(0.01f, 0.01f, 0.01f)));

			dObjects[1]->addTransform(bezTrans);
		}

		this->controller->resetClicks();
	}

	if (this->sceneState == 1)
	{
		timer--;
		if (timer <= 0)
		{
			std::cout << "Game Over! Final Score: " << this->score << std::endl;
			exit(0);
		}

		if (this->frameCount++ > 600)
		{
			this->frameCount = 0;

			DrawableObject* dObject;

			if (this->defTexture)
				dObject = new DrawableObject(this->defModel, this->defShaderProgram, this->defColor, this->defTexture);
			else
				dObject = new DrawableObject(this->defModel, this->defShaderProgram, this->defColor);

			if (this->dObjects.size() < 50)
			{
				vector<DrawableObject*> newObjects = this->dObjects;

				Transformation* transform = new Transformation();
				//transform->transforms.push_back(new Translate(glm::vec3((rand() % 60 - 30) / 10.0f, 0.5f, (rand() % 60 - 30))));

				std::vector<glm::vec3> points;
				points.clear();

				for (int i = 0; i < 5; i++)
					points.push_back(glm::vec3((rand() % 60 - 30), 0.5f, (rand() % 60 - 30)));

				transform->transforms.push_back(new SetTraslate(points, 0.001f));
				transform->transforms.push_back(new Scale(glm::vec3(0.1f, 0.1f, 0.1f)));

				dObject->addTransform(transform);
				dObject->objectType = "target";

				newObjects.push_back(dObject);

				this->addDrawableObjects(newObjects);
			}
		}
	}
}

void Scene::addAObject(ShaderProgram* shaderProgram, Model* model, glm::vec3 color, Texture* texture)
{
	this->defShaderProgram = shaderProgram;
	this->defModel = model;
	this->defColor = color;
	this->defTexture = texture;
}

void Scene::setFlashlight(Flashlight* flashlight)
{
	this->flashlight = flashlight;
}