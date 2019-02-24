#include "DrawJob.h"
#include "GL/glew.h"

#include "UserInputGLFWKeyboardComponent.h"

#include <iostream>

DrawJob::DrawJob()
	: Job("DrawJob")
{

}


DrawJob::~DrawJob()
{

}

bool DrawJob::onStarting()
{
	return true;
}

bool DrawJob::onStopping()
{
	return true;
}

bool DrawJob::onUpdate()
{
	//std::cout << "Job " << getName() << " update:" << std::endl;
	for (auto& entity : *m_targetEntities.get())
	{
		TransformComponent* tcomponent;
		MeshComponent* mcomponent;

		entity->getComponent(tcomponent);
		entity->getComponent(mcomponent);

		if(UserInputKeyboardComponent::instance()->getInputValue(GLFW_KEY_E) == GLFW_PRESS)
		{
			std::cout << "E!" << std::endl;
		}

		if (tcomponent && mcomponent)
		{
			//std::cout << "\tDrawing entity \"" << entity->getName() << "\"...";
			const bool success = draw(tcomponent, mcomponent);
			/*if(success)
			{
				std::cout << "OK" << std::endl;
			}else
			{
				std::cout << "FAIL" << std::endl;
			}*/
		}
	}
	return true;
}

bool DrawJob::draw(const TransformComponent* tc, const MeshComponent* mc)
{
	// Everything present AND mesh has at least vertex buffer
	if(tc && mc && (mc->getFeatures() & MeshComponent::MESH_FEATURES::VERTEX) )
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER_ARB, mc->getVAO());
		glVertexAttribPointerARB(0, 3, GL_FLOAT, false, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, mc->getNumberVertex());
		glDisableVertexAttribArray(0);

		return true;
	}

	return false;
}
