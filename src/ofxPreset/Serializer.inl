#include "Serializer.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	nlohmann::json & Serializer::Serialize(nlohmann::json & json, const ofAbstractParameter & parameter)
	{
		const auto name = parameter.getName();
		json[name] = parameter.toString();

		return json;
	}
	
	//--------------------------------------------------------------
	const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofAbstractParameter & parameter)
	{
		const auto name = parameter.getName();
		if (json.count(name))
		{
			string valueString = json[name];
			if (!valueString.empty())
			{
				parameter.fromString(valueString);
			}
		}

		return json;
	}

	//--------------------------------------------------------------
    nlohmann::json & Serializer::Serialize(nlohmann::json & json, const ofParameterGroup & group)
    {
        const auto name = group.getName();
        auto & jsonGroup = name.empty() ? json : json[name];
        for (const auto & parameter : group)
        {
            // Group.
            auto parameterGroup = dynamic_pointer_cast<ofParameterGroup>(parameter);
            if (parameterGroup)
            {
                // Recurse through contents.
                Serializer::Serialize(jsonGroup, *parameterGroup);
                continue;
            }

            // Parameter.
			auto parameterAbstract = dynamic_pointer_cast<ofAbstractParameter>(parameter);
			if (parameterAbstract)
            {
				Serializer::Serialize(jsonGroup, *parameterAbstract);
				continue;
            }
        }

        return jsonGroup;
    }

    //--------------------------------------------------------------
    const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofParameterGroup & group)
    {
        const auto name = group.getName();
        if (!name.empty() && !json.count(name))
        {
            ofLogWarning("Serializer::deserialize") << "Name " << name << " not found in JSON!";
            return json;
        }

        const auto & jsonGroup = name.empty() ? json : json[name];
        for (const auto & parameter : group)
        {
            if (!parameter)
            {
                continue;
            }

            // Group.
			auto parameterGroup = dynamic_pointer_cast<ofParameterGroup>(parameter);
			if (parameterGroup)
			{
				// Recurse through contents.
				Serializer::Deserialize(jsonGroup, *parameterGroup);
				continue;
			}

            // Parameter.
			auto parameterAbstract = dynamic_pointer_cast<ofAbstractParameter>(parameter);
			if (parameterAbstract)
			{
				Serializer::Deserialize(jsonGroup, *parameterAbstract);
			}
        }

        return jsonGroup;
    }

    //--------------------------------------------------------------
    nlohmann::json & Serializer::Serialize(nlohmann::json & json, const ofNode & node, const string & name)
    {
        auto & jsonGroup = name.empty() ? json : json[name];
        ostringstream oss;
        oss << node.getGlobalTransformMatrix();
        jsonGroup["transform"] = oss.str();

        return jsonGroup;
    }
    
    //--------------------------------------------------------------
    const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofNode & node, const string & name)
    {
        const auto & jsonGroup = name.empty() ? json : json[name];
        string valueString = jsonGroup["transform"];
        ofMatrix4x4 transform;
        istringstream iss;
        iss.str(valueString);
        iss >> transform;
        node.setTransformMatrix(transform);

        return jsonGroup;
    }
}
