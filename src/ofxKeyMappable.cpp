#include "ofxKeyMappable.h"

ofxKeyMappable::ofxKeyMappable(int id) : _id(id){}

void ofxKeyMappable::addListener(ofxKeyMapper & listener){
//    ofAddListener(_mapEvent, &listener, &ofxKeyMapper::onMapEvent);
}

ofEvent <int> & ofxKeyMappable::getMapEvent(){
	return _mapEvent;
}
