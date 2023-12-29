#include <COGE/core/Core.h>

COGE::Engine::~Engine() 
{
	/*delete generalShader;
	delete UIShader;
	free(planeModel->vertices);
	free(planeModel->indices);
	delete planeModel;*/

	delete UIShader;
	delete planeModel;
	for(unsigned int i = 0;i<forests.size();i++) delete forests[i];
	delete sky;
}