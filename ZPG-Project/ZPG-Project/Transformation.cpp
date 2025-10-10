#include "Transformation.h"

Transformation::Transformation()
{
	this->matrix = glm::mat4(1.0f);
}

void Transformation::applyTransforms(ShaderProgram* shaderProgram)
{
   for (int i = 0; i < transforms.size(); i++)
   {
       this->matrix = transforms[i]->applyTransform(this->matrix);
   }

   shaderProgram->setUniform("modelMatrix", this->matrix);
}

void Transformation::resetMatrix()
{
	this->matrix = glm::mat4(1.0f);
}
