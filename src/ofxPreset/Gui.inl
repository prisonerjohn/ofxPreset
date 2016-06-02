#include "Gui.h"

namespace ofxPreset
{
	//--------------------------------------------------------------
	void Gui::SetNextWindow(GuiSettings & settings)
	{
		settings.windowSize.x = 0;
		settings.windowPos.y += settings.windowSize.y + kGuiMargin;
	}

	//--------------------------------------------------------------
	bool Gui::BeginWindow(Parameter<bool> & parameter, const GuiSettings & settings, bool collapse)
	{
		return Gui::BeginWindow(parameter.getName(), settings, collapse, parameter.getRef());
	}
	
	//--------------------------------------------------------------
	bool Gui::BeginWindow(const string & name, const GuiSettings & settings, bool collapse, bool * opened)
	{
		ImGui::SetNextWindowPos(settings.windowPos, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowSize(settings.windowSize, ImGuiSetCond_Appearing);
		ImGui::SetNextWindowCollapsed(collapse, ImGuiSetCond_Appearing);
		return ImGui::Begin(name.c_str(), opened, ImGuiWindowFlags_AlwaysAutoResize | (collapse ?  0 : ImGuiWindowFlags_NoCollapse));
	}

	//--------------------------------------------------------------
	void Gui::EndWindow(GuiSettings & settings)
	{
		settings.windowPos = ImGui::GetWindowPos();
		settings.windowSize = ImGui::GetWindowSize();
		ImGui::End();

		const auto bounds = ofRectangle(settings.windowPos, settings.windowSize.x, settings.windowSize.y);
		settings.mouseOverGui |= bounds.inside(ofGetMouseX(), ofGetMouseY());
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
