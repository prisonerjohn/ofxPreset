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
	bool imGui();

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
			ofParameter<ofFloatColor> background{ "Background", ofFloatColor::black };
			ofParameter<ofFloatColor> foreground{ "Foreground", ofFloatColor::crimson };

			PARAM_DECLARE("Colors", background, foreground);
		} colors; 
		
		struct : ofParameterGroup
		{
			ofParameter<bool> mouseEnabled{ "Mouse Enabled", true };
			ofParameter<string> filePath{ "File Path", "camera.json" };

			PARAM_DECLARE("Camera", mouseEnabled, filePath);
		} camera;

		struct : ofParameterGroup
		{
			ofParameter<bool> enabled{ "Enabled", true };
			ofParameter<float> sizeMin{ "Size Min", 10.0f, 0.0f, 1000.0f };
			ofParameter<float> sizeMax{ "Size Max", 200.0f, 0.0f, 1000.0f };
			ofParameter<float> speed{ "Speed", 0.1f, 0.0f, 1.0f };

			PARAM_DECLARE("Mesh", enabled, sizeMin, sizeMax, speed);
		} mesh;

		struct : ofParameterGroup
		{
			ofParameter<int> fillMode{ "Fill Mode", RenderModeTexture };   // Auto-update because we're using radio buttons in the gui.
			ofParameter<int> strokeMode{ "Stroke Mode", RenderModeNone };  // Auto-update because we're using radio buttons in the gui.
			ofParameter<bool> preview{ "Preview", false };                 // Auto-update because we can close the window from its toolbar.
			ofParameter<string> imagePath{ "Image Path", "texture.jpg" };

			PARAM_DECLARE("Render", fillMode, strokeMode, preview, imagePath);
		} render;

		PARAM_DECLARE("App", colors, camera, mesh, render);
	} parameters;
};
