#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "ofxPreset.h"

class ofApp
	: public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// Camera
	void saveCamera();
	void loadCamera();

	ofEasyCam camera;

	// Mesh
	float stepper;
	float cubeSize;

	// Render
	bool loadImage(const string & filePath);

	ofTexture texture;

	// GUI
	void imGui();

	ofxImGui gui;
	bool guiVisible;
	bool mouseOverGui;

	// Parameters
	void loadSettings(const string & filePath);
	void saveSettings(const string & filePath);

	enum RenderMode
	{
		RenderModeNone = 0,
		RenderModeColor,
		RenderModeTexture
	};

	struct : ofParameterGroup
	{
		struct : ofParameterGroup
		{
			ofxPreset::Parameter<ofFloatColor> background{ "Background", ofFloatColor::black };
			ofxPreset::Parameter<ofFloatColor> foreground{ "Foreground", ofFloatColor::crimson };

			PARAM_DECLARE("Colors", background, foreground);
		} colors; 
		
		struct : ofParameterGroup
		{
			ofxPreset::Parameter<bool> mouseEnabled{ "Mouse Enabled", true, true };
			ofParameter<string> filePath{ "File Path", "camera.json" };

			PARAM_DECLARE("Camera", mouseEnabled, filePath);
		} camera;

		struct : ofParameterGroup
		{
			ofxPreset::Parameter<bool> enabled{ "Enabled", true, true };
			ofxPreset::Parameter<float> sizeMin{ "Size Min", 10.0f, 0.0f, 1000.0f };
			ofxPreset::Parameter<float> sizeMax{ "Size Max", 200.0f, 0.0f, 1000.0f };
			ofxPreset::Parameter<float> speed{ "Speed", 0.1f, 0.0f, 1.0f };

			PARAM_DECLARE("Mesh", enabled, sizeMin, sizeMax, speed);
		} mesh;

		struct : ofParameterGroup
		{
			ofxPreset::Parameter<int> fillMode{ "Fill Mode", RenderModeTexture };
			ofxPreset::Parameter<int> strokeMode{ "Stroke Mode", RenderModeNone };
			ofxPreset::Parameter<bool> preview{ "Preview", false, true };
			ofParameter<string> imagePath{ "Image Path", "texture.jpg" };

			PARAM_DECLARE("Render", fillMode, strokeMode, preview, imagePath);
		} render;

		PARAM_DECLARE("App", colors, camera, mesh, render);
	} parameters;
};
