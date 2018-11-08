#pragma once
#include "ofxKeyMappable.h"

class ofxKeyMappableVoid : public ofxKeyMappable {
public:
    ofxKeyMappableVoid(ofParameter <void> & parameter, int id) : ofxKeyMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxKeyMappableVoid::notify);
    }
    void map(){}
    void notify(){
        _mapEvent.notify(_id);
    }
    ofParameter <void> _parameter;
};
