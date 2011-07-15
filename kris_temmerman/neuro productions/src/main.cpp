#include "testApp.h"
#include "ofAppGlutWindow.h"




int main() {
	ofAppGlutWindow window;
    //window.setGlutDisplayString("rgb double depth>=16 alpha samples<=4");
   window.setGlutDisplayString("rgb double depth>=32 alpha samples<=4");
	ofSetupOpenGL(&window, 900 ,900, OF_WINDOW);
    ofSetWindowPosition(0 , 0) ;
	ofRunApp(new testApp());
}
