#include "Parameter.h"

namespace ofxPreset
{
#pragma mark Parameter::Data
    //--------------------------------------------------------------
    template<typename ParameterType>
    Parameter<ParameterType>::Data::Data(bool autoUpdate)
        : autoUpdating(false)
    {
        this->setAutoUpdating(autoUpdate);
        this->parameter.addListener(this, &Parameter::Data::onValueChanged);
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    Parameter<ParameterType>::Data::Data(const ofParameter<ParameterType> & v, bool autoUpdate)
        : parameter(v)
        , mutableValue(v)
        , autoUpdating(false)
    {
        this->setAutoUpdating(autoUpdate);
        this->parameter.addListener(this, &Parameter::Data::onValueChanged);
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    Parameter<ParameterType>::Data::~Data()
    {
        this->setAutoUpdating(false);
        this->parameter.removeListener(this, &Parameter::Data::onValueChanged);
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    void Parameter<ParameterType>::Data::update()
    {
        if (this->parameter.get() != this->mutableValue)
        {
            this->parameter.setWithoutEventNotifications(this->mutableValue);
        }
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    void Parameter<ParameterType>::Data::setAutoUpdating(bool autoUpdating)
    {
        if (this->autoUpdating == autoUpdating) return;

        if (autoUpdating)
        {
            ofAddListener(ofEvents().update, this, &Parameter::Data::onUpdate);
        }
        else
        {
            ofRemoveListener(ofEvents().update, this, &Parameter::Data::onUpdate);
        }

        this->autoUpdating = autoUpdating;
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    void Parameter<ParameterType>::Data::onUpdate(ofEventArgs & args)
    {
        this->update();
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    void Parameter<ParameterType>::Data::onValueChanged(ParameterType & v)
    {
        this->mutableValue = this->parameter.get();
    }
    
#pragma mark Parameter
    //--------------------------------------------------------------
	template<typename ParameterType>
    Parameter<ParameterType>::Parameter(bool autoUpdating)
        : data(make_shared<Data>(autoUpdating))
    {}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ofParameter<ParameterType> & v, bool autoUpdating)
        : data(make_shared<Data>(ofParameter<ParameterType>(v), autoUpdating))
    {}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const ParameterType & v, bool autoUpdating)
        : data(make_shared<Data>(ofParameter<ParameterType>(v), autoUpdating))
    {}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string & name, const ParameterType & v, bool autoUpdating)
        : data(make_shared<Data>(ofParameter<ParameterType>(name, v), autoUpdating))
    {}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(const string & name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating)
        : data(make_shared<Data>(ofParameter<ParameterType>(name, v, min, max), autoUpdating))
    {}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::Parameter(shared_ptr<Data> data)
        : data(data)
    {}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::update()
	{
        this->data->update();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setAutoUpdating(bool autoUpdating)
	{
        this->data->setAutoUpdating(autoUpdating);
	}
	
	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isAutoUpdating() const
	{
		return this->data->autoUpdating;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType * Parameter<ParameterType>::getRef()
	{
		return &this->data->mutableValue;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	shared_ptr<ofParameter<ParameterType>> Parameter<ParameterType>::getInternal()
	{
		return dynamic_pointer_cast<ofParameter<ParameterType>>(this->data->parameter.newReference());
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType & Parameter<ParameterType>::get() const
    {
		return this->data->parameter.get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType * Parameter<ParameterType>::operator->() const
    {
		return this->data->parameter.operator->();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType>::operator const ParameterType & () const
    {
		return (ParameterType &)this->data->parameter.get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setName(const string & name)
    {
		this->data->parameter.setName(name);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	string Parameter<ParameterType>::getName() const
    {
		return this->data->parameter.getName();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::getMin() const
    {
		return this->data->parameter.getMin();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::getMax() const
    {
		return this->data->parameter.getMax();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	string Parameter<ParameterType>::toString() const
    {
		return this->data->parameter.toString();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::fromString(const string & name)
    {
		return this->data->parameter.fromString(name);
	}

    //--------------------------------------------------------------
    template<typename ParameterType>
    template<class ListenerClass, typename ListenerMethod>
    void Parameter<ParameterType>::addListener(ListenerClass * listener, ListenerMethod method, int prio) 
    {
        this->data->parameter.addListener(listener, method, prio);
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    template<class ListenerClass, typename ListenerMethod>
    void Parameter<ParameterType>::removeListener(ListenerClass * listener, ListenerMethod method, int prio) 
    {
        this->data->parameter.addListener(listener, method, prio);
    }

    //--------------------------------------------------------------
    template<typename ParameterType>
    template<typename... Args>
    ofEventListener Parameter<ParameterType>::newListener(Args...args) 
    {
        return this->data->parameter.newListener(args...);
    }

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::enableEvents()
    {
		this->data->parameter->enableEvents();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::disableEvents()
    {
		this->data->parameter->disableEvents();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isSerializable() const
    {
		return this->data->parameter.isSerializable();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Parameter<ParameterType>::isReadOnly() const
    {
		return this->data->parameter.isReadOnly();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::makeReferenceTo(Parameter<ParameterType> & mom)
    {
		this->data->parameter.makeReference(mom.parameter);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator=(const Parameter<ParameterType> & v)
    {
		this->data->parameter = v.parameter;
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const ParameterType & Parameter<ParameterType>::operator=(const ParameterType & v)
    {
		this->data->parameter = v;
		return this->get();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::operator++(int v)
    {
		return this->data->parameter.operator++(v);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator++()
    {
		this->data->parameter.operator++();
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	ParameterType Parameter<ParameterType>::operator--(int v)
    {
		return this->data->parameter.operator--(v);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator--()
    {
		this->data->parameter.operator--();
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator+=(const OtherType & v)
    {
		this->data->parameter.operator+(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator-=(const OtherType & v)
    {
		this->data->parameter.operator-=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator*=(const OtherType & v){
		this->data->parameter.operator*=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator/=(const OtherType & v)
    {
		this->data->parameter.operator/=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator%=(const OtherType & v)
    {
		this->data->parameter.operator%=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator&=(const OtherType & v)
    {
		this->data->parameter.operator&=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator|=(const OtherType & v)
    {
		this->data->parameter.operator|=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator^=(const OtherType & v)
    {
		this->data->parameter.operator^=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator<<=(const OtherType & v)
    {
		this->data->parameter.operator<<=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	template<typename OtherType>
	Parameter<ParameterType> & Parameter<ParameterType>::operator>>=(const OtherType & v)
    {
		this->data->parameter.operator>>=(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const ParameterType & v)
    {
		this->data->parameter.set(v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const string & name, const ParameterType & v)
    {
		this->data->parameter.set(name, v);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	Parameter<ParameterType> & Parameter<ParameterType>::set(const string & name, const ParameterType & v, const ParameterType & min, const ParameterType & max)
    {
		this->data->parameter.set(name, v, min, max);
		return *this;
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
    Parameter<ParameterType> & Parameter<ParameterType>::setWithoutEventNotifications(const ParameterType & v)
    {
        this->data->parameter.setWithoutEventNotifications(v);
        return *this;
    }

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setMin(const ParameterType & min)
    {
		this->data->parameter.setMin(min);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setMax(const ParameterType & max)
    {
		this->data->parameter.setMax(max);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setSerializable(bool serializable)
    {
		this->data->parameter.setSerializable(serializable);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	shared_ptr<ofAbstractParameter> Parameter<ParameterType>::newReference() const
    {
		return make_shared<Parameter<ParameterType>>(this->data);
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	void Parameter<ParameterType>::setParent(ofParameterGroup & parent)
    {
		this->data->parameter.setParent(parent);
	}

    //--------------------------------------------------------------
    template<typename ParameterType>
    const ofParameterGroup Parameter<ParameterType>::getFirstParent() const
    {
        return this->data->parameter.getFirstParent();
    }

	//--------------------------------------------------------------
	template<typename ParameterType>
	size_t Parameter<ParameterType>::getNumListeners() const
    {
		return this->data->parameter.getNumListeners();
	}

	//--------------------------------------------------------------
	template<typename ParameterType>
	const void * Parameter<ParameterType>::getInternalObject() const
    {
        return this->data.get();
	}
}
