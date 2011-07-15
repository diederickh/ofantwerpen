//
//  MainModel.cpp
//  ofxKinect
//
//  Created by Kris Temmerman on 31/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//

#include "MainModel.h"




MainModel* MainModel::m_pSingleton = NULL;

MainModel::MainModel() { }
MainModel::~MainModel() { }

MainModel* MainModel::Instance()
{
    if(m_pSingleton == NULL)
        m_pSingleton = new MainModel;
    
    return m_pSingleton;
}

