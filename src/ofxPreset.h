#pragma once

#include "ofxPreset/Gui.h"
#include "ofxPreset/Serializer.h"

// Stolen from ofxRulr, thanks Elliot!
// Syntactic sugar which enables struct-ofParameterGroup
#define PARAM_DECLARE(NAME, ...) bool paramDeclareConstructor \
{ [this] { this->setName(NAME), this->add(__VA_ARGS__); return true; }() };
