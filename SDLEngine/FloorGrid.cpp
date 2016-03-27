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
	shaderUniformLoc_vertexColor(0)
{
	// load shaders
	shader = new ShaderProgram("Color.vs", "Color.fs");

	// get shader attrib locations
	shaderUniformLoc_vertexColor = shader->GetAttribLocation("vertexColor");
	shaderUniformLoc_model = shader->GetUniformLocation("model");
	shaderUniformLoc_view = shader->GetUniformLocation("view");
	shaderUniformLoc_projection = shader->GetUniformLocation("projection");

	// build the grid
	std::vector<VertexPositionColor> lines;
	float extent = dim / spacing;
	for (GLint loop = -extent; loop < extent; loop += spacing)
	{
		// Draw lines along Z-Axis
		lines.push_back({ { loop + centre.x, centre.y, extent + centre.z }, color });	// glVertex3f(loop, centre.y, extent);
		lines.push_back({ { loop + centre.x, centre.y, -extent + centre.z }, color });	// glVertex3f(loop, centre.y, -extent);
		// Draw lines across X-Axis
		lines.push_back({ { -extent + centre.x, centre.y, loop + centre.z }, color });	// glVertex3f(-extent, centre.y, loop);
		lines.push_back({ { extent + centre.x, centre.y, loop + centre.z }, color });	// glVertex3f(extent, centre.y, loop);

		vertexCount += 4;
	}

	vertexData = &lines[0];

	// bind buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	if (!vertexBuffer)
		fatalError("FAILED: Unable to create vertex buffer");
}


void FloorGrid::Draw(Camera3* cam)
{
	// bind shader
	shader->Bind();

	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); // vertex

	// enable and attribute the vertex buffer in the shader
	glEnableVertexAttribArray(shaderAttribLoc_vertexPosition);
	glVertexAttribPointer(shaderAttribLoc_vertexPosition,
		3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColor),
		(void*)offsetof(VertexPositionColor, position)); // position

	// enable and attribute the color buffer in the shader
	glEnableVertexAttribArray(shaderUniformLoc_vertexColor);
	glVertexAttribPointer(shaderUniformLoc_vertexColor,
		4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexPositionColor),
		(void*)offsetof(VertexPositionColor, color)); // color

	// pass camera transformations to shader
	glm::mat4 model = MAT4_I;

	glUniformMatrix4fv(shaderUniformLoc_model, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(shaderUniformLoc_view, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
	glUniformMatrix4fv(shaderUniformLoc_projection, 1, GL_FALSE, glm::value_ptr(cam->GetPerspectiveMatrix()));

	// draw the triangles
	glDrawArrays(GL_LINES, 0, vertexCount);

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind shader
	shader->Unbind();
}
