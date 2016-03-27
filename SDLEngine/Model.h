#pragma once
//#include <fbxsdk.h>

class Model
{
public:
	Model();
	~Model();

	//// Load the model from an FBX file
	//void LoadFromFBX(const char* fileName);

	//// Call to render the model
	//void Render();

private:
	//// Scene that holds our loaded FBX model information
	//FbxScene* mScene;

	//// Recursive function to traverse the nodes to draw
	//void DrawRecursive(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition);
	//// Draw the geometry of our meshes
	//void DrawMesh(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition);

	//// Get the geometry offset to a node. This is only for the mesh and the children do not inherit this transform
	//FbxAMatrix GetGeometryOffset(FbxNode* pNode);
};