namespace COGE
{
	// maybe implement to file and then read from file when need to it but... I dont know.
	// maybe textures will be better. But textures may use way more bytes than vertices and indices.
	// I don't have any idea surely. But I'll continue to do that.
	float A_vertices[] = 
	{
		-1.0f,	+1.0f, //0
		-0.8f,	+1.0f, //1
		+0.8f,	+1.0f, //2
		+1.0f,	+1.0f, //3
		-0.8f,	+0.8f, //4
		+0.8f,	+0.8f, //5
		-0.8f,	+0.1f, //6
		+0.8f,	+0.1f, //7
		-0.8f,	-0.1f, //8
		+0.8f,	-0.1f, //9
		-1.0f,	-1.0f, //10
		-0.8f,	-1.0f, //11
		+0.8f,	-1.0f, //12
		+1.0f,	-1.0f  //13
	};

	unsigned int A_indices[] = 
	{
		0,	10,	11,
		0,	1,	11,

		2,	3,	13,
		2,	12,	13,

		1,	2,	4,
		2,	4,	5,

		6,	7,	9,
		6,	8,	9
	};

	float C_vertices[] = 
	{
		-1.0f,	+1.0f, //0
		+1.0f,	+1.0f, //1
		-0.8f,	+0.8f, //2
		+1.0f,	+0.8f, //3
		-0.8f,	-0.8f, //4
		+1.0f,	-0.8f, //5
		-1.0f,	-1.0f, //6
		+1.0f,	-1.0f, //7
		-1.0f,	+0.8f, //8
		-1.0f,	-0.8f  //9
	};

	unsigned int C_indices[] = 
	{
		0,	1,	3,
		0,	8,	3,

		8,	2,	4,
		8,	9,	4,

		9,	6,	7,
		9,	5,	7
	};

	GLS::Drawer* get_A()
	{
		unsigned int each_size[] = {2};
		return new GLS::Drawer(sizeof(A_vertices), A_vertices,sizeof(A_indices), A_indices,GL_STATIC_DRAW, 
			sizeof(each_size), each_size, 2);
	}
}