#pragma once
#include "ofxKeyMappable.h"

class ofxKeyMappableFloat : public ofxKeyMappable {
public:
    ofxKeyMappableFloat(ofParameter<float> & parameter, int id) : ofxKeyMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxKeyMappableFloat::notify);
    }
    void map(){
        _parameter = _parameter == _parameter.getMin() ? _parameter.getMax() : _parameter.getMin();
    }
    void notify(float & value){
        _mapEvent.notify(_id);
    }
    ofParameter<float> _parameter;
};
