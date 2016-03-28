#include "FloorGrid.h"



FloorGrid::FloorGrid(glm::vec3 centre, int dim, int spacing, Color color) :
	vertexCount(0),
	vertexData(nullptr),
	vertexBuffer(0),
	shader(nullptr),
	shaderUniformLoc_model(0),
	shaderUniformLoc_view(0),
	shaderUniformLoc_projection(0),
	shaderAttribLoc_vertexPosition(0),
	shaderAttribLoc_vertexColor(0)
{
	// load shaders
	shader = new ShaderProgram("Color.vs", "Color.fs");

	// get shader attrib locations
	shaderAttribLoc_vertexColor = shader->GetAttribLocation("vertexColor");
	shaderUniformLoc_model = shader->GetUniformLocation("model");
	shaderUniformLoc_view = shader->GetUniformLocation("view");
	shaderUniformLoc_projection = shader->GetUniformLocation("projection");

	// build the grid
	float extent = dim / spacing;
	std::vector<VertexPositionColor> verticies;
	for (GLint loop = -extent; loop < extent; loop += spacing)
	{
		// Draw lines along Z-Axis
		verticies.push_back({ { loop + centre.x, centre.y, extent + centre.z }, color });	// glVertex3f(loop, centre.y, extent);
		verticies.push_back({ { loop + centre.x, centre.y, -extent + centre.z }, color });	// glVertex3f(loop, centre.y, -extent);
		// Draw lines across X-Axis
		verticies.push_back({ { -extent + centre.x, centre.y, loop + centre.z }, color });	// glVertex3f(-extent, centre.y, loop);
		verticies.push_back({ { extent + centre.x, centre.y, loop + centre.z }, color });	// glVertex3f(extent, centre.y, loop);

		vertexCount += 4;
	}
	vertexData = &verticies[0];

	std::vector<int> indicies;
	for (int i = 0; i < vertexCount; i++)
	{
		indicies.push_back(i);
		indexCount++;
	}
	indexData = &indicies[0];

	// gen buffers
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	if (!vertexBuffer)
		fatalError("FAILED: Unable to create vertex buffer");

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	if (!indexBuffer)
		fatalError("FAILED: Unable to create index buffer");

	GenerateVertexArrayObject();
}


void FloorGrid::GenerateVertexArrayObject()
{
	// generate and bind a vao
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);

	// bind buffers - !!! THIS IS NOT SAVED IN THE VAO BUT REQUIRED FOR SETUP !!!
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // index

	// enable attribs
	glEnableVertexAttribArray(shaderAttribLoc_vertexPosition);
	glEnableVertexAttribArray(shaderAttribLoc_vertexColor);

	// define attribs
	glVertexAttribPointer(shaderAttribLoc_vertexPosition,
		3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor),
		(void*)offsetof(VertexPositionColor, position));
	glVertexAttribPointer(shaderAttribLoc_vertexColor,
		4, GL_FLOAT, GL_TRUE, sizeof(VertexPositionColor),
		(void*)offsetof(VertexPositionColor, color));

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, NULL); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL); // index

	// unbind vao
	glBindVertexArray(NULL);
}


void FloorGrid::Draw(Camera3* cam)
{
	// bind shader
	shader->Bind();

	// bind vao
	glBindVertexArray(vertexArrayObjectID);

	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer); // index

	// pass model transformation to shader
	glm::mat4 model = MAT4_I;
	/*model = glm::translate(model, glm::vec3(0.0f));
	model = glm::rotate(model, 0.0f, VEC3_UP);
	model = glm::scale(model, glm::vec3(1.0f));*/
	glUniformMatrix4fv(shaderUniformLoc_model, 1, GL_FALSE, glm::value_ptr(model));

	// pass camera veiw + projection to the shader
	glUniformMatrix4fv(shaderUniformLoc_view, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
	glUniformMatrix4fv(shaderUniformLoc_projection, 1, GL_FALSE, glm::value_ptr(cam->GetPerspectiveMatrix()));

	// draw the triangles
	glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, (void*)0);

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	// unbind voa
	glBindVertexArray(NULL);

	// unbind shader
	shader->Unbind();
}
