#pragma once 
#include <iostream>



class smart_usd{ 

    public: 
    smart_usd(); 
    smart_usd(const std::string& user, const std::string& dcc,
                         const std::string& stage, const std::string& dept,
                         bool& status)
    : user(user), dcc(dcc), stage(stage), department(dept), status(status){} 

    ~smart_usd(); 

    std::string get_user(); 
    std::string get_dcc(); 
    std::string get_stage(); 
    std::string get_department(); 
    bool get_status(); 

    void set_usesr(); 
    void set_dcc(); 
    void set_stage(); 
    void set_department(); 
    void set_status(); 

    private: 
    std::string user; 
    std::string dcc; 
    std::string stage; 
    std::string department; 
    bool status; 
}; 