#include "Parameter.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(bool autoUpdating)
		: ofParameter()
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ofParameter<ParameterType> & v, bool autoUpdating)
		: ofParameter(v)
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);

		this->mutableValue = ofParameter::get();
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ParameterType & v, bool autoUpdating)
		: ofParameter(v)
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);

		this->mutableValue = ofParameter::get();
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string& name, const ParameterType & v, bool autoUpdating)
		: ofParameter(name, v)
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);

		this->mutableValue = ofParameter::get();
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating)
		: ofParameter(name, v, min, max)
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);

		this->mutableValue = ofParameter::get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::~Parameter()
	{
		this->setAutoUpdating(false);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::update()
	{
		if (ofParameter::get() != this->mutableValue)
		{
			ofParameter::setWithoutEventNotifications(mutableValue);
		}
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setAutoUpdating(bool autoUpdating)
	{
		if (this->autoUpdating == autoUpdating) return;

		if (autoUpdating)
		{
			ofAddListener(ofEvents().update, this, &Parameter::onUpdate);
			this->addListener(this, &Parameter::onValueChanged);
		}
		else
		{
			ofRemoveListener(ofEvents().update, this, &Parameter::onUpdate);
			this->removeListener(this, &Parameter::onValueChanged);
		}

		this->autoUpdating = autoUpdating;
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isAutoUpdating() const
	{
		return this->autoUpdating;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::onUpdate(ofEventArgs & args)
	{
		this->update();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::onValueChanged(ParameterType & v)
	{
		this->mutableValue = ofParameter::get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType * Parameter<ParameterType>::getRef()
	{
		return &this->mutableValue;
	}
}