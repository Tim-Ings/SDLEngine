#include "Sprite.h"



// creates a new sprite from the given image file
Sprite::Sprite(const std::string& path) :
	name(""),
	width(0),
	height(0),
	shader(nullptr),
	textureID(0),
	vertexBuffer(0),
	indexBuffer(0),
	uvBuffer(0),
	shaderUniformLoc_sampler(0),
	shaderUniformLoc_colorTint(0),
	shaderUniformLoc_model(0),
	shaderUniformLoc_view(0),
	shaderUniformLoc_projection(0),
	shaderAttribLoc_vertexUV(0),
	shaderAttribLoc_vertexPosition(0)
{
	name = path;

	// load shader
	shader = new ShaderProgram("Texture.vs", "Texture.fs");

	// get attributes from shader
	MapShaderAttributes();

	// load image
	LoadImage();

	// generate buffers
	GenerateVertexBuffer();
	GenerateIndexBuffer();

	// generate vertex array object
	GenerateVertexArrayObject();

	// set uniform attributes
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader->SetUniform("sampler", 0); //set to 0 because the texture will be bound to GL_TEXTURE0
}


// frees resources associated with the sprite
Sprite::~Sprite()
{
	Unload();
}


// generates vertext buffer for simple square sprite
void Sprite::GenerateVertexBuffer()
{
	vertexData[0].position = { -1, -1, 0 };
	vertexData[0].uv = { 0, 1 };

	vertexData[1].position = { 1, -1, 0 };
	vertexData[1].uv = { 1, 1 };

	vertexData[2].position = { -1, 1, 0 };
	vertexData[2].uv = { 0, 0 };

	vertexData[3].position = { 1, 1, 0 };
	vertexData[3].uv = { 1, 0 };

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	if (!indexBuffer)
		fatalError("FAILED: Unable to create index buffer");
}


void Sprite::GenerateVertexArrayObject()
{
	// generate and bind a vao
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);

	// bind buffers - !!! THIS IS NOT SAVED IN THE VAO BUT REQUIRED FOR SETUP !!!
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // index

	// enable attribs
	glEnableVertexAttribArray(shaderAttribLoc_vertexPosition);
	glEnableVertexAttribArray(shaderAttribLoc_vertexUV);

	// define attribs
	glVertexAttribPointer(shaderAttribLoc_vertexPosition,
		3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionTexture),
		(void*)offsetof(VertexPositionTexture, position));
	glVertexAttribPointer(shaderAttribLoc_vertexUV,
		2, GL_FLOAT, GL_TRUE, sizeof(VertexPositionTexture),
		(void*)offsetof(VertexPositionTexture, uv));

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, NULL); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL); // index

	// unbind vao
	glBindVertexArray(NULL);
}


void Sprite::MapShaderAttributes()
{
	shaderUniformLoc_sampler = shader->GetUniformLocation("sampler");
	shaderUniformLoc_colorTint = shader->GetUniformLocation("colorTint");
	shaderUniformLoc_model = shader->GetUniformLocation("model");
	shaderUniformLoc_view = shader->GetUniformLocation("view");
	shaderUniformLoc_projection = shader->GetUniformLocation("projection");
	shaderAttribLoc_vertexPosition = shader->GetAttribLocation("vertexPosition");
	shaderAttribLoc_vertexUV = shader->GetAttribLocation("vertexUV");
}


void Sprite::LoadImage()
{
	// load image
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(name.c_str());
	textureID = GenerateTexture(surface);

	// free the usurface after we have created a texture from it
	if (surface)
		SDL_FreeSurface(surface);
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


void Sprite::Draw(Camera3* cam, const SDL_Rect& dest, const Color& color)
{
	// bind shader
	shader->Bind();

	// bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// bind vao
	glBindVertexArray(vertexArrayObjectID);

	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // index

	// pass color tint to shader
	glUniform4f(shaderUniformLoc_colorTint, (float)color.r / 255, (float)color.g / 255, (float)color.b / 255, (float)color.a / 255);

	// pass model transformation to shader
	glm::mat4 model = MAT4_I;
	model = glm::translate(model, glm::vec3(dest.x, dest.y, 0.0f));
	model = glm::rotate(model, 0.0f, VEC3_UP);
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(shaderUniformLoc_model, 1, GL_FALSE, glm::value_ptr(model));

	// TODO DISABLE VIEW + PROJ TO KEEP SPRITE IN SCREEN SPACE
	// pass camera veiw + projection to the shader
	glUniformMatrix4fv(shaderUniformLoc_view, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
	glUniformMatrix4fv(shaderUniformLoc_projection, 1, GL_FALSE, glm::value_ptr(cam->GetPerspectiveMatrix()));

	// draw the triangles
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	// unbind voa
	glBindVertexArray(NULL);

	// unbind shader
	shader->Unbind();
}
