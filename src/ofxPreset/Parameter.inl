#include "Parameter.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(bool autoUpdating)
	{
		this->setup(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ofParameter<ParameterType> & v, bool autoUpdating)
	:parameter(v)
	,mutableValue(v)
	{
		this->setup(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ParameterType & v, bool autoUpdating)
	:parameter(v)
	,mutableValue(v)
	{
		this->setup(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string& name, const ParameterType & v, bool autoUpdating)
	:parameter(name, v)
	,mutableValue(v)
	{
		this->setup(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating)
	:parameter(name, v, min, max)
	,mutableValue(v)
	{
		this->setup(autoUpdating);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(ofParameter<ParameterType> && parameter, bool autoUpdating)
	:parameter(parameter)
	,mutableValue(parameter.get())
	{
		this->setup(autoUpdating);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::~Parameter()
	{
		this->setAutoUpdating(false);

		this->removeListener(this, &Parameter::onValueChanged);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setup(bool autoUpdating)
	{
		this->autoUpdating = false;
		this->setAutoUpdating(autoUpdating);
		this->addListener(this, &Parameter::onValueChanged);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::update()
	{
		if (get() != this->mutableValue)
		{
			setWithoutEventNotifications(mutableValue);
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
		}
		else
		{
			ofRemoveListener(ofEvents().update, this, &Parameter::onUpdate);
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
		this->mutableValue = get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType * Parameter<ParameterType>::getRef()
	{
		return &this->mutableValue;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType & Parameter<ParameterType>::get() const{
		return this->parameter.get();
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType * Parameter<ParameterType>::operator->() const{
		return this->parameter.operator->();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::operator const ParameterType & () const{
		return (ParameterType&)this->parameter;
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setName(const string & name){
		this->parameter.setName(name);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	string Parameter<ParameterType>::getName() const{
		return this->parameter.getName();
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::getMin() const{
		return this->parameter.getMin();
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::getMax() const{
		return this->parameter.getMax();
	}



	//--------------------------------------------------------------
	template<typename ParameterType>
	std::string Parameter<ParameterType>::toString() const{
		return this->parameter.toString();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::fromString(const std::string & name){
		return this->parameter.fromString(name);
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::enableEvents(){
		this->parameter->enableEvents();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::disableEvents(){
		this->parameter->disableEvents();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isSerializable() const{
		return this->parameter.isSerializable();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isReadOnly() const{
		return this->parameter.isReadOnly();
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::makeReferenceTo(Parameter<ParameterType> & mom){
		this->parameter.makeReference(mom.parameter);
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator=(const Parameter<ParameterType> & v){
		this->parameter = v.parameter;
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType & Parameter<ParameterType>::operator=(const ParameterType & v){
		this->parameter = v;
		return get();
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::operator++(int v){
		return this->parameter.operator++(v);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator++(){
		this->parameter.operator++();
		return *this;
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::operator--(int v){
		return this->parameter.operator--(v);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator--(){
		this->parameter.operator--();
		return *this;
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator+=(const OtherType & v){
		this->parameter.operator+(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator-=(const OtherType & v){
		this->parameter.operator-=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator*=(const OtherType & v){
		this->parameter.operator*=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator/=(const OtherType & v){
		this->parameter.operator/=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator%=(const OtherType & v){
		this->parameter.operator%=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator&=(const OtherType & v){
		this->parameter.operator&=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator|=(const OtherType & v){
		this->parameter.operator|=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator^=(const OtherType & v){
		this->parameter.operator^=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator<<=(const OtherType & v){
		this->parameter.operator<<=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator>>=(const OtherType & v){
		this->parameter.operator>>=(v);
		return *this;
	}



	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const ParameterType & v){
		this->parameter.set(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const string& name, const ParameterType & v){
		this->parameter.set(name, v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max){
		this->parameter.set(name, v, min, max);
		return *this;
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::setWithoutEventNotifications(const ParameterType & v){
		this->parameter.setWithoutEventNotifications(v);
		return *this;
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setMin(const ParameterType & min){
		this->parameter.setMin(min);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setMax(const ParameterType & max){
		this->parameter.setMax(max);
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setSerializable(bool serializable){
		this->parameter.setSerializable(serializable);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	shared_ptr<ofAbstractParameter> Parameter<ParameterType>::newReference() const{
		ofParameter<ParameterType> newParameter(this->parameter);
		return shared_ptr<Parameter<ParameterType>>(new Parameter<ParameterType>(std::move(newParameter), this->autoUpdating));
	}


	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setParent(ofParameterGroup & _parent){
		this->parameter.setParent(_parent);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	size_t Parameter<ParameterType>::getNumListeners() const{
		return this->parameter.getNumListeners();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const void* Parameter<ParameterType>::getInternalObject() const{
		return this->parameter.getInternalObject();
	}
}
