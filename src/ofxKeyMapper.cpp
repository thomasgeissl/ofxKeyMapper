#include "ofxKeyMapper.h"

ofxKeyMapper::ofxKeyMapper() : _idCounter(0){
	_parameters.setName("parameters");
	_activeParameter.set("on/off", true);
	_activeMappingParameter.set("mapping mode", false);

	_parameters.add(_activeParameter);
	_parameters.add(_activeMappingParameter);
}

void ofxKeyMapper::addParameter(ofParameter <bool> & parameter){
	auto mappable = new ofxKeyMappableBool(parameter, ++_idCounter);

	ofAddListener(mappable->getMapEvent(), this, &ofxKeyMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxKeyMapper::addParameter(ofParameter <float> & parameter){
	auto mappable = new ofxKeyMappableFloat(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxKeyMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxKeyMapper::addParameter(ofParameter <int> & parameter){
	auto mappable = new ofxKeyMappableInt(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxKeyMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxKeyMapper::addParameter(ofParameter <void> & parameter){
	auto mappable = new ofxKeyMappableVoid(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxKeyMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxKeyMapper::addParameters(ofParameterGroup & parameters){
    for(auto parameter : parameters){
        auto type = parameter->type();
        if(type == "11ofParameterIvE"){
            auto typedParameter = parameter->cast<void>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIbE"){
            auto typedParameter = parameter->cast<bool>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIiE"){
            auto typedParameter = parameter->cast<int>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIfE"){
            auto typedParameter = parameter->cast<float>();
            addParameter(typedParameter);
        }
    }
}

bool ofxKeyMapper::addMapping(int key, int id, bool force){
	if(doesMappingExist(key)){
		ofLogWarning("ofxKeyMapper") << "mapping does already exist: (" << key << ", " << id << ")";
		if(force){
			_mapping[key] = id;
			return true;
		}else{
			return false;
		}
	}else{
		_mapping[key] = id;
		ofLogNotice("ofxKeyMapper") << "added mapping: (" << key << ", " << id << ")";
		return true;
	}
}
bool ofxKeyMapper::removeMapping(int key){
	if(doesMappingExist(key)){
		_mapping.erase(_mapping.find(key));
		return true;
	}else{
		ofLogWarning("ofxKeyMapper") << "mapping does not exist. are you sure you are doing right?";
		return false;
	}
}

bool ofxKeyMapper::doesMappingExist(int key){
	return (_mapping.find(key) != _mapping.end());
}

bool ofxKeyMapper::doesMappableExist(int id){
	return (_mappables.find(id) != _mappables.end());
}

int ofxKeyMapper::getMappedId(int key){
	if(doesMappingExist(key)){
		return _mapping[key];
	}else{
//        TODO: better throw an exception instead of returning -1?
		ofLogError("ofxKeyMapper") << "mapping does not exist. returning -1";
		return -1;
	}
}

ofxKeyMappable * ofxKeyMapper::getMappable(int id){
	if(doesMappableExist(id)){
		return _mappables[id];
	}else{
//        TODO: better throw an exception instead of returning nullptr?
		ofLogError("ofxKeyMapper") << "mappable does not exit. returning nullptr";
		return nullptr;
	}
}

ofParameterGroup & ofxKeyMapper::getParameters(){
	return _parameters;
}

void ofxKeyMapper::onMapEvent(int & idOfMappable){
	if(_activeMappingParameter){
		_idOfMappable = idOfMappable;
	}
}

bool ofxKeyMapper::loadMapping(string path){
	ofFile mappingFile;
	ofJson mappingJson;
	mappingFile.open(ofToDataPath(path));
	if(mappingFile.exists()){
        mappingFile >> mappingJson;
        ofLogNotice("ofxKeyMapper") << "successfully loaded mappings " << mappingJson.dump(4);
        _mapping.clear();

        for(auto mapping : mappingJson["mappings"]){
            addMapping(mapping["key"].get<int>(), mapping["id"].get<int>());
        }
	}else{
		ofLogError("ofxKeyMapper") << ofToDataPath(path) << " does not exist";
		return false;
	}
}

bool ofxKeyMapper::saveMapping(string path, bool force){
	ofFile mappingFile;
	mappingFile.open(ofToDataPath(path), ofFile::ReadWrite);
	if(mappingFile.exists() && !force){
		ofLogError("ofxKeyMapper") << ofToDataPath(path) << " already exists.";
		return false;
	}else{
		mappingFile.create();
	}
	ofJson mappingJson;

	mappingJson["mappings"] = ofJson::array();
	for(auto mapping : _mapping){
		int key = mapping.first;
		int id = mapping.second;
        // TODO: add parameter name for better debugging or manually removing entries
		mappingJson["mappings"].push_back({{"key", key}, {"id", id}});
	}
	mappingFile << mappingJson.dump(4);
	mappingFile.close();
	return true;
}

void ofxKeyMapper::keyPressed(int key){
	if(!_activeParameter){
		return;
	}

	if(_activeMappingParameter){
		if(_idOfMappable != -1){
			addMapping(key, _idOfMappable);
		_idOfMappable = -1;
		}
	}
	if(doesMappingExist(key)){
			auto id = getMappedId(key);
			if(doesMappableExist(id)){
					getMappable(id)->map();
			}
	}
}
