#pragma once

#include "ofxImGui.h"

#include "Parameter.h"

static const int kGuiMargin = 10;

namespace ofxPreset
{
	class Gui
	{
	public:
		static inline bool BeginWindow(Parameter<bool> & parameter, const ofVec2f & pos, const ofVec2f & size, bool collapse = true);
		static inline bool BeginWindow(const string & name, const ofVec2f & pos, const ofVec2f & size, bool collapse = true, bool * opened = nullptr);
	
		static inline bool EndWindow(ofVec2f & pos, ofVec2f & size);
	
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
