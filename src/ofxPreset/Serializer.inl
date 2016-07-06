#include "Serializer.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	template<typename DataType>
	nlohmann::json & Serializer::Serialize(nlohmann::json & json, const vector<DataType> & values, const string & name)
	{
		auto & jsonGroup = name.empty() ? json : json[name];
		
		for (const auto & val : values)
		{
			ostringstream oss;
			oss << val;
			jsonGroup.push_back(oss.str());
		}

		return jsonGroup;
	}
	
	//--------------------------------------------------------------
	template<typename DataType>
	const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, vector<DataType> & values, const string & name)
	{
		if (!name.empty() && !json.count(name))
		{
			ofLogWarning("Serializer::Deserialize") << "Name " << name << " not found in JSON!";
			return json;
		}

		const auto & jsonGroup = name.empty() ? json : json[name];
		values.clear();

		for (const auto & jsonValue : jsonGroup)
		{	
			istringstream iss;
			iss.str(jsonValue);
			DataType val;
			iss >> val;
			values.push_back(val);
		}

		return jsonGroup;
	}
	
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
            ofLogWarning("Serializer::Deserialize") << "Name " << name << " not found in JSON!";
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
	nlohmann::json & Serializer::Serialize(nlohmann::json & json, const ofEasyCam & easyCam, const string & name)
	{
		auto & jsonGroup = Serializer::Serialize(json, (ofCamera &)easyCam, name);

		// Need to remove const qualifier because some getters are not const.
		// Can be removed if/when this PR goes through: https://github.com/openframeworks/openFrameworks/pull/5126
		auto & mutableCam = const_cast<ofEasyCam &>(easyCam);

		ostringstream oss;
		oss << mutableCam.getTarget().getPosition();
		jsonGroup["target"] = oss.str();
		jsonGroup["distance"] = easyCam.getDistance();
		jsonGroup["drag"] = easyCam.getDrag();
		jsonGroup["mouseInputEnabled"] = mutableCam.getMouseInputEnabled();
		jsonGroup["mouseMiddleButtonEnabled"] = mutableCam.getMouseMiddleButtonEnabled();
		jsonGroup["translationKey"] = mutableCam.getTranslationKey();

		return jsonGroup;
	}

	//--------------------------------------------------------------
	const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofEasyCam & easyCam, const string & name)
	{
		if (!name.empty() && !json.count(name))
		{
			ofLogWarning("Serializer::Deserialize") << "Name " << name << " not found in JSON!";
			return json;
		}

		easyCam.setAutoDistance(false);

		const auto & jsonGroup = name.empty() ? json : json[name];

		ofVec3f target;
		istringstream iss;
		iss.str(jsonGroup["target"]);
		iss >> target;
		easyCam.setTarget(target);
		easyCam.setDistance(jsonGroup["distance"]);
		easyCam.setDrag(jsonGroup["drag"]);
		jsonGroup["mouseInputEnabled"] ? easyCam.enableMouseInput() : easyCam.disableMouseInput();
		jsonGroup["mouseMiddleButtonEnabled"] ? easyCam.enableMouseMiddleButton() : easyCam.disableMouseMiddleButton();
		int translationKey = jsonGroup["translationKey"];
		easyCam.setTranslationKey(translationKey);

		Serializer::Deserialize(jsonGroup, (ofCamera &)easyCam);

		return jsonGroup;
	}

	//--------------------------------------------------------------
	nlohmann::json & Serializer::Serialize(nlohmann::json & json, const ofCamera & camera, const string & name)
	{
		auto & jsonGroup = Serializer::Serialize(json, (ofNode &)camera, name);

		jsonGroup["fov"] = camera.getFov();
		jsonGroup["nearClip"] = camera.getNearClip();
		jsonGroup["farClip"] = camera.getFarClip();
		ostringstream oss;
		oss << camera.getLensOffset();
		jsonGroup["lensOffset"] = oss.str();
		jsonGroup["aspectRatio"] = camera.getAspectRatio();
		jsonGroup["forceAspectRatio"] = camera.getForceAspectRatio();
		jsonGroup["ortho"] = camera.getOrtho();

		return jsonGroup;
	}

	//--------------------------------------------------------------
	const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofCamera & camera, const string & name)
	{
		if (!name.empty() && !json.count(name))
		{
			ofLogWarning("Serializer::Deserialize") << "Name " << name << " not found in JSON!";
			return json;
		}
		
		const auto & jsonGroup = name.empty() ? json : json[name];

		camera.setFov(jsonGroup["fov"]);
		camera.setNearClip(jsonGroup["nearClip"]);
		camera.setFarClip(jsonGroup["farClip"]);
		ofVec2f lensOffset;
		istringstream iss;
		iss.str(jsonGroup["lensOffset"]);
		iss >> lensOffset;
		camera.setLensOffset(lensOffset);
		camera.setForceAspectRatio(jsonGroup["forceAspectRatio"]);
		if (camera.getForceAspectRatio())
		{
			camera.setAspectRatio(jsonGroup["aspectRatio"]);
		}
		jsonGroup["ortho"] ? camera.enableOrtho() : camera.disableOrtho();

		Serializer::Deserialize(jsonGroup, (ofNode &)camera);

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
		if (!name.empty() && !json.count(name))
		{
			ofLogWarning("Serializer::Deserialize") << "Name " << name << " not found in JSON!";
			return json;
		}

		const auto & jsonGroup = name.empty() ? json : json[name];

		ofMatrix4x4 transform;
		istringstream iss;
		iss.str(jsonGroup["transform"]);
		iss >> transform;
		node.setTransformMatrix(transform);

		return jsonGroup;
    }
}
