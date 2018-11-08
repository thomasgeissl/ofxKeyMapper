#pragma once
#include "ofxKeyMappable.h"

class ofxKeyMappableInt : public ofxKeyMappable {
public:
    ofxKeyMappableInt(ofParameter<int> & parameter, int id) : ofxKeyMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxKeyMappableInt::notify);
    }
    void map(){
        _parameter = _parameter == _parameter.getMin() ? _parameter.getMax() : _parameter.getMin();
    }
    void notify(int & value){
        _mapEvent.notify(_id);
    }
    ofParameter<int> _parameter;
};
