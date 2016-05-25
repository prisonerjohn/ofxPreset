#include "Gui.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	bool Gui::BeginWindow(Parameter<bool> & parameter, const ofVec2f & pos, const ofVec2f & size, bool collapse)
	{
		return Gui::BeginWindow(parameter.getName(), pos, size, collapse, parameter.getRef());
	}
	
	//--------------------------------------------------------------
	bool Gui::BeginWindow(const string & name, const ofVec2f & pos, const ofVec2f & size, bool collapse, bool * opened)
	{
		ImGui::SetNextWindowPos(pos, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowSize(size, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowCollapsed(collapse, ImGuiSetCond_Appearing);
		return ImGui::Begin(name.c_str(), opened, ImGuiWindowFlags_AlwaysAutoResize | (collapse ?  0 : ImGuiWindowFlags_NoCollapse));
	}

	//--------------------------------------------------------------
	bool Gui::EndWindow(ofVec2f & pos, ofVec2f & size)
	{
		pos = ImGui::GetWindowPos();
		size = ImGui::GetWindowSize();
		ImGui::End();

		const auto bounds = ofRectangle(pos, size.x, size.y);
		return bounds.inside(ofGetMouseX(), ofGetMouseY());
	}

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec2f> & parameter)
    {
        return ImGui::SliderFloat2(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x);
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec3f> & parameter)
    {
        return ImGui::SliderFloat3(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x);
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofVec4f> & parameter)
    {
        return ImGui::SliderFloat4(parameter.getName().c_str(), parameter.getRef()->getPtr(), parameter.getMin().x, parameter.getMax().x);
    }

    //--------------------------------------------------------------
    bool Gui::AddParameter(Parameter<ofFloatColor> & parameter)
    {
        return ImGui::ColorEdit4(parameter.getName().c_str(), &(parameter.getRef()->r));
    }

	//--------------------------------------------------------------
	template<typename ParameterType>
	bool Gui::AddParameter(Parameter<ParameterType> & parameter)
	{
		const auto & info = typeid(ParameterType);
		if (info == typeid(float))
		{
			return ImGui::SliderFloat(parameter.getName().c_str(), (float *)parameter.getRef(), parameter.getMin(), parameter.getMax());
		}
		if (info == typeid(int))
		{
			return ImGui::SliderInt(parameter.getName().c_str(), (int *)parameter.getRef(), parameter.getMin(), parameter.getMax());
		}
		if (info == typeid(bool))
		{
			return ImGui::Checkbox(parameter.getName().c_str(), (bool *)parameter.getRef());
		}
		ofLogWarning("Gui::addParameter") << "Could not create GUI element for type " << info.name();
		return false;
	}

	//--------------------------------------------------------------
	bool Gui::AddRange(const string & name, Parameter<float> & parameterMin, Parameter<float> & parameterMax, float speed)
	{
		return ImGui::DragFloatRange2(name.c_str(), parameterMin.getRef(), parameterMax.getRef(), speed, parameterMin.getMin(), parameterMax.getMax());
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
