#pragma once

#include "ofMain.h"

// Stolen from ofxRulr, thanks Elliot!
// Syntactic sugar which enables struct-ofParameterGroup
#define PARAM_DECLARE(NAME, ...) bool paramDeclareConstructor \
{ [this] { this->setName(NAME), this->add(__VA_ARGS__); return true; }() };

namespace ofxPreset
{
	template<typename ParameterType>
	class Parameter
		: public ofParameter<ParameterType>
	{
	public:
		Parameter(bool autoUpdating = true);
		Parameter(const ofParameter<ParameterType> & v, bool autoUpdating = true);
		Parameter(const ParameterType & v, bool autoUpdating = true);
		Parameter(const string& name, const ParameterType & v, bool autoUpdating = true);
		Parameter(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating = true);

		virtual ~Parameter();

		void update();

		void setAutoUpdating(bool autoUpdating);
		bool isAutoUpdating() const;

		ParameterType * getRef();

	protected:
		void onUpdate(ofEventArgs & args);
		void onValueChanged(ParameterType & v);

	private:
		// Called from the constructors.
		void setup(bool autoUpdating);

		ParameterType mutableValue;

		bool autoUpdating;
	};
}

#include "Parameter.inl"
