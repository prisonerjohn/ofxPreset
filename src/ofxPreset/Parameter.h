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
    protected:
        struct Data
        {
        public:
            Data(bool autoUpdating);
            Data(const ofParameter<ParameterType> & parameter, bool autoUpdating);

            void update();
            void setAutoUpdating(bool autoUpdating);

        public: 
            ParameterType mutableValue;
            ofParameter<ParameterType> parameter;
            bool autoUpdating;

        protected:
			ofEventListener onUpdateListener;
			ofEventListener onValueChangedListener;
        };

        shared_ptr<Data> data;

	public:
		Parameter(bool autoUpdating = false);
		Parameter(const ofParameter<ParameterType> & v, bool autoUpdating = false);
		Parameter(const ParameterType & v, bool autoUpdating = false);
		Parameter(const string & name, const ParameterType & v, bool autoUpdating = false);
		Parameter(const string & name, const ParameterType & v, const ParameterType & min, const ParameterType & max, bool autoUpdating = false);
        Parameter(shared_ptr<Data> data);

		void update();

		void setAutoUpdating(bool autoUpdating);
		bool isAutoUpdating() const;

		virtual void setName(const string & name) override;
		virtual string getName() const override;

        virtual string toString() const override;
        virtual void fromString(const string & name) override;
        
        ParameterType * getRef();
		shared_ptr<ofParameter<ParameterType>> getInternal();

        const ParameterType & get() const;
        const ParameterType * operator->() const;
        operator const ParameterType & () const;

        ParameterType getMin() const;
		ParameterType getMax() const;
		
		template<class ListenerClass, typename ListenerMethod>
        void addListener(ListenerClass * listener, ListenerMethod method, int prio = OF_EVENT_ORDER_AFTER_APP);
		template<class ListenerClass, typename ListenerMethod>
        void removeListener(ListenerClass * listener, ListenerMethod method, int prio = OF_EVENT_ORDER_AFTER_APP);
		template<typename... Args>
        ofEventListener newListener(Args...args);

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
		Parameter<ParameterType> & set(const string & name, const ParameterType & v);
		Parameter<ParameterType> & set(const string & name, const ParameterType & v, const ParameterType & min, const ParameterType & max);

		Parameter<ParameterType> & setWithoutEventNotifications(const ParameterType & v);

		void setMin(const ParameterType & min);
		void setMax(const ParameterType & max);

		void setSerializable(bool serializable);
		shared_ptr<ofAbstractParameter> newReference() const;

		void setParent(ofParameterGroup & _parent);
        const ofParameterGroup getFirstParent() const;

		size_t getNumListeners() const;
		const void* getInternalObject() const;
	};
}

#include "Parameter.inl"
