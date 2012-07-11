//
//  Config.h
//  elly
//
//  Created by Ce Zhang on 7/4/12.
//  Copyright (c) 2012 University of Wisconsin-Madison. All rights reserved.
//

#ifndef elly_Config_h
#define elly_Config_h

#include <string>


namespace elly{
    namespace utils{
        
        class Config{
        public:
            
            std::string version_number;
         
            std::string ui_verbose;
            std::string ui_logfile;
            std::string ui_logverbose;
            
            std::string rt_input;
            std::string rt_output;
            std::string rt_workdir;
            
            std::string rt_mode;
            
            int rt_thin;
            int rt_burnin;
            
            
            int sys_nthreads;
            
            
            Config(){
                
                version_number = "0.1";
                
                ui_verbose = "info";
                ui_logfile = "";
                ui_logverbose = "debug";
                
                rt_input   = "";
                rt_output  = "";
                rt_workdir = "";
                
                rt_mode    = "";
                
                rt_thin    = 1;
                rt_burnin  = 1;
                
                sys_nthreads = 1;
                
            }
            
            
        };
        
    }
}



#endif
