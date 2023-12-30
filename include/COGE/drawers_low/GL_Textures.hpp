namespace GLS
{
	struct TextureData
	{
		unsigned int type;
		int width, height;
		unsigned char* data = nullptr;
		void destroyData();
	};

	class Texture
	{
	private:
		unsigned int texture;
	public:
		Texture(GLS::TextureData);
		~Texture();
		void bind();
		bool isOK();

	};
}