#ifndef COGE_COGE_CLOSE_H
#define COGE_COGE_CLOSE_H

void deletion()
{
	delete generalShader;
	delete UIShader;
	free(planeModel->vertices);
	free(planeModel->indices);
	delete planeModel;
}

#endif