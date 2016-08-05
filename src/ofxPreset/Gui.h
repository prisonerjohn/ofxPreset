#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

static const int kGuiMargin = 10;

namespace ofxPreset
{	
    class Gui
	{
	public:
		struct WindowOpen
		{
			shared_ptr<ofParameter<bool>> parameter;
			bool value;
		};
	
		struct Settings
		{
			inline Settings();

			ofVec2f windowPos;
			ofVec2f windowSize;
			bool mouseOverGui;
			bool windowBlock;
		};

		static inline void SetNextWindow(Settings & settings);

		static inline bool BeginWindow(ofParameter<bool> & parameter, Settings & settings, bool collapse = true);
		static inline bool BeginWindow(const string & name, Settings & settings, bool collapse = true, bool * open = nullptr);
	
		static inline void EndWindow(Settings & settings);

		static inline void AddGroup(ofParameterGroup & group, Settings & settings);
	
        static inline bool AddParameter(ofParameter<glm::tvec2<int>> & parameter);
        static inline bool AddParameter(ofParameter<glm::tvec3<int>> & parameter);
        static inline bool AddParameter(ofParameter<glm::tvec4<int>> & parameter);

        static inline bool AddParameter(ofParameter<glm::vec2> & parameter);
        static inline bool AddParameter(ofParameter<glm::vec3> & parameter);
        static inline bool AddParameter(ofParameter<glm::vec4> & parameter);
        
        static inline bool AddParameter(ofParameter<ofVec2f> & parameter);
        static inline bool AddParameter(ofParameter<ofVec3f> & parameter);
        static inline bool AddParameter(ofParameter<ofVec4f> & parameter);
        
        static inline bool AddParameter(ofParameter<ofFloatColor> & parameter);

		template<typename ParameterType>
		static inline bool AddParameter(ofParameter<ParameterType> & parameter);

		static inline bool AddRadio(ofParameter<int> & parameter, vector<string> labels, int columns = 1);

		static inline bool AddRange(const string & name, ofParameter<float> & parameterMin, ofParameter<float> & parameterMax, float speed = 0.01f);

		static inline bool AddValues(const string & name, vector<glm::tvec2<int>> & values, int minValue, int maxValue);
		static inline bool AddValues(const string & name, vector<glm::tvec3<int>> & values, int minValue, int maxValue);
		static inline bool AddValues(const string & name, vector<glm::tvec4<int>> & values, int minValue, int maxValue);

		static inline bool AddValues(const string & name, vector<glm::vec2> & values, float minValue, float maxValue);
		static inline bool AddValues(const string & name, vector<glm::vec3> & values, float minValue, float maxValue);
		static inline bool AddValues(const string & name, vector<glm::vec4> & values, float minValue, float maxValue);

		static inline bool AddValues(const string & name, vector<ofVec2f> & values, float minValue, float maxValue);
		static inline bool AddValues(const string & name, vector<ofVec3f> & values, float minValue, float maxValue);
		static inline bool AddValues(const string & name, vector<ofVec4f> & values, float minValue, float maxValue);

		template<typename DataType>
		static inline bool AddValues(const string & name, vector<DataType> & values, DataType minValue, DataType maxValue);

		static inline void AddImage(ofBaseHasTexture & hasTexture, const ofVec2f & size);
		static inline void AddImage(ofTexture & texture, const ofVec2f & size);
    };
}

#include "Gui.inl"
