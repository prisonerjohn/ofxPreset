#pragma once

#include "ofxImGui.h"

#include "Parameter.h"

static const int kGuiMargin = 10;

namespace ofxPreset
{
	struct GuiSettings
	{
		ofVec2f windowPos;
		ofVec2f windowSize;
		bool mouseOverGui;
	};
	
	class Gui
	{
	public:
		static inline void SetNextWindow(GuiSettings & settings);

		static inline bool BeginWindow(Parameter<bool> & parameter, const GuiSettings & settings, bool collapse = true);
		static inline bool BeginWindow(const string & name, const GuiSettings & settings, bool collapse = true, bool * opened = nullptr);
	
		static inline void EndWindow(GuiSettings & settings);
	
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
