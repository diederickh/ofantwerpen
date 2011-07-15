//
//  GausianBlurFactory.cpp
//  renderTest
//
//  Created by Kris Temmerman on 22/04/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "GausianBlurFactory.h"

GausianBlurFactory* GausianBlurFactory::m_pGausianBlurFactory = NULL;

GausianBlurFactory::GausianBlurFactory() { }
GausianBlurFactory::~GausianBlurFactory() { }

GausianBlurFactory* GausianBlurFactory::getInstance()
{
    if(m_pGausianBlurFactory == NULL)
        m_pGausianBlurFactory = new GausianBlurFactory;
    
    return m_pGausianBlurFactory;
    
}

float* GausianBlurFactory::getOffsetData(int textWidth ,int textHeight ,int radius,bool isHorizontal)
{
    int size = (radius*2+1)*2;
    
    float *data =new float[size];
    
    float wStep = 1.0f/ textWidth;
    float hStep =1.0f/ textHeight;
    
    int i;
    int pos =-radius;
    
    if (isHorizontal)
    {
        for(i=0;i<size/2;i++)
        {
            data[i*2] = wStep*pos;
            data[i*2 +1] = 0.0;
            pos++;
        }
    }
    else
    {
        for(i=0;i<size/2;i++)
        {
            data[i*2] = 0.0;
            data[i*2 +1] = hStep*pos;
            pos++;   
        }
    }
    
    return data;
} 
float* GausianBlurFactory::getKernel(int radius)
{
    
    
    
    int r = radius;
    int rows = r*2+1;
    
    
    float *kernel =new float[rows];
    
    
    float sigma = (float)radius/3;
    float sigma22 = 2*sigma*sigma;
    float sigmaPi2 = 2*3.1415*sigma;
    float sqrtSigmaPi2 = (float)sqrt(sigmaPi2);
    float radius2 = radius*radius;
    float total = 0;
    int index = 0;
    for (int row = -r; row <= r; row++) {
        float distance = row*row;
        if (distance > radius2)
            kernel[index] = 0;
        else
           kernel[index] = (float)exp(-(distance)/sigma22) / sqrtSigmaPi2;
        
        kernel[index] =r-abs(row);
        
        total += kernel[index];
        index++;
    }
    
    for (int i = 0; i < rows; i++)
        kernel[i] /= total;

    return kernel;
}