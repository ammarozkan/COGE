#include <COGE/Mathematics.h>
#include <COGE/Macros.h>
#include <fstream>

std::ofstream log_file(COGE_LOG_FILE_PATH);

void print(glm::vec3 t)
{
	std::cout << "X:" << t.x << " Y:" << t.y << " Z:" << t.z << std::endl;
}

void print(glm::vec4 t)
{
	std::cout << "X:" << t.x << " Y:" << t.y << " Z:" << t.z << " W:" << t.w << std::endl;
}

void print(float t)
{
	std::cout << "Float:" << t << std::endl;
}