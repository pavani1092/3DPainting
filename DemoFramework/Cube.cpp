#include "OpenGL.h"

#include <string>
#include <vector>

// Includes to create the cube
#include "ISceneNode.h"
#include "ModelManager.h"
#include "DrawableProxy.h"
#include "DrawableCubeSolution.h"
#include "DrawableSphereSolution.h"
#include "DrawableFloorSolution.h"
#include "DrawableQuad.h"
#include "DrawableOBJ.h"
#include "DrawableBrushPath.h"
#include "SetBackgroundCommand.h"
#include "SetPolygonModeCommand.h"
// Material includes
#include "SolidColorMaterialSolution.h"
#include "ShadedMaterial.h"
#include "MaterialProxy.h"
#include "MaterialManager.h"
#include "ShaderConstantMaterial.h"
#include "Color.h"

#include "BlankTexture2D.h"
#include "TextureBinding.h"
#include "TextureBindManager.h"
#include "TextureBindManagerOpenGL.h"
#include "TextureDataImage.h"
#include "SamplerApplicator.h"
#include "SimpleShaderMaterial.h"
#include "TexParam2DNoMipMap.h"
#include "TexParam2DMipMap.h"
#include "AdjustViewPortCommand.h"
#include "ShaderConstantFloat.h"
#include "ShaderConstantInt.h"

// Includes for the camera
#include "ExaminerCameraNode.h"
#include "PerspectiveTransformSolution.h"
#include "LookAtTransformSolution.h"
#include "ShaderConstantModelView.h"

// Lights
#include "PointLight.h"
#include "DirectionalLight.h"
#include "LightManager.h"
#include "ShaderConstantLights.h"

#include "RenderTargetProxy.h"
#include "RenderTarget.h"
#include "RenderManager.h"
#include "ClearFrameCommand.h"
#include "SwapCommand.h"
#include "DepthBuffer.h"

// Includes for walking the scene graph
#include "DebugRenderVisitor.h"
#include "PrintSceneVisitor.h"
#include "Background.h"

// Interaction
std::vector<IMouseHandler*> mouseHandlers;
std::vector<IKeyboardHandler*> keyboardHandlers;


using namespace Crawfis::Graphics;
using namespace Crawfis::Math;
using namespace std;


ISceneNode* rootSceneNode;
IVisitor* renderVisitor;
ExaminerCameraNode* examiner;

ISceneNode* uvSceneNode;
IVisitor* uvRenderVisitor;
ExaminerCameraNode* uvExaminer;

ISceneNode* wfSceneNode;
IVisitor* wfRenderVisitor;
ExaminerCameraNode* wfExaminer;

ISceneNode* texSceneNode;
IVisitor* texRenderVisitor;
ExaminerCameraNode* texExaminer;

ITextureDataObject* wfTexture;
ITextureDataObject* uvTexture;
ITextureDataObject* diffTexture;
ITextureDataObject* dummy;

RenderTargetProxy* wfFBO;
RenderTargetProxy* uvFBO;
RenderTargetProxy* texFBO;
bool wfCommand;
bool uvCommand;
bool texCommand;
bool mainCommand;
bool mainUVCommand;
bool mainTexCommand;
bool mainWFCommand;
TransformMatrixNodeSolution* objTransformBrush;

int windowGUID;
int windowWidth;
int windowHeight; 
int sideViewSize = 20;
int viewportSize = 180;
ShaderConstantVec4* brushColor;
ShaderConstantFloat* brushSize;
SamplerApplicator* uniformBindingTexture;
TextureBinding*  textureBinding;
ITextureDataObject* texture[5];
void CreateGLUTWindow(std::string windowTitle)
{
	windowWidth = 800;
	windowHeight = 600;
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	windowGUID = glutCreateWindow(windowTitle.c_str());
}

void InitializeOpenGLExtensions()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		throw "Error initializing GLEW";
	}

	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void InitializeDevices()
{
	CreateGLUTWindow("OpenGL Demo Framework");
	InitializeOpenGLExtensions();
	glDisable(GL_CULL_FACE);
}

void CreateLights()
{
	PointLight* pointLight = new PointLight("light0-pt");
	pointLight->setPosition(Vector3(-2, 5, -1));

	LightManager::Instance()->SetLight(0, pointLight);
	DirectionalLight* dirLight = new DirectionalLight("light1-dir");
	//dirLight->setColor(Colors::IndianRed);
	dirLight->setDirection(Vector3(10, 1, 1));
	LightManager::Instance()->SetLight(1, dirLight);
}

void CreateGoldMaterial()
{
	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\VertexLight.glsl");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\SolidColorSolution.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);

	Color gold(0.8314f, 0.6863f, 0.2169f, 1.0f);
	ShadedMaterial* shinyGold = new ShadedMaterial(shaderProgram);
	shinyGold->setAmbientReflection(0.01f*gold);
	shinyGold->setDiffuseReflection(0.7f*gold);
	shinyGold->setSpecularReflection(0.25f*gold);
	shinyGold->setShininess(100.0f);

	ShaderConstantMaterial* materialConstant = new ShaderConstantMaterial("frontMaterial");
	materialConstant->setValue(shinyGold);
	ShaderConstantLights* lightConstant = new ShaderConstantLights();
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(materialConstant);
	shaderConstantList->AddConstant(lightConstant);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("ShinyGold", shinyGold);
}

void CreateSimpleMaterial(ITextureDataObject* texture, string name)
{
	SamplerApplicator* uniformBinding = new SamplerApplicator("texture");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(texture, uniformBinding);
	binding->Enable();
	binding->Disable();


	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\SimpleVertex.vert");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\SimpleFragment.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);

	SimpleShaderMaterial* simpleMaterial = new SimpleShaderMaterial(shaderProgram);
	shaderProgram->setShaderConstant(uniformBinding);
	simpleMaterial->AddTexture(binding);

	MaterialManager::Instance()->RegisterMaterial(name, simpleMaterial);

}

/*void CreateTexturedMaterial()
{
	ITextureDataObject* texture = new BlankTexture2D(1024, 1024);
	ITextureDataObject* redTexture = new BlankTexture2D(1024, 1024, Color(1, 0, 0, 1), GL_RGB);
	redTexture->setTextureParams(&TexParam2DNoMipMap::Instance);

	ITextureDataObject* imageTexture = new TextureDataImage("../Media/Textures/bunny_texture.png", GL_RGB);
	imageTexture->setTextureParams(&TexParam2DMipMap::Instance);
	SamplerApplicator* uniformBinding = new SamplerApplicator("texture");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(imageTexture, uniformBinding);
	binding->Enable();
	binding->Disable();
	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\ShadedTextured-vert.glsl");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\Textured.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial(shaderProgram);
	texturedMaterial->setShaderConstant(uniformBinding);
	texturedMaterial->AddTexture(binding);

	ShadedMaterial* white = new ShadedMaterial(shaderProgram);
	white->setAmbientReflection(0.0f*Colors::White);
	white->setDiffuseReflection(0.75f*Colors::White);
	white->setSpecularReflection(0.25f*Colors::White);
	white->setShininess(10.0f);

	ShaderConstantMaterial* materialConstant = new ShaderConstantMaterial("frontMaterial");
	materialConstant->setValue(white);
	ShaderConstantLights* lightConstant = new ShaderConstantLights();
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(materialConstant);
	shaderConstantList->AddConstant(lightConstant);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("Textured", texturedMaterial);
}*/

void CreateNormalSampledMaterial()
{
	ITextureDataObject* imageTexture = new TextureDataImage("..\\Lab2\\Media\\Textures\\dino_normals.png", GL_RGB);
	imageTexture->setName("bunnyNormals");
	imageTexture->setTextureParams(&TexParam2DMipMap::Instance);
	SamplerApplicator* uniformBinding = new SamplerApplicator("normalSampler");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(imageTexture, uniformBinding);
	binding->Enable();
	binding->Disable();

	SamplerApplicator* uniformBindingDiffuse = new SamplerApplicator("diffuseSampler");
	TextureBinding* bindingDiffuse = TextureBindManager::Instance()->CreateBinding(diffTexture, uniformBindingDiffuse);
	bindingDiffuse->Enable();
	bindingDiffuse->Disable();


	SamplerApplicator* uniformBindingUV = new SamplerApplicator("uvSampler");
	TextureBinding* bindingUV = TextureBindManager::Instance()->CreateBinding(uvTexture, uniformBindingUV);
	bindingUV->Enable();
	bindingUV->Disable();

	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\NormalVertex.vert");

	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\NormalFrag.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial(shaderProgram);
	texturedMaterial->AddTexture(binding);
	texturedMaterial->AddTexture(bindingDiffuse);
	texturedMaterial->AddTexture(bindingUV);

	ShadedMaterial* white = new ShadedMaterial(shaderProgram);
	white->setAmbientReflection(0.0f*Colors::White);
	white->setDiffuseReflection(0.75f*Colors::White);
	white->setSpecularReflection(0.25f*Colors::White);
	white->setShininess(10.0f);

	ShaderConstantMaterial* materialConstant = new ShaderConstantMaterial("frontMaterial");
	materialConstant->setValue(white);
	ShaderConstantLights* lightConstant = new ShaderConstantLights();
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(materialConstant);
	shaderConstantList->AddConstant(lightConstant);
	shaderConstantList->AddConstant(uniformBinding);
	shaderConstantList->AddConstant(uniformBindingDiffuse);
	shaderConstantList->AddConstant(uniformBindingUV);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("NormalMaterial", texturedMaterial);
}


void createMaterialFromTexture(ITextureDataObject* texture) {
	SamplerApplicator* uniformBinding = new SamplerApplicator("texture");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(texture, uniformBinding);
	binding->Enable();
	binding->Disable();
	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\ShadedTextured-vert.glsl");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\Textured.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial(shaderProgram);
	texturedMaterial->setShaderConstant(uniformBinding);
	texturedMaterial->AddTexture(binding);

	ShadedMaterial* white = new ShadedMaterial(shaderProgram);
	white->setAmbientReflection(0.0f*Colors::White);
	white->setDiffuseReflection(0.75f*Colors::White);
	white->setSpecularReflection(0.25f*Colors::White);
	white->setShininess(10.0f);

	ShaderConstantMaterial* materialConstant = new ShaderConstantMaterial("frontMaterial");
	materialConstant->setValue(white);
	ShaderConstantLights* lightConstant = new ShaderConstantLights();
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(materialConstant);
	shaderConstantList->AddConstant(lightConstant);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("UVSavedTexture", texturedMaterial);
}
void CreateUVColoredMaterial()
{
	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\SimpleMVPVertex.vert");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\TexturedColored.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* uvMaterial = new SimpleShaderMaterial(shaderProgram);
	MaterialManager::Instance()->RegisterMaterial("UVColored", uvMaterial);
}

void CreateWFMaterial()
{
	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\WFVertex.vert");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\WFfrag.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* wfMaterial = new SimpleShaderMaterial(shaderProgram);
	MaterialManager::Instance()->RegisterMaterial("WFMaterial",wfMaterial);

}

/*void CreateMapMaterial(ITextureDataObject* texture) {
	SamplerApplicator* uniformBindingUV = new SamplerApplicator("uvTexture");
	TextureBinding* bindingUV = TextureBindManager::Instance()->CreateBinding(texture, uniformBindingUV);
	bindingUV->Enable();
	bindingUV->Disable();

	ITextureDataObject* imageTexture = new TextureDataImage("../Media/Textures/bunny_texture.png", GL_RGB);
	imageTexture->setTextureParams(&TexParam2DMipMap::Instance);
	SamplerApplicator* uniformBinding = new SamplerApplicator("mainTexture");
	TextureBinding* binding = TextureBindManager::Instance()->CreateBinding(imageTexture, uniformBinding);
	binding->Enable();
	binding->Disable();

	

	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\DoubleTextured-vert.glsl");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\DoubleTextured.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, fragmentRoutine);
	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial(shaderProgram);
	ShaderConstantCollection* uniformBindingList = new ShaderConstantCollection();
	//uniformBindingList->AddConstant(uniformBindingUV);
	//uniformBindingList->AddConstant(uniformBinding);
	
	texturedMaterial->setShaderConstant(uniformBindingList);
	texturedMaterial->AddTexture(bindingUV);
	texturedMaterial->AddTexture(binding);
	

	ShadedMaterial* white = new ShadedMaterial(shaderProgram);
	white->setAmbientReflection(0.0f*Colors::White);
	white->setDiffuseReflection(0.75f*Colors::White);
	white->setSpecularReflection(0.25f*Colors::White);
	white->setShininess(10.0f);

	ShaderConstantMaterial* materialConstant = new ShaderConstantMaterial("frontMaterial");
	materialConstant->setValue(white);
	ShaderConstantLights* lightConstant = new ShaderConstantLights();
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(materialConstant);
	shaderConstantList->AddConstant(lightConstant);
	shaderConstantList->AddConstant(uniformBindingUV);
	shaderConstantList->AddConstant(uniformBinding);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("UVMapTexture", texturedMaterial);
}*/

void CreateBrushMaterial()
{
	//ITextureDataObject* texture = new BlankTexture2D(512, 512, Colors::Grey, GL_RGBA, false);
	texture[0] = new TextureDataImage("..\\Media\\Textures\\tex5.jpg", GL_RGBA);
	texture[0]->setName("brushTex1");	
	texture[0]->setTextureParams(&TexParam2DNoMipMap::Instance);

	texture[1] = new TextureDataImage("..\\Media\\Textures\\tex1.jpg", GL_RGBA);
	texture[1]->setName("brushTex2");
	texture[1]->setTextureParams(&TexParam2DNoMipMap::Instance);

	texture[2] = new TextureDataImage("..\\Media\\Textures\\tex2.jpg", GL_RGBA);
	texture[2]->setName("brushTex3");
	texture[2]->setTextureParams(&TexParam2DNoMipMap::Instance);

	texture[3] = new TextureDataImage("..\\Media\\Textures\\tex3.jpg", GL_RGBA);
	texture[3]->setName("brushTex4");
	texture[3]->setTextureParams(&TexParam2DNoMipMap::Instance);

	texture[4] = new TextureDataImage("..\\Media\\Textures\\tex4.jpg", GL_RGBA);
	texture[4]->setName("brushTex5");
	texture[4]->setTextureParams(&TexParam2DNoMipMap::Instance);


	uniformBindingTexture = new SamplerApplicator("brushTexture");
	textureBinding = TextureBindManager::Instance()->CreateBinding(texture[0], uniformBindingTexture);
	textureBinding->Enable();
	textureBinding->Disable();

	SamplerApplicator* uniformBindingUV = new SamplerApplicator("uvTexture");
	TextureBinding* bindingUV = TextureBindManager::Instance()->CreateBinding(uvTexture, uniformBindingUV);
	bindingUV->Enable();
	bindingUV->Disable();

	VertexRoutine* vertexRoutine = new VertexRoutine("..\\Media\\Shaders\\brush.vert");
	GeometryRoutine* geometryRoutine = new GeometryRoutine("..\\Media\\Shaders\\brush.geom");
	FragmentRoutine* fragmentRoutine = new FragmentRoutine("..\\Media\\Shaders\\brush.frag");
	IShaderProgram* shaderProgram = new ShaderProgramWithMatrices(vertexRoutine, geometryRoutine,fragmentRoutine);
	SimpleShaderMaterial* texturedMaterial = new SimpleShaderMaterial(shaderProgram);
	//texturedMaterial->setShaderConstant(uniformBinding);
	texturedMaterial->AddTexture(textureBinding);
	texturedMaterial->AddTexture(bindingUV);

	
	brushColor = new ShaderConstantVec4("brushClr");
	brushSize = new ShaderConstantFloat("brushSize");
	//brushColor->setValue(Color(0.9f, 0.9f, 0.9f, 1.0f));
	ShaderConstantCollection* shaderConstantList = new ShaderConstantCollection();
	shaderConstantList->AddConstant(uniformBindingTexture);
	shaderConstantList->AddConstant(uniformBindingUV);
	shaderConstantList->AddConstant(brushColor);
	shaderConstantList->AddConstant(brushSize);
	shaderProgram->setShaderConstant(shaderConstantList);

	MaterialManager::Instance()->RegisterMaterial("BrushTexture", texturedMaterial);
}


ISceneNode* CreateUVSceneGraph()
{
	
	DrawableQuad* UVObj = new DrawableQuad();
	ModelManager::Instance()->RegisterModel("UVObj", UVObj);

	DrawableProxy* objNode = new DrawableProxy("UVObj", "UVObj");

	CreateSimpleMaterial(uvTexture,"uvTex");

	MaterialProxy* objMaterial = new MaterialProxy("UV Material", "uvTex", objNode);
	TransformMatrixNodeSolution* objTransform = new TransformMatrixNodeSolution("UVSpace", objMaterial);
	//objTransform->Scale(20, 20, 20);

	GroupNode* group = new GroupNode("UV");
	group->AddChild(objTransform);
	uvExaminer = new ExaminerCameraNode("UVExaminer", group);
	uvExaminer->setWidth(viewportSize);
	uvExaminer->setHeight(viewportSize);
	return uvExaminer;
}

ISceneNode* CreateWFSceneGraph()
{

	DrawableQuad* WFObj = new DrawableQuad();
	ModelManager::Instance()->RegisterModel("WFObj", WFObj);

	DrawableProxy* objNode = new DrawableProxy("WFObj", "WFObj");

	CreateSimpleMaterial(wfTexture,"wfTex");



	MaterialProxy* objMaterial = new MaterialProxy("WF Material", "wfTex", objNode);
	TransformMatrixNodeSolution* objTransform = new TransformMatrixNodeSolution("WFSpace", objMaterial);
	//objTransform->Scale(35, 35, 35);
	GroupNode* group = new GroupNode("WF");
	group->AddChild(objTransform);
	wfExaminer = new ExaminerCameraNode("WFExaminer", group);
	wfExaminer->setWidth(viewportSize);
	wfExaminer->setHeight(viewportSize);
	return wfExaminer;
}

RenderTargetProxy* CreateFrameBufferWithTexture(ITextureDataObject* texture, string name, Crawfis::Graphics::ISceneNode * scene, Crawfis::Graphics::Color color , bool& command) {
	IDepthBuffer* depthBuffer = new DepthBuffer(600, 600, false);
	IRenderTarget* target = new RenderTarget(texture, depthBuffer);
	RenderManager::Instance()->RegisterRenderTarget(name, target);
	if (!command) {
		ClearFrameCommand* c = new ClearFrameCommand(color);
		c->setName(name);
		target->setEnableCommand(c);
		if (name == "wf") {
			target->setEnableCommand(new SetPolygonModeCommand(GL_LINE));
			target->setDisableCommand(new SetPolygonModeCommand(GL_FILL));
		}
		
		(command) = true;
	}
	
	RenderTargetProxy* frameBuffer = new RenderTargetProxy("Display", name, scene);
	return frameBuffer;
}

ISceneNode* CreateTexSceneGraph()
{
	

	DrawableQuad* TexObj = new DrawableQuad();
	ModelManager::Instance()->RegisterModel("TexObj", TexObj);

	DrawableProxy* objNode = new DrawableProxy("TexObj", "TexObj");

	CreateSimpleMaterial(diffTexture, "diffTex");


	MaterialProxy* objMaterial = new MaterialProxy("Tex Material", "diffTex", objNode);
	TransformMatrixNodeSolution* objTransform = new TransformMatrixNodeSolution("TexSpace", objMaterial);

	GroupNode* group = new GroupNode("Tex");
	texExaminer = new ExaminerCameraNode("TexExaminer", group);
	texExaminer->setWidth(viewportSize);
	texExaminer->setHeight(viewportSize);


	group->AddChild(objTransformBrush);
	return texExaminer;
}



ISceneNode* CreateSceneGraph()
{

	DrawableOBJ* bunnyObj = new DrawableOBJ("..\\Media\\Obj\\dino.obj");
	ModelManager::Instance()->RegisterModel("BunnyObj", bunnyObj);
	DrawableProxy* objNode = new DrawableProxy("BunnyObj", "BunnyObj");

	DrawableOBJ* wfBunnyObj = new DrawableOBJ("..\\Media\\Obj\\dino.obj", true);
	ModelManager::Instance()->RegisterModel("WFBunnyObj", wfBunnyObj);
	DrawableProxy* wfObjNode = new DrawableProxy("WFBunnyObj", "WFBunnyObj");

	

	CreateLights();
	CreateGoldMaterial();









	CreateUVColoredMaterial();
	CreateWFMaterial();
	

	if (wfTexture == 0) {
		wfTexture = new BlankTexture2D(600, 600);
		wfTexture->setName("wfTex");
		wfTexture->setTextureParams(&TexParam2DNoMipMap::Instance);
		wfTexture->Enable();

		MaterialProxy* wfObjMaterial = new MaterialProxy("WF Scene Material", "WFMaterial", wfObjNode);
		TransformMatrixNodeSolution* wfObjTransform = new TransformMatrixNodeSolution("WFSceneSpace", wfObjMaterial);
		wfFBO = CreateFrameBufferWithTexture(wfTexture, "wf", wfObjTransform, Colors::Yellow,wfCommand);
	}
	

	if (uvTexture == 0) {
		uvTexture = new BlankTexture2D(600, 600);
		uvTexture->setName("uvTex");
		uvTexture->setTextureParams(&TexParam2DNoMipMap::Instance);
		uvTexture->Enable();

		MaterialProxy* uvObjMaterial = new MaterialProxy("uv scene Material", "UVColored", objNode);
		TransformMatrixNodeSolution* uvObjTransform = new TransformMatrixNodeSolution("uvsceneSpace", uvObjMaterial);
		uvObjTransform->Translate(0, -0.15, 0);
		//uvObjTransform->Rotate(90.0f, Vector3(0, 1, 0));
		uvObjTransform->Scale(6, 5, 8);
		uvCommand = false;
		uvFBO = CreateFrameBufferWithTexture(uvTexture, "uv", uvObjTransform, Colors::Blue,uvCommand);
	}
	
	CreateBrushMaterial();
	DrawableBrushPath* brushPath = new DrawableBrushPath();
	ModelManager::Instance()->RegisterModel("brushObj", brushPath);
	DrawableProxy* brushObjNode = new DrawableProxy("brushObj", "brushObj");

	MaterialProxy* objMaterialBrush = new MaterialProxy("brush scene Material", "BrushTexture", brushObjNode);
	objTransformBrush = new TransformMatrixNodeSolution("BrushSceneSpace", objMaterialBrush);
	mouseHandlers.push_back(brushPath);
	keyboardHandlers.push_back(brushPath);

	if (diffTexture == 0) {
		diffTexture = new BlankTexture2D(600, 600, Colors::White, GL_RGBA, false);
		diffTexture->setName("diffTextt");
		diffTexture->setTextureParams(&TexParam2DNoMipMap::Instance);
		diffTexture->Enable();

		
		IRenderTarget* target = new RenderTarget(diffTexture);
		RenderManager::Instance()->RegisterRenderTarget("mapp", target);
	//	int vstate[4];
	//	glGetIntegerv(GL_VIEWPORT, &vstate[0]);
	//	target->setEnableCommand(new AdjustViewPortCommand(0, 0, 600, 600));
		//target->setDisableCommand(new AdjustViewPortCommand(vstate[0], vstate[1], vstate[2], vstate[3]));
		//texCommand = false;
		//texFBO = CreateFrameBufferWithTexture(diffTexture, "mapp", objTransformBrush, Colors::White, texCommand);
		texFBO= new RenderTargetProxy("Display", "mapp", objTransformBrush);
	}
	



	 
	CreateNormalSampledMaterial();
	MaterialProxy* objMaterialB = new MaterialProxy("Obj Material", "NormalMaterial", objNode);
	TransformMatrixNodeSolution* objTransformB = new TransformMatrixNodeSolution("MainSpace", objMaterialB);
	objTransformB->Translate(0, -0.15, 0);
	//objTransformB->Rotate(90.0f, Vector3(0, 1, 0));
	objTransformB->Scale(6, 5, 8);



	GroupNode* group = new GroupNode("Pedestal");
	group->AddChild(wfFBO);
	group->AddChild(uvFBO);
	group->AddChild(texFBO);
	group->AddChild(objTransformB);
	//group->AddChild(objTransformBrush);
	examiner = new ExaminerCameraNode("Examiner", group);
	examiner->setWidth(600);
	examiner->setHeight(600);
	return examiner;
}

void DisplayFrame()
{
	brushColor->setValue(examiner->getBrushColor());
	brushSize->setValue(examiner->getBrushSize());
	textureBinding->setTexture(texture[examiner->getBrushTexture()-1]);
	glEnable(GL_SCISSOR_TEST);

	glViewport(0, 0, 600, 600);
	glScissor(0, 0, 600, 600);
	rootSceneNode->Accept(renderVisitor);


	//wfExaminer->setWidth(viewportSize);
	//wfExaminer->setHeight(viewportSize);
	glViewport(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 1 * viewportSize - 1 * sideViewSize, viewportSize, viewportSize);
	glScissor(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 1 * viewportSize - 1 * sideViewSize, viewportSize, viewportSize);
	wfSceneNode->Accept(wfRenderVisitor);

	//uvExaminer->setWidth(viewportSize);
	//uvExaminer->setHeight(viewportSize);
	glViewport(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 2 * viewportSize - 2 * sideViewSize, viewportSize, viewportSize);
	glScissor(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 2 * viewportSize - 2 * sideViewSize, viewportSize, viewportSize);
	uvSceneNode->Accept(uvRenderVisitor);

	//texExaminer->setWidth(viewportSize);
	//texExaminer->setHeight(viewportSize);
	glViewport(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 3 * viewportSize - 3 * sideViewSize, viewportSize, viewportSize);
	glScissor(windowWidth - viewportSize - sideViewSize + 10, windowHeight - 3 * viewportSize - 3 * sideViewSize, viewportSize, viewportSize);
	texSceneNode->Accept(texRenderVisitor);

}

void ReshapeWindow(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
	/*examiner->setWidth(windowWidth/2);
	examiner->setHeight(windowHeight);
	glViewport(0, 0, windowWidth/2, windowHeight);*/
	glutPostRedisplay();
}

ISceneNode* CreateFrameBuffer(Crawfis::Graphics::ISceneNode * scene,string name, bool isSwap, bool hasBg, Crawfis::Graphics::Color color, bool& command)
{

	IRenderTarget* screen = new RenderTarget();
	RenderManager::Instance()->RegisterRenderTarget(name, screen);
	if (!command) {
		if (hasBg) {
			screen->setEnableCommand(new SetBackgroundCommand(color));//
		}
		else {
			ClearFrameCommand* c = new ClearFrameCommand(color);
			c->setName(name);
			screen->setEnableCommand(c);

		}

		screen->setDisableCommand(new SwapCommand(isSwap));
		command = true;
	}
	
	RenderTargetProxy* frameBuffer = new RenderTargetProxy("Screen Display", name, scene);
	return frameBuffer;
}
void KeyboardController(unsigned char key, int x, int y)
{
	printf("Key Pressed: %c\n", key);
	std::vector<IKeyboardHandler*>::iterator handlerIterator;
	for (handlerIterator = keyboardHandlers.begin(); handlerIterator != keyboardHandlers.end(); handlerIterator++)
	{
		(*handlerIterator)->KeyPress(key, x, y);
	}
	glutPostRedisplay();
}

void NumPadController(int key, int x, int y)
{
	std::vector<IKeyboardHandler*>::iterator handlerIterator;
	for (handlerIterator = keyboardHandlers.begin(); handlerIterator != keyboardHandlers.end(); handlerIterator++)
	{
		(*handlerIterator)->NumPadPress(key, x, y);
	}
	glutPostRedisplay();
}

void MousePressController(int button, int state, int ix, int iy)
{
	std::vector<IMouseHandler*>::iterator handlerIterator;
	for (handlerIterator = mouseHandlers.begin(); handlerIterator != mouseHandlers.end(); handlerIterator++)
	{
		(*handlerIterator)->MouseEvent(button, state, ix, iy);
	}
	glutPostRedisplay();
}

void MouseMotionController(int ix, int iy)
{
	std::vector<IMouseHandler*>::iterator handlerIterator;
	for (handlerIterator = mouseHandlers.begin(); handlerIterator != mouseHandlers.end(); handlerIterator++)
	{
		(*handlerIterator)->MouseMoved(ix, iy);
	}
	glutPostRedisplay();
}

void IdleCallback()
{
}
void InitializeDevIL()
{
	::ilInit();
	::iluInit();
	::ilutInit();
	//::ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	//::ilEnable(IL_ORIGIN_SET);
}

void initMainScene() {
	ISceneNode* scene = CreateSceneGraph();
	mainCommand = false;
	rootSceneNode = CreateFrameBuffer(scene, "mainScene",true,true, Colors::IndianRed, mainCommand);
	renderVisitor = new DebugRenderVisitor();
	PrintSceneVisitor* printScene = new PrintSceneVisitor();
	rootSceneNode->Accept(printScene);
	keyboardHandlers.push_back(examiner);
	mouseHandlers.push_back(examiner);
}
void initWFScene() {
	ISceneNode* scene = CreateWFSceneGraph();
	wfSceneNode = CreateFrameBuffer(scene, "WFScene", false,false, Colors::IndianRed,mainWFCommand);
	wfRenderVisitor = new DebugRenderVisitor();
	PrintSceneVisitor* printScene = new PrintSceneVisitor();
	wfSceneNode->Accept(printScene);
	//keyboardHandlers.push_back(wfExaminer);
	//mouseHandlers.push_back(wfExaminer);
}
void initUVScene() {
	ISceneNode* scene = CreateUVSceneGraph();
	mainUVCommand = false;
	uvSceneNode = CreateFrameBuffer(scene, "UVScene", false,false, Colors::IndianRed,mainUVCommand);
	uvRenderVisitor = new DebugRenderVisitor();
	PrintSceneVisitor* printScene = new PrintSceneVisitor();
	uvSceneNode->Accept(printScene);
	//keyboardHandlers.push_back(uvExaminer);
	//mouseHandlers.push_back(uvExaminer);
}
void initTexScene() {
	ISceneNode* scene = CreateTexSceneGraph();
	texSceneNode = CreateFrameBuffer(scene, "texScene", true, false,Colors::White,mainTexCommand);
	texRenderVisitor = new DebugRenderVisitor();
	PrintSceneVisitor* printScene = new PrintSceneVisitor();
	texSceneNode->Accept(printScene);
	//keyboardHandlers.push_back(texExaminer);
	//mouseHandlers.push_back(texExaminer);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	InitializeDevices();
	InitializeDevIL();
	TextureBindManagerOpenGL::Init();
	MatrixStack::Init();

	initMainScene();

	initWFScene();
	initUVScene();
	initTexScene();

	

	glutDisplayFunc(DisplayFrame);
	glutReshapeFunc(ReshapeWindow);
	glutKeyboardFunc(KeyboardController);
	glutSpecialFunc(NumPadController);
	glutMouseFunc(MousePressController);
	glutMotionFunc(MouseMotionController);

	glutMainLoop();

	return 0;
}