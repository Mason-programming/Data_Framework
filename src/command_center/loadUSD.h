// BlenderBridge.hpp
#ifndef LOAD_USD_HPP
#define LOAD_USD_HPP

#include <usdex/core/XformAlgo.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/usd/usdGeom/xformable.h>
#include <string> 
#include <iostream>

class loadUSD{

    private: 
        const std::string filepath; 
        void* operator new(size_t size); 
        void operator delete(void* ptr); 

    public: 
    loadUSD(const std::string& filepath); 

    void loadUSDFile(const std::string& filepath); 
    void exportUSDFile()
    void recievedUpdate(); 

    ~loadUSD(); 


}; 

class loadBlender : loadUSD{

    public: 
        virtual void loadUSDFile(); 
        virtual void exportUSDFile(); 
        virtual void recievedUpdate(); 
        ~loadBlender(); 
}; 

class loadUnreal : loadUSD{

    public: 

    virtual void loadUSDFile(const std::string& filepath); 
    virtual void exportUSDFile(); 
    virtual void recievedUpdate();
    ~loadUnreal();  
}; 

