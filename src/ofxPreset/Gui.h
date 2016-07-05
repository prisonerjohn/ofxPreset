#pragma once

#include "ofxImGui.h"

#include "Parameter.h"

static const int kGuiMargin = 10;

namespace ofxPreset
{	
    class Gui
	{
    public:
        struct Settings
        {
            inline Settings();

            ofVec2f windowPos;
            ofVec2f windowSize;
            bool windowBlock;
            bool mouseOverGui;
        };

	public:
		static inline void SetNextWindow(Settings & settings);

		static inline bool BeginWindow(Parameter<bool> & parameter, Settings & settings, bool collapse = true);
		static inline bool BeginWindow(const string & name, Settings & settings, bool collapse = true, bool * opened = nullptr);
	
		static inline void EndWindow(Settings & settings);

		static inline void AddGroup(ofParameterGroup & group, Settings & settings);
	
        static inline bool AddParameter(Parameter<glm::tvec2<int>> & parameter);
        static inline bool AddParameter(Parameter<glm::tvec3<int>> & parameter);
        static inline bool AddParameter(Parameter<glm::tvec4<int>> & parameter);

        static inline bool AddParameter(Parameter<glm::vec2> & parameter);
        static inline bool AddParameter(Parameter<glm::vec3> & parameter);
        static inline bool AddParameter(Parameter<glm::vec4> & parameter);
        
        static inline bool AddParameter(Parameter<ofVec2f> & parameter);
        static inline bool AddParameter(Parameter<ofVec3f> & parameter);
        static inline bool AddParameter(Parameter<ofVec4f> & parameter);
        
        static inline bool AddParameter(Parameter<ofFloatColor> & parameter);
		
        template<typename ParameterType>
		static inline bool AddParameter(Parameter<ParameterType> & parameter);

		static inline bool AddRange(const string & name, Parameter<float> & parameterMin, Parameter<float> & parameterMax, float speed = 0.01f);

		static inline void AddImage(ofBaseHasTexture & hasTexture, const ofVec2f & size);
		static inline void AddImage(ofTexture & texture, const ofVec2f & size);
    };
}

#include "Gui.inl"
