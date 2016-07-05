#include "Gui.h"

namespace ofxPreset
{
    //--------------------------------------------------------------
    Gui::Settings::Settings()
        : windowPos(kGuiMargin, kGuiMargin)
        , windowSize(ofVec2f::zero())
        , windowBlock(false)
        , mouseOverGui(false)
    {}
    
    //--------------------------------------------------------------
	void Gui::SetNextWindow(Settings & settings)
	{
		settings.windowSize.x = 0;
		settings.windowPos.y += settings.windowSize.y + kGuiMargin;
	}

	//--------------------------------------------------------------
	bool Gui::BeginWindow(Parameter<bool> & parameter, Settings & settings, bool collapse)
	{
        return Gui::BeginWindow(parameter.getName(), settings, collapse, parameter.getRef());
	}
	
	//--------------------------------------------------------------
	bool Gui::BeginWindow(const string & name, Settings & settings, bool collapse, bool * opened)
	{
        if (settings.windowBlock)
        {
            ofLogWarning("Gui::BeginWindow") << "Already inside a window block!";
            return false;
        }

        settings.windowBlock = true;
        
        ImGui::SetNextWindowPos(settings.windowPos, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowSize(settings.windowSize, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowCollapsed(collapse, ImGuiSetCond_Appearing);
		return ImGui::Begin(name.c_str(), opened, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | (collapse ?  0 : ImGuiWindowFlags_NoCollapse));
	}

	//--------------------------------------------------------------
	void Gui::EndWindow(Settings & settings)
	{
        if (!settings.windowBlock)
        {
            ofLogWarning("Gui::EndWindow") << "Not inside a window block!";
            return;
        }

        settings.windowBlock = false;
        
        settings.windowPos = ImGui::GetWindowPos();
		settings.windowSize = ImGui::GetWindowSize();
		ImGui::End();

		const auto bounds = ofRectangle(settings.windowPos, settings.windowSize.x, settings.windowSize.y);
		settings.mouseOverGui |= bounds.inside(ofGetMouseX(), ofGetMouseY());
	}

	//--------------------------------------------------------------
	void Gui::AddGroup(ofParameterGroup & group, Settings & settings)
	{
        bool prevWindowBlock = settings.windowBlock;
        if (settings.windowBlock)
        {
            if (!ImGui::CollapsingHeader(group.getName().c_str(), nullptr, true, true))
            {
                return;
            }
        }
        else
        {
            Gui::BeginWindow(group.getName().c_str(), settings);
		}

		for (auto parameter : group)
		{
			// Group.
			auto parameterGroup = dynamic_pointer_cast<ofParameterGroup>(parameter);
			if (parameterGroup)
			{
				// Recurse through contents.
				Gui::AddGroup(*parameterGroup, settings);
				continue;
			}

			// Parameter, try everything we know how to handle.
			auto parameterVec2f = dynamic_pointer_cast<Parameter<ofVec2f>>(parameter);
			if (parameterVec2f)
			{
				Gui::AddParameter(*parameterVec2f);
				continue;
			}
			auto parameterVec3f = dynamic_pointer_cast<Parameter<ofVec3f>>(parameter);
			if (parameterVec3f)
			{
				Gui::AddParameter(*parameterVec3f);
				continue;
			}
			auto parameterVec4f = dynamic_pointer_cast<Parameter<ofVec4f>>(parameter);
			if (parameterVec4f)
			{
				Gui::AddParameter(*parameterVec4f);
				continue;
			}
			auto parameterFloatColor = dynamic_pointer_cast<Parameter<ofFloatColor>>(parameter);
			if (parameterFloatColor)
			{
				Gui::AddParameter(*parameterFloatColor);
				continue;
			}
			auto parameterFloat = dynamic_pointer_cast<Parameter<float>>(parameter);
			if (parameterFloat)
			{
				Gui::AddParameter(*parameterFloat);
				continue;
			}
			auto parameterInt = dynamic_pointer_cast<Parameter<int>>(parameter);
			if (parameterInt)
			{
				Gui::AddParameter(*parameterInt);
				continue;
			}
			auto parameterBool = dynamic_pointer_cast<Parameter<bool>>(parameter);
			if (parameterBool)
			{
				Gui::AddParameter(*parameterBool);
				continue;
			}

			ofLogWarning("Gui::AddGroup") << "Could not create GUI element for parameter " << parameter->getName();
		}

        // Only end window if we created it.
        if (settings.windowBlock && !prevWindowBlock)
		{
            Gui::EndWindow(settings);
		}
	}

	//--------------------------------------------------------------
	bool Gui::AddParameter(Parameter<glm::tvec2<int>> & parameter)
	{
		if (ImGui::SliderInt2(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	bool Gui::AddParameter(Parameter<glm::tvec3<int>> & parameter)
	{
		if (ImGui::SliderInt3(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	bool Gui::AddParameter(Parameter<glm::tvec4<int>> & parameter)
	{
		if (ImGui::SliderInt4(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
	}

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<glm::vec2> & parameter)
    {
        if (ImGui::SliderFloat2(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
        {
            parameter.update();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<glm::vec3> & parameter)
    {
        if (ImGui::SliderFloat3(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
        {
            parameter.update();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<glm::vec4> & parameter)
    {
        if (ImGui::SliderFloat4(parameter.getName().c_str(), glm::value_ptr(*parameter.getRef()), parameter.getMin().x, parameter.getMax().x))
        {
            parameter.update();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec2f> & parameter)
    {
		if (ImGui::SliderFloat2(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec3f> & parameter)
    {
		if (ImGui::SliderFloat3(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec4f> & parameter)
    {
		if (ImGui::SliderFloat4(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x))
		{
			parameter.update();
			return true;
		}
		return false;
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofFloatColor> & parameter)
    {
		if (ImGui::ColorEdit4(parameter.getName().c_str(), &(parameter.getRef()->r)))
		{
			parameter.update();
			return true;
		}
		return false;
    }

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Gui::AddParameter(Parameter<ParameterType> & parameter)
	{
		const auto & info = typeid(ParameterType);
		if (info == typeid(float))
		{
			if (ImGui::SliderFloat(parameter.getName().c_str(), (float *)parameter.getRef(), parameter.getMin(), parameter.getMax()))
			{
				parameter.update();
				return true;
			}
			return false;
		}
		if (info == typeid(int))
		{
			if (ImGui::SliderInt(parameter.getName().c_str(), (int *)parameter.getRef(), parameter.getMin(), parameter.getMax()))
			{
				parameter.update();
				return true;
			}
			return false;
		}
		if (info == typeid(bool))
		{
			if (ImGui::Checkbox(parameter.getName().c_str(), (bool *)parameter.getRef()))
			{
				parameter.update();
				return true;
			}
			return false;
		}
		ofLogWarning("Gui::AddParameter") << "Could not create GUI element for type " << info.name();
		return false;
	}

	//--------------------------------------------------------------
	bool Gui::AddRange(const string & name, Parameter<float> & parameterMin, Parameter<float> & parameterMax, float speed)
	{
		if (ImGui::DragFloatRange2(name.c_str(), parameterMin.getRef(), parameterMax.getRef(), speed, parameterMin.getMin(), parameterMax.getMax()))
		{
			parameterMin.update();
			parameterMax.update();
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------
	void Gui::AddImage(ofBaseHasTexture & hasTexture, const ofVec2f & size)
	{
		Gui::AddImage(hasTexture.getTexture(), size);
	}
	
	//--------------------------------------------------------------
	void Gui::AddImage(ofTexture & texture, const ofVec2f & size)
	{
		ImTextureID textureID = (ImTextureID)(uintptr_t)texture.texData.textureID;
		ImGui::Image(textureID, size);
	}
}
