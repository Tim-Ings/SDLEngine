#include "Model.h"



// creates a new sprite from the given image file
Model::Model(const std::string& path) :
	name(""),
	shader(nullptr),
	textureID(0),
	vertexBuffer(0),
	indexBuffer(0),
	uvBuffer(0),
	shaderUniformLoc_model(0),
	shaderUniformLoc_view(0),
	shaderUniformLoc_projection(0),
	shaderAttribLoc_vertexPosition(0),
	shaderAttribLoc_vertexColor(0)
{
	// load shader
	shader = new ShaderProgram("Color.vs", "Color.fs");

	// get attributes from shader
	MapShaderAttributes();

	// load fbx model
	LoadModel(path);
	
	// generate a vertex array object
	GenerateVertexArrayObject();

	// set uniform attributes
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader->SetUniform("sampler", 0); //set to 0 because the texture is bound to GL_TEXTURE0
}


// frees resources associated with the sprite
Model::~Model()
{
	Unload();
}


void Model::LoadModel(std::string file)
{
#define LOAD_FBX
#ifdef LOAD_FBX
	// create the fbx sdk manager
	FbxManager* sdkManager = FbxManager::Create();

	// create an io settings object
	FbxIOSettings * ios = FbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ios);

	// configure the fbx io settings object
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_MATERIAL, true);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_TEXTURE, true);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_LINK, false);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_SHAPE, false);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GOBO, false);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_ANIMATION, true);
	(*(sdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);

	// create an importer
	FbxImporter* fbxImporter = FbxImporter::Create(sdkManager, "");

	// initialize the importer
	bool fbxImportStatus = fbxImporter->Initialize(file.c_str(), -1, sdkManager->GetIOSettings());
	if (!fbxImportStatus) 
	{
		std::cout << fbxImporter->GetStatus().GetErrorString() << std::endl;
		fatalError("Call to FbxImporter::Initialize() failed");
	}

	// create a new scene so it can be populated by the imported file
	fbxScene = FbxScene::Create(sdkManager, "myScene");

	// import the contents of the file into the scene.
	fbxImporter->Import(fbxScene);

	// the file has been imported, we can get rid of the importer
	fbxImporter->Destroy();

	// file format version numbers to be populated.
	int verMajor, verMinor, verRevision;

	// populate the fbx file format version numbers with the import file
	fbxImporter->GetFileVersion(verMajor, verMinor, verRevision);

	std::cout << "scene name: " << fbxScene->GetName() << std::endl;
	std::cout << "scene version: " << verMajor << "." << verMinor << "." << verRevision << std::endl;

	// generate buffers
	GenerateBuffers();
#else
	VertexPositionColor cubeVertexData[8];
	cubeVertexData[0].position = { -0.5f, 0.5f, 0.5f };
	cubeVertexData[0].color = { 255, 0, 0, 255 };
	cubeVertexData[1].position = { -0.5f, 0.5f, -0.5f };
	cubeVertexData[1].color = { 255, 255, 255, 255 };
	cubeVertexData[2].position = { 0.5f, 0.5f, -0.5f };
	cubeVertexData[2].color = { 255, 255, 255, 255 };
	cubeVertexData[3].position = { 0.5f, 0.5f, 0.5f };
	cubeVertexData[3].color = { 255, 255, 255, 255 };
	cubeVertexData[4].position = { -0.5f, -0.5f, 0.5f };
	cubeVertexData[4].color = { 255, 255, 255, 255 };
	cubeVertexData[5].position = { -0.5f, -0.5f, -0.5f };
	cubeVertexData[5].color = { 255, 255, 255, 255 };
	cubeVertexData[6].position = { 0.5f, -0.5f, -0.5f };
	cubeVertexData[6].color = { 255, 255, 255, 255 };
	cubeVertexData[7].position = { 0.5f, -0.5f, 0.5f };
	cubeVertexData[7].color = { 255, 255, 255, 255 };

	int cubeIndexData[36];
	// CCW winding
	cubeIndexData[0] = 0;
	cubeIndexData[1] = 2;
	cubeIndexData[2] = 1;
	cubeIndexData[3] = 0;
	cubeIndexData[4] = 3;
	cubeIndexData[5] = 2;
	cubeIndexData[6] = 0;
	cubeIndexData[7] = 1;
	cubeIndexData[8] = 4;
	cubeIndexData[9] = 1;
	cubeIndexData[10] = 5;
	cubeIndexData[11] = 4;
	cubeIndexData[12] = 1;
	cubeIndexData[13] = 2;
	cubeIndexData[14] = 5;
	cubeIndexData[15] = 2;
	cubeIndexData[16] = 6;
	cubeIndexData[17] = 5;
	cubeIndexData[18] = 7;
	cubeIndexData[19] = 2;
	cubeIndexData[20] = 3;
	cubeIndexData[21] = 7;
	cubeIndexData[22] = 6;
	cubeIndexData[23] = 2;
	cubeIndexData[24] = 4;
	cubeIndexData[25] = 3;
	cubeIndexData[26] = 0;
	cubeIndexData[27] = 4;
	cubeIndexData[28] = 7;
	cubeIndexData[29] = 3;
	cubeIndexData[30] = 4;
	cubeIndexData[31] = 5;
	cubeIndexData[32] = 6;
	cubeIndexData[33] = 4;
	cubeIndexData[34] = 6;
	cubeIndexData[35] = 7;

	// CW winding
	/*cubeIndexData[0] = 1;
	cubeIndexData[1] = 2;
	cubeIndexData[2] = 0;
	cubeIndexData[3] = 2;
	cubeIndexData[4] = 3;
	cubeIndexData[5] = 0;
	cubeIndexData[6] = 4;
	cubeIndexData[7] = 1;
	cubeIndexData[8] = 0;
	cubeIndexData[9] = 4;
	cubeIndexData[10] = 5;
	cubeIndexData[11] = 1;
	cubeIndexData[12] = 5;
	cubeIndexData[13] = 2;
	cubeIndexData[14] = 1;
	cubeIndexData[15] = 5;
	cubeIndexData[16] = 6;
	cubeIndexData[17] = 2;
	cubeIndexData[18] = 3;
	cubeIndexData[19] = 2;
	cubeIndexData[20] = 7;
	cubeIndexData[21] = 2;
	cubeIndexData[22] = 6;
	cubeIndexData[23] = 7;
	cubeIndexData[24] = 0;
	cubeIndexData[25] = 3;
	cubeIndexData[26] = 4;
	cubeIndexData[27] = 3;
	cubeIndexData[28] = 7;
	cubeIndexData[29] = 4;
	cubeIndexData[30] = 6;
	cubeIndexData[31] = 5;
	cubeIndexData[32] = 4;
	cubeIndexData[33] = 7;
	cubeIndexData[34] = 6;
	cubeIndexData[35] = 4;*/


	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexData), &cubeVertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	if (!vertexBuffer)
		fatalError("FAILED: Unable to create vertex buffer");

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndexData), &cubeIndexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	if (!indexBuffer)
		fatalError("FAILED: Unable to create index buffer");

	indexCount = 36;

#endif // LOAD_FBX
}


// generates buffers from fbx scene
void Model::GenerateBuffers()
{
	// get the root node
	FbxNode* rootNode = fbxScene->GetRootNode();
	int childCount = rootNode->GetChildCount();
	// get data from all children
	for (int childI = 0; childI < childCount; childI++)
	{
		// get the child's mesh
		FbxNode* child = rootNode->GetChild(childI);
		FbxMesh* mesh = child->GetMesh();
		if (mesh) // is the child a mesh object?
		{
			// add all the child's verticies to the vertex data
			int vertCount = mesh->GetControlPointsCount();
			for (int vertI = 0; vertI < vertCount; vertI++)
			{
				FbxVector4 vert = mesh->GetControlPointAt(vertI);
				VertexPositionColor vpc;
				vpc.position = { (float)vert.mData[0], (float)vert.mData[1], (float)vert.mData[2] };
				vpc.color = { 255, 255, 255, 255 };
				//std::cout << "pushing vertex = " << vpc.position.x << ", " << vpc.position.y << "," << vpc.position.z << std::endl;
				vertexData.push_back(vpc);
			}

			// add all the child's indicies to the index data
			int polygonCount = mesh->GetPolygonCount();
			for (int polygonI = 0; polygonI < polygonCount; polygonI++)
			{
				int polygonSize = mesh->GetPolygonSize(polygonI);
				for (int indexI = 0; indexI < polygonSize; indexI++)
				{
					int index = mesh->GetPolygonVertex(polygonI, indexI);
					indexData.push_back(index);
					indexCount++;
				}
			}
		}
	}

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	if (!vertexBuffer)
		fatalError("FAILED: Unable to create vertex buffer");

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	if (!indexBuffer)
		fatalError("FAILED: Unable to create index buffer");
}


void Model::GenerateVertexArrayObject()
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


void Model::MapShaderAttributes()
{
	shaderUniformLoc_model = shader->GetUniformLocation("model");
	shaderUniformLoc_view = shader->GetUniformLocation("view");
	shaderUniformLoc_projection = shader->GetUniformLocation("projection");
	shaderAttribLoc_vertexPosition = shader->GetAttribLocation("vertexPosition");
	shaderAttribLoc_vertexColor = shader->GetAttribLocation("vertexColor");
}


void Model::Unload()
{
	// tell gl to flag vram used by this texture to be freed
	glDeleteTextures(1, &textureID);
}


void Model::Draw(Camera3* cam, const glm::vec3& pos)
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
	model = glm::translate(model, pos);
	model = glm::rotate(model, 0.0f, VEC3_UP);
	model = glm::scale(model, glm::vec3(1.0f));
	glUniformMatrix4fv(shaderUniformLoc_model, 1, GL_FALSE, glm::value_ptr(model));

	// pass camera veiw + projection to the shader
	glUniformMatrix4fv(shaderUniformLoc_view, 1, GL_FALSE, glm::value_ptr(cam->GetViewMatrix()));
	glUniformMatrix4fv(shaderUniformLoc_projection, 1, GL_FALSE, glm::value_ptr(cam->GetPerspectiveMatrix()));

	// draw the triangles
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);

	// unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

	// unbind voa
	glBindVertexArray(NULL);

	// unbind shader
	shader->Unbind();
}
