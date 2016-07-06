#pragma once

#include "ofMain.h"

namespace ofxPreset
{
    class Serializer
    {
    public:
		template<typename DataType>
		static inline nlohmann::json & Serialize(nlohmann::json & json, const vector<DataType> & values, const string & name = "");
		template<typename DataType>
		static inline const nlohmann::json & Deserialize(const nlohmann::json & json, vector<DataType> & values, const string & name = "");

		static inline nlohmann::json & Serialize(nlohmann::json & json, const ofAbstractParameter & parameter);
		static inline const nlohmann::json & Deserialize(const nlohmann::json & json, ofAbstractParameter & parameter);

        static inline nlohmann::json & Serialize(nlohmann::json & json, const ofParameterGroup & group);
        static inline const nlohmann::json & Deserialize(const nlohmann::json & json, ofParameterGroup & group);

		static inline nlohmann::json & Serialize(nlohmann::json & json, const ofEasyCam & easyCam, const string & name = "");
		static inline const nlohmann::json & Deserialize(const nlohmann::json & json, ofEasyCam & easyCam, const string & name = "");

		static inline nlohmann::json & Serialize(nlohmann::json & json, const ofCamera & camera, const string & name = "");
		static inline const nlohmann::json & Deserialize(const nlohmann::json & json, ofCamera & camera, const string & name = "");

        static inline nlohmann::json & Serialize(nlohmann::json & json, const ofNode & node, const string & name = "");
        static inline const nlohmann::json & Deserialize(const nlohmann::json & json, ofNode & node, const string & name = "");
	};
}

#include "Serializer.inl"
