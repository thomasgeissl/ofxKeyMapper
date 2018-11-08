#pragma once
#include "ofxKeyMappable.h"

class ofxKeyMappableBool : public ofxKeyMappable {
public:
    ofxKeyMappableBool(ofParameter <bool> & parameter, int id) : ofxKeyMappable(id), _parameter(parameter){
        _parameter.addListener(this, &ofxKeyMappableBool::notify);
    }
    void map(){
        _parameter = !_parameter;
    }
    void notify(bool & value){
        _mapEvent.notify(_id);
    }
    ofParameter<bool> _parameter;
};
