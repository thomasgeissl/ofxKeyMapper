#pragma once
#include "ofMain.h"
#include "ofxKeyMappable.h"
#include "ofxKeyMappableBool.h"
#include "ofxKeyMappableFloat.h"
#include "ofxKeyMappableInt.h"
#include "ofxKeyMappableVoid.h"

class ofxKeyMapper{
	public:
		ofxKeyMapper();
		void addParameter(ofParameter <bool> & parameter);
		void addParameter(ofParameter <float> & parameter);
		void addParameter(ofParameter <int> & parameter);
		void addParameter(ofParameter <void> & parameter);
        void addParameters(ofParameterGroup & parameters);


		bool addMapping(int key, int id, bool force = true);
		bool removeMapping(int key);

		bool doesMappingExist(int key);
		bool doesMappableExist(int id);
		int getMappedId(int key);
		ofxKeyMappable * getMappable(int id);
		ofParameterGroup & getParameters();
		void onMapEvent(int & idOfMappable);

		bool loadMapping(std::string path);
		bool saveMapping(std::string path, bool force = true);

		void keyPressed(int key);

	private:
		std::map<int, ofxKeyMappable*> _mappables;
		std::map<int, int> _mapping;
		std::vector<ofParameter<bool>> _params;

		ofParameterGroup _parameters;
		ofParameter <bool> _activeParameter;
		ofParameter <bool> _activeMappingParameter;

		int _idOfMappable;
		int _idCounter;
};
