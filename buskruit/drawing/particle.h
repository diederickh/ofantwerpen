#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class particle
{
    public:
        ofVec3f pos;
        ofVec3f vel;
        ofVec3f frc;   // frc is also know as acceleration (newton says "f=ma")
    
        int alpha;
			
        particle();
		virtual ~particle(){};

        void resetForce();
        void addForce(float x, float y);
        void addDampingForce();
        void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw();
	
		float damping;

    protected:
    private:
};

#endif // PARTICLE_H
