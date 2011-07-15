//
//  GausianBlurFactory.h
//  renderTest
//
//  Created by Kris Temmerman on 22/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//  
// c'est une singleton

#ifndef GAUSIONBLUR_FACTORY
#define GAUSIONBLUR_FACTORY


#include <vector>
#include <math.h>

using namespace std;

class GausianBlurFactory {

    protected: 
        GausianBlurFactory();
    public:
        virtual ~GausianBlurFactory();
        static GausianBlurFactory* getInstance();
    
        float* getKernel(int radius);
        float* getOffsetData(int textWidth ,int textHeight ,int radius,bool isHorizontal);
    
    private:
    
    vector<vector<float> > filterpool;

    static GausianBlurFactory* m_pGausianBlurFactory;
};
#endif

