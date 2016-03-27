#include "Sprite.h"


ShaderProgram* Sprite::textureShader = nullptr;


// creates a new sprite from the given image file
Sprite::Sprite(const std::string& path)
{
	// load shaders if not already
	if (!Sprite::textureShader)
		Sprite::textureShader = new ShaderProgram("Texture.vs", "Texture.fs");

	// assign shader
	shader = Sprite::textureShader;

	// load image
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(path.c_str());
	textureID = GenerateTexture(surface);

	// free the usurface after we have created a texture from it
	if (surface)
		SDL_FreeSurface(surface);

	// generate buffers
	GenerateVertexBuffer();
	GenerateIndexBuffer();

	// get attributes from shader
	shaderUniformLoc_sampler = shader->GetUniformLocation("sampler");
	shaderAttribLoc_vertexPosition = shader->GetAttribLocation("vertexPosition");
	shaderAttribLoc_vertexUV = shader->GetAttribLocation("vertexUV");

	// set uniform attributes
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader->SetUniform("sampler", 0); //set to 0 because the texture is bound to GL_TEXTURE0
}


// frees resources associated with the sprite
Sprite::~Sprite()
{
	Unload();
}


// generates vertext buffer for simple square sprite
void Sprite::GenerateVertexBuffer()
{
	vertexData[0].position = { 0, 0, 0 };
	vertexData[0].uv = { 0, 0 };

	vertexData[1].position = { 1, 0, 0 };
	vertexData[1].uv = { 1, 0 };

	vertexData[2].position = { 0, 1, 0 };
	vertexData[2].uv = { 0, 1 };

	vertexData[3].position = { 1, 1, 0 };
	vertexData[3].uv = { 1, 1 };

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (!vertexBuffer)
		fatalError("FAILED: Unable to create vertex buffer");
}


// generates index buffer for simple square sprite
void Sprite::GenerateIndexBuffer()
{
	indexData[0] = 1;
	indexData[1] = 0;
	indexData[2] = 2;

	indexData[3] = 1;
	indexData[4] = 2;
	indexData[5] = 3;

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (!indexBuffer)
		fatalError("FAILED: Unable to create index buffer");
}


// generates a texture from the given surface
// returns an ogl pointer to the texture
GLuint Sprite::GenerateTexture(SDL_Surface* surface)
{
	if (!surface)
		fatalError("FAILED: Surface is null");

	GLuint texture;

	// create a texture in vram
	glGenTextures(1, &texture);
	if (!texture)
		fatalError("FAILED: Unable to create texture");

	// bind the newly created texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// fill the texture with data from the surface
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h,
				0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		fatalError("FAILED: glTexImage2D()");

	// enable linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}


void Sprite::Unload()
{
	// tell gl to flag vram used by this texture to be freed
	glDeleteTextures(1, &textureID);
}


void Sprite::Draw(const SDL_Rect& dest)
{
	// bind shader
	shader->Bind();

	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // index

	// enable and attribute the vertex buffer in the shader
	glEnableVertexAttribArray(shaderAttribLoc_vertexPosition);
	glVertexAttribPointer(shaderAttribLoc_vertexPosition,
		3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture),
		(void*)offsetof(VertexPositionTexture, position)); // position

	// enable and attribute the uv buffer in the shader
	glEnableVertexAttribArray(shaderAttribLoc_vertexUV);
	glVertexAttribPointer(shaderAttribLoc_vertexUV,
		2, GL_FLOAT, GL_TRUE, sizeof(VertexPositionTexture),
		(void*)offsetof(VertexPositionTexture, uv));

	// draw the triangles
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// unbind shader
	shader->Unbind();
}
