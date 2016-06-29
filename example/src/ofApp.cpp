#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_NOTICE);
	ofDisableArbTex();
	ofBackground(ofColor::black);

	this->stepper = 0.0f;

	// Load default settings, if any.
	this->loadSettings("defaults.json");

	// GUI
	this->gui.setup();
	this->guiVisible = true;
}

//--------------------------------------------------------------
void ofApp::update()
{
	this->stepper += this->parameters.mesh.speed;
	cubeSize = ofMap(sinf(this->stepper), -1.0f, 1.0f, this->parameters.mesh.sizeMin, this->parameters.mesh.sizeMax);
	
	if (this->guiVisible || this->parameters.camera.mouseEnabled)
	{
		ofShowCursor();
	}
	else
	{
		ofHideCursor();
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(this->parameters.colors.background.get());
	
	this->camera.begin();
	{	
		ofEnableDepthTest();

		ofSetColor(ofColor::white);

		if (this->parameters.mesh.enabled)
		{
			ofPushStyle();
			{
				ofSetColor(this->parameters.colors.foreground.get());
				
				if (this->parameters.render.fillMode != RenderModeNone)
				{
					ofFill();
					if (this->parameters.render.fillMode == RenderModeTexture && this->texture.isAllocated())
					{
						this->texture.bind();
					}
					ofDrawBox(this->cubeSize);
					if (this->parameters.render.fillMode == RenderModeTexture && this->texture.isAllocated())
					{
						this->texture.unbind();
					}
				}
				if (this->parameters.render.strokeMode != RenderModeNone)
				{
					ofNoFill();
					if (this->parameters.render.strokeMode == RenderModeTexture && this->texture.isAllocated())
					{
						this->texture.bind();
					}
					ofDrawBox(this->cubeSize);
					if (this->parameters.render.strokeMode == RenderModeTexture && this->texture.isAllocated())
					{
						this->texture.unbind();
					}
				}
			}
			ofPopStyle();
		}

		ofDisableDepthTest();
	}
	this->camera.end();

	// GUI
	this->mouseOverGui = false;
	if (this->guiVisible)
	{
		imGui();
	}
	if (this->mouseOverGui)
	{
		this->camera.disableMouseInput();
	}
	else if (this->parameters.camera.mouseEnabled)
	{
		this->camera.enableMouseInput();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::loadCamera()
{
	ofFile file(this->parameters.camera.filePath.get());
	if (file.exists())
	{
		nlohmann::json json;
		file >> json;

		ofxPreset::Serializer::Deserialize(json, this->camera);
	}

	if (this->parameters.camera.mouseEnabled)
	{
		this->camera.enableMouseInput();
	}
	else
	{
		this->camera.disableMouseInput();
	}
}

//--------------------------------------------------------------
void ofApp::saveCamera()
{
	nlohmann::json json;

	ofxPreset::Serializer::Serialize(json, this->camera);

	ofFile file(this->parameters.camera.filePath.get(), ofFile::WriteOnly);
	file << json;
}

//--------------------------------------------------------------
bool ofApp::loadImage(const string & filePath)
{
	ofImage image;
	image.setUseTexture(false);
	if (!image.load(filePath)) {
		ofLogError("ofApp::loadImage") << "No image found at " << filePath;
		return false;
	}

	ofTextureData texData;
	texData.width = image.getWidth();
	texData.height = image.getHeight();
	texData.textureTarget = GL_TEXTURE_2D;
	texData.bFlipTexture = true;
	this->texture.allocate(texData);
	this->texture.loadData(image.getPixels());

	this->parameters.render.imagePath = filePath;
	return true;
}

//--------------------------------------------------------------
void ofApp::imGui()
{
	this->gui.begin();
	{
		auto mainSettings = ofxPreset::GuiSettings();

		ofxPreset::Gui::AddGroup(this->parameters, mainSettings);

		/*if (ofxPreset::Gui::BeginWindow(this->parameters.getName(), mainSettings))
		{
			ImGui::Text("%.1f FPS (%.3f ms/frame)", ofGetFrameRate(), 1000.0f / ImGui::GetIO().Framerate);

			if (ImGui::Button("Save All..."))
			{
				auto dialogResult = ofSystemSaveDialog("settings.json", "Save Settings");
				if (dialogResult.bSuccess)
				{
					this->saveSettings(dialogResult.filePath);
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Load All..."))
			{
				auto dialogResult = ofSystemLoadDialog("Load Settings", false, ofToDataPath("settings"));
				if (dialogResult.bSuccess)
				{
					this->loadSettings(dialogResult.filePath);
				}
			}

			if (ImGui::CollapsingHeader(this->parameters.colors.getName().c_str(), nullptr, true, true))
			{
				ofxPreset::Gui::AddParameter(this->parameters.colors.background);
				ofxPreset::Gui::AddParameter(this->parameters.colors.foreground);
			}

			if (ImGui::CollapsingHeader(this->parameters.camera.getName().c_str(), nullptr, true, true))
			{
				if (ofxPreset::Gui::AddParameter(this->parameters.camera.mouseEnabled))
				{
					this->loadCamera();
				}
				if (ImGui::Button("Save..."))
				{
					auto dialogResult = ofSystemSaveDialog("camera.json", "Save Camera");
					if (dialogResult.bSuccess)
					{
						this->parameters.camera.filePath = dialogResult.filePath;
						this->saveCamera();
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Load..."))
				{
					auto dialogResult = ofSystemLoadDialog("Load Camera", false, ofToDataPath("settings"));
					if (dialogResult.bSuccess)
					{
						this->parameters.camera.filePath = dialogResult.filePath;
						this->loadCamera();
					}
				}
			}

			if (ImGui::CollapsingHeader(this->parameters.mesh.getName().c_str(), nullptr, true, true))
			{
				ofxPreset::Gui::AddParameter(this->parameters.mesh.enabled);
				ofxPreset::Gui::AddRange("Size Range", this->parameters.mesh.sizeMin, this->parameters.mesh.sizeMax, 1.0f);
				ofxPreset::Gui::AddParameter(this->parameters.mesh.speed);
				ImGui::Text("Size: %.2f", this->cubeSize);
			}

			if (ImGui::CollapsingHeader(this->parameters.render.getName().c_str(), nullptr, true, true))
			{
				if (ImGui::Button("Load Image..."))
				{
					auto dialogResult = ofSystemLoadDialog("Load Image", false, ofToDataPath(""));
					if (dialogResult.bSuccess)
					{
						this->loadImage(dialogResult.filePath);
					}
				}

				ImGui::SetNextTreeNodeOpened(true, ImGuiSetCond_Appearing);
				if (ImGui::TreeNode("Fill"))
				{
					ImGui::Columns(3);
					ImGui::RadioButton("None", this->parameters.render.fillMode.getRef(), RenderModeNone); ImGui::NextColumn();
					ImGui::RadioButton("Color", this->parameters.render.fillMode.getRef(), RenderModeColor); ImGui::NextColumn();
					ImGui::RadioButton("Texture", this->parameters.render.fillMode.getRef(), RenderModeTexture); ImGui::NextColumn();
					ImGui::Columns(1);

					ImGui::TreePop();
				}

				ImGui::SetNextTreeNodeOpened(true, ImGuiSetCond_Appearing);
				if (ImGui::TreeNode("Stroke"))
				{
					ImGui::Columns(3);
					ImGui::RadioButton("None", this->parameters.render.strokeMode.getRef(), RenderModeNone); ImGui::NextColumn();
					ImGui::RadioButton("Color", this->parameters.render.strokeMode.getRef(), RenderModeColor); ImGui::NextColumn();
					ImGui::RadioButton("Texture", this->parameters.render.strokeMode.getRef(), RenderModeTexture); ImGui::NextColumn();
					ImGui::Columns(1);

					ImGui::TreePop();
				}

				if (this->texture.isAllocated())
				{
					ofxPreset::Gui::AddParameter(this->parameters.render.preview);
				}
			}
		}
		ofxPreset::Gui::EndWindow(mainSettings);*/

		if (this->parameters.render.preview)
		{
			static const float kPreviewSize = 256.0f;
			auto previewSettings = ofxPreset::GuiSettings();
			previewSettings.windowPos = ofVec2f(ofGetWidth() - kPreviewSize - kGuiMargin * 3, kGuiMargin);
			previewSettings.windowSize = ofVec2f(kPreviewSize, kPreviewSize);

			if (ofxPreset::Gui::BeginWindow(this->parameters.render.preview, previewSettings, false))
			{
				ofxPreset::Gui::AddImage(this->texture, previewSettings.windowSize);
			}
			ofxPreset::Gui::EndWindow(previewSettings);
		}
	}
	this->gui.end();
}

//--------------------------------------------------------------
void ofApp::loadSettings(const string & filePath)
{
	ofFile file(filePath);
	if (file.exists())
	{
		nlohmann::json json;
		file >> json;

		ofxPreset::Serializer::Deserialize(json, this->parameters);

		this->loadCamera();

		if (!this->parameters.render.imagePath.get().empty())
		{
			this->loadImage(this->parameters.render.imagePath);
		}
	}
}

//--------------------------------------------------------------
void ofApp::saveSettings(const string & filePath)
{
	nlohmann::json json;

	ofxPreset::Serializer::Serialize(json, this->parameters);

	ofFile file(filePath, ofFile::WriteOnly);
	file << json;
}

