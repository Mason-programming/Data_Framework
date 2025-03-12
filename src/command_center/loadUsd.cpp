#include "loadUSD.h"


bool loadBlender::loadUSDFile(std::string usd_path){

    bool was_successful = false; 

    try{ 

        

        was_successful = true; 

    }
    catch{ 



    }

    

    if (!usd_path){ 
        std::cout << "There was no usd path that was provided" << std::endl; 
        return -1; 
    }


    return was_successful 
}

