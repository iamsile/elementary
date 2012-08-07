//
//  IncrementalCorrelationRelation.h
//  elly
//
//  Created by Ce Zhang on 8/6/12.
//  Copyright (c) 2012 University of Wisconsin-Madison. All rights reserved.
//

#ifndef elly_IncrementalCorrelationRelation_h
#define elly_IncrementalCorrelationRelation_h


#include "../utils/Common.h"

#include <vector>

#include "../../../storageman/storageman/Buffer_mm.h"
#include "../../../storageman/storageman/KeyValue_fl.h"
#include "../../../storageman/storageman/KeyValue_vl.h"

#include "../../../storageman/storageman/KeyValue_fl_fastmm.h"

#include "../factors/factor_inits.h"

#include "AbstractCorrelationRelation.h"


namespace mia{
    namespace elly{
        namespace dstruct{
            
            template<template<template<class C> class A, class B> class BUFFER, class TYPE>
            class IncrementalCorrelationRelation : public mia::elly::dstruct::AbstractCorrelationRelation{
                
            public:
                
                mia::sm::KeyValue_fl<BUFFER, TYPE> kv;
                //mia::sm::KeyValue_fl_fastmm<TYPE> kv;
                
                void * lookup(int fid){
                    //todo: remember to delete
                    //todo: check whether it is slow
                    
                    //std::cout << "lookup" << fid << std::endl;
                    
                    TYPE rr = kv.get(fid);
                    TYPE * ret = new TYPE;
                    *ret = rr;
                    
                    return ret;
                }
                
                void update(int fid, void (*func_update)(void * , int , int , int ), int vid, int from, int to){
                    
                    if(func_update == NULL){
                        return;
                    }
                    
                    //lock(fid);
                    //kv.adhoc_update(fid, from, to);
                    //release(fid);
                    
                    //lock(fid);
                    TYPE rr = kv.get(fid);
                    func_update(&rr, vid, from, to);
                    kv.set(fid, rr);
                    //release(fid);
                
                }
                
                
                void prepare(){
                    
                    nfactor = 0;
                    
                    if(filetype.compare("tsv") == 0){
                        
                        int fid, vid, aux, nvar;
                        std::ifstream fin( filename.c_str() );
                        
                        while(fin >> fid >> nvar){
                            
                            TYPE fstate; //todo: change to a better name -- this is more general a class
                            
                            fin >> aux;
                            fstate.init_aux(aux);
                            
                            for(int i=0;i<nvar;i++){
                                fin >> vid;
                                fstate.init(vid);
                            }
                            
                            kv.set(fid, fstate);
                            nfactor ++;
                            
                            pthread_mutex_t * sem = new pthread_mutex_t;
                            pthread_mutex_init(sem, NULL);
                            sems.push_back(sem);
                            
                        }
                        
                    }
                    
                    mia::elly::utils::log() << "    + # factors = " << nfactor << std::endl;
                    
                }
                
            };
            
            
            
            
            
            
        }
    }
}



#endif
