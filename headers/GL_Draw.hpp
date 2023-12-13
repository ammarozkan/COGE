#include <vector>

namespace GLS
{
	struct Object3D
	{
		glm::vec3 position = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);
		glm::mat4 rotation = glm::mat4(1);
		glm::mat4 model;

		void modelRefresh();
		void shader_model(unsigned int model_location);
		void rotateRelative(glm::vec3 t, float angle);
		glm::vec3 getFront();
		glm::vec3 getRight();
	};

	class Drawer
	{
	private:
		VAO *vao = nullptr;
		VBO *vbo = nullptr;
		EBO *ebo = nullptr;
		unsigned int indices;

		void object_init(unsigned int vs, float*v, unsigned int is, unsigned int*i, unsigned int t);
	public:
		Drawer();
		Drawer(MODEL model, unsigned int draw_type);
		Drawer(MODEL model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem);
		~Drawer();

		void init_buffers(MODEL model, unsigned int draw_type);
		void init_buffers(MODEL model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem);
		
		void drawTriangle();
		void drawElements();
	};
}



namespace GLS
{



	// OBJECT3D DEFINITIONS




	void Object3D::modelRefresh()
	{
		glm::mat4 rot = rotation * glm::mat4(1);
		glm::mat4 trans = glm::translate(glm::mat4(1),position);
		glm::mat4 scal = glm::scale(glm::mat4(1),scale);
		model = trans * scal * rot;
	}

	void Object3D::shader_model(unsigned int model_location) // User should use the shader before function
	{
		glUniformMatrix4fv(model_location,1,GL_FALSE,glm::value_ptr(model));
	}

	void Object3D::rotateRelative(glm::vec3 t, float angle)
	{
		glm::vec4 th = rotation * glm::vec4(t.x,t.y,t.z,1.0f);
		rotation = glm::rotate(rotation, angle, glm::vec3(t.x,t.y,t.z));
	}

	glm::vec3 Object3D::getFront()
	{
		glm::vec4 r = (rotation * glm::vec4(0.0f,0.0f,1.0f,1.0f));
		return glm::vec3(r.x,r.y,r.z);
	}

	glm::vec3 Object3D::getRight()
	{
		glm::vec4 r = (rotation * glm::vec4(-1.0f,0.0f,0.0f,1.0f));
		return glm::vec3(r.x,r.y,r.z);
	}

	

	// DRAWER DEFINITIONS



	void Drawer::object_init(unsigned int v_size, float*ver, unsigned int i_size, unsigned int*ind, unsigned int type)
	{
		vao = new VAO(); vbo = new VBO(); ebo = new EBO();
		vao->bind();
		vbo->data(v_size,ver,type);
		ebo->data(i_size,ind,type);
	}

	Drawer::Drawer() {}

	Drawer::~Drawer() 
	{
		if(vao!=nullptr) { delete vao; delete vbo; delete ebo; }
	}

	Drawer::Drawer(MODEL model, unsigned int draw_type) { init_buffers(model,draw_type); }

	Drawer::Drawer(MODEL model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem=0) 
	{ init_buffers(model,draw_type,each_size_size,each_size,sumofthem); }

	void Drawer::init_buffers(MODEL model, unsigned int draw_type)
	{
		object_init(model.vertice_size,model.vertices,model.indice_size,model.indices,draw_type);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		indices = model.indice_size/sizeof(unsigned int);
	}

	void Drawer::init_buffers(MODEL model, unsigned int draw_type, unsigned int each_size_size, unsigned int* each_size, unsigned int sumofthem=0)
	{
		object_init(model.vertice_size,model.vertices,model.indice_size,model.indices,draw_type);

		unsigned int count = each_size_size/sizeof(unsigned int);
		if(sumofthem == 0) for (unsigned int i = 0;i<count;i++) sumofthem += each_size[i];

		unsigned int offset = 0;
		for(unsigned int i = 0;i<count;i++)
		{
			glVertexAttribPointer(i, each_size[i], GL_FLOAT, GL_FALSE, sumofthem * sizeof(float), (void*)(offset));
			glEnableVertexAttribArray(i);
			offset+=each_size[i]*sizeof(float);
		}

		indices = model.indice_size/sizeof(unsigned int);
	}

	void Drawer::drawElements()
	{
		vao->bind();
		glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
	}
}
