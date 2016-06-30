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
	    : public ofAbstractParameter
	{
	public:
		Parameter(bool autoUpdating = false);
		Parameter(const ofParameter<ParameterType> & v, bool autoUpdating = false);
		Parameter(const ParameterType & v, bool autoUpdating = false);
		Parameter(const string& name, const ParameterType & v, bool autoUpdating = false);
		Parameter(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating = false);

		virtual ~Parameter();

		void update();

		void setAutoUpdating(bool autoUpdating);
		bool isAutoUpdating() const;

		ParameterType * getRef();
		const ParameterType & get() const;
		const ParameterType * operator->() const;
		operator const ParameterType & () const;

		void setName(const string & name);
		string getName() const;

		ParameterType getMin() const;

		ParameterType getMax() const;


		std::string toString() const;
		void fromString(const std::string & name);

		template<class ListenerClass, typename ListenerMethod>
		void addListener(ListenerClass * listener, ListenerMethod method, int prio=OF_EVENT_ORDER_AFTER_APP){
			parameter.addListener(listener, method, prio);
		}

		template<class ListenerClass, typename ListenerMethod>
		void removeListener(ListenerClass * listener, ListenerMethod method, int prio=OF_EVENT_ORDER_AFTER_APP){
			parameter.addListener(listener, method, prio);
		}

		template<typename... Args>
		ofEventListener newListener(Args...args) {
			return parameter.newListener(args...);
		}

		void enableEvents();
		void disableEvents();
		bool isSerializable() const;
		bool isReadOnly() const;

		void makeReferenceTo(Parameter<ParameterType> & mom);

		Parameter<ParameterType> & operator=(const Parameter<ParameterType> & v);
		const ParameterType & operator=(const ParameterType & v);

		ParameterType operator++(int v);
		Parameter<ParameterType> & operator++();

		ParameterType operator--(int v);
		Parameter<ParameterType> & operator--();

		template<typename OtherType>
		Parameter<ParameterType> & operator+=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator-=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator*=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator/=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator%=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator&=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator|=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator^=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator<<=(const OtherType & v);
		template<typename OtherType>
		Parameter<ParameterType> & operator>>=(const OtherType & v);


		Parameter<ParameterType> & set(const ParameterType & v);
		Parameter<ParameterType> & set(const string& name, const ParameterType & v);
		Parameter<ParameterType> & set(const string& name, const ParameterType & v, const ParameterType & min, const ParameterType & max);

		Parameter<ParameterType> & setWithoutEventNotifications(const ParameterType & v);

		void setMin(const ParameterType & min);
		void setMax(const ParameterType & max);

		void setSerializable(bool serializable);
		shared_ptr<ofAbstractParameter> newReference() const;

		void setParent(ofParameterGroup & _parent);

		const ofParameterGroup getFirstParent() const{
			return parameter.getFirstParent();
		}

		size_t getNumListeners() const;
		const void* getInternalObject() const;

	protected:
		void onUpdate(ofEventArgs & args);
		void onValueChanged(ParameterType & v);

	private:
		// Called from the constructors.
		void setup(bool autoUpdating);
		Parameter(ofParameter<ParameterType> && parameter, bool autoUpdating);

		ParameterType mutableValue;
		ofParameter<ParameterType> parameter;

		bool autoUpdating;
	};
}

#include "Parameter.inl"
