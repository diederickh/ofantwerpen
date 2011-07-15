//
//  MainModel.h
//  ofxKinect
//
//  Created by Kris Temmerman on 31/05/11.
//  Copyright 2011 Neuro Productions. All rights reserved.
//
#include <iostream>
using namespace std ;

class MainModel {
protected: 
    MainModel ();
public:
    virtual ~MainModel ();
    static MainModel * Instance();
    
    int state;
    
    
private:
    static MainModel * m_pSingleton;
};

