## ofxPreset
A collection of classes for working with openFrameworks app parameters.
* `ofxPreset::Parameter` is an extension of `ofParameter` with access to a value reference, making it easier to use in GUI systems like [ofxImGui](https://github.com/jvcleave/ofxImGui/) and [ofxCvGui](https://github.com/elliotwoods/ofxCvGui)
* `ofxPreset::Serializer` contains helper methods for serializing/deserializing different objects to JSON. This currently includes `ofParameter` (and `ofParameterGroup`), and `ofNode`. It uses the [nlohmann::json](https://github.com/nlohmann/json) library that ships with OF. 
* `ofxPreset::Gui` contains helper methods for adding `ofxPreset::Parameter` objects to ImGui. Using this class requires that [ofxImGui](https://github.com/jvcleave/ofxImGui/) be added to your project.

A lot of the concepts here (and some of the code) come from [ofxRulr](https://github.com/elliotwoods/ofxRulr), but have been adapted to require less external dependencies and to use [ofxImGui](https://github.com/jvcleave/ofxImGui/) instead of [ofxCvGui](https://github.com/elliotwoods/ofxCvGui) (sorry Elliot!).
