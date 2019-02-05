#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"

#define USE_PROGRAMMABLE_GL

using namespace flowTools;

enum visualizationTypes{ INPUT_FOR_DEN = 0, INPUT_FOR_VEL, FLOW_VEL, BRIDGE_VEL, BRIDGE_DEN, BRIDGE_TMP, OBSTACLE, FLUID_BUOY, FLUID_VORT, FLUID_TMP, FLUID_DIVE, FLUID_PRS, FLUID_VEL, FLUID_DEN };

const vector<string> visualizationNames({"input for density", "input for velocity", "optical flow", "bridge velocity", "bridge density", "bridge temperature", "obstacle", "fluid buoyancy", "fluid vorticity", "fluid temperature", "fluid divergence", "fluid pressure", "fluid velocity", "fluid density"});

class ofApp : public ofBaseApp{
public:
	void	setup();
	void	update();
	void	draw();
	void	keyPressed(int key);
	
	int		simulationWidth, simulationHeight, avgWidth, avgHeight, windowWidth, windowHeight;
	
	ofParameter<int>	densityWidth;
	ofParameter<int>	densityHeight;
	ofParameter<int>	simulationScale;
	ofParameter<int>	areaScale;
	void 				simulationResolutionListener(int &_value);
	
	vector< ftFlow* >		flows;
	ftOpticalFlow			opticalFlow;
	ftVelocityBridgeFlow	velocityBridgeFlow;
	ftDensityBridgeFlow		densityBridgeFlow;
	ftTemperatureBridgeFlow temperatureBridgeFlow;
	ftFluidFlow				fluidFlow;
	vector< ftMouseFlow* >	mouseFlows;
	ftMouseFlow				densityMouseFlow;
	ftMouseFlow				velocityMouseFlow;
	
	ofFloatPixels			pixels;
	int						numRegios;
	vector<ofRectangle> 	regios;
	ftPixelFlow				pixelFlow;
	vector<ftAverageFlow>	averageFlows;
	
	ofParameterGroup		visualizationParameters;
	ofParameter<int>		visualizationMode;
	ofParameter<string>		visualizationName;
	ofParameter<float>		visualizationScale;
	ofParameter<bool>		toggleVisualizationScalar;
	void visualizationModeListener(int& _value) 			{ visualizationName.set(visualizationNames[_value]); }
	void visualizationScaleListener(float& _value)			{ for (auto flow : flows) { flow->setVisualizationScale(_value); } }
	void toggleVisualizationScalarListener(bool &_value)	{ for (auto flow : flows) { flow->setVisualizationToggleScalar(_value); } }
	
	ofVideoGrabber		simpleCam;
	ofFbo				cameraFbo;
	
	ofxPanel			gui;
	void				setupGui();
	void				minimizeGui(ofxGuiGroup* _group);	
	void				switchGuiColor(bool _switch);
	ofParameter<float>	guiFPS;
	ofParameter<float>	guiMinFPS;
	ofParameter<bool>	toggleFullScreen;
	ofParameter<bool>	toggleGuiDraw;
	ofParameter<bool>	toggleCameraDraw;
	ofParameter<bool>	toggleMouseDraw;
	ofParameter<bool>	toggleAverageDraw;
	ofParameter<bool>	toggleReset;
	
	void				toggleFullScreenListener(bool& _value) { ofSetFullscreen(_value);}
	void				toggleResetListener(bool& _value);
	void 				windowResized(ofResizeEventArgs & _resize){ windowWidth = _resize.width; windowHeight = _resize.height; }
	
	void				drawGui();
	deque<float>		deltaTimeDeque;
	float				lastTime;
};
