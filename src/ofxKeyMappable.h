#pragma once
#include "ofParameter.h"

class ofxKeyMapper;
class ofxKeyMappable {
public:
    ofxKeyMappable(int id);
    void addListener(ofxKeyMapper & listener);
    virtual void map(){}
    ofEvent<int> & getMapEvent();
    
protected:
    ofEvent<int> _mapEvent;
    int _id;
    
private:
};

