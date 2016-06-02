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

		ostringstream oss;
		oss << easyCam.getTarget().getPosition();
		jsonGroup["target"] = oss.str();
		jsonGroup["distance"] = easyCam.getDistance();
		jsonGroup["drag"] = easyCam.getDrag();
		jsonGroup["mouseInputEnabled"] = easyCam.getMouseInputEnabled();
		jsonGroup["mouseMiddleButtonEnabled"] = easyCam.getMouseMiddleButtonEnabled();
		jsonGroup["translationKey"] = easyCam.getTranslationKey();

		return jsonGroup;
	}

	//--------------------------------------------------------------
	const nlohmann::json & Serializer::Deserialize(const nlohmann::json & json, ofEasyCam & easyCam, const string & name)
	{
		const auto & jsonGroup = Serializer::Deserialize(json, (ofCamera &)easyCam, name);

		easyCam.setAutoDistance(false);

		try
		{
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
		}
		catch (const domain_error & err)
		{
			ofLogError("Serializer::Deserialize") << err.what();
		}

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
		const auto & jsonGroup = Serializer::Deserialize(json, (ofNode &)camera, name);

		try
		{
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
		}
		catch (const domain_error & err)
		{
			ofLogError("Serializer::Deserialize") << err.what();
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

		try
		{
			ofMatrix4x4 transform;
			istringstream iss;
			iss.str(jsonGroup["transform"]);
			iss >> transform;
			node.setTransformMatrix(transform);
		}
		catch (const domain_error & err)
		{
			ofLogError("Serializer::Deserialize") << err.what();
		}

        return jsonGroup;
    }
}
