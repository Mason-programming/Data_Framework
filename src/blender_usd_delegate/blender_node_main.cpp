//
// Created by Mason Kirby on 6/18/25.
//


#include "blender_usd_delegate.h"

int main(){
    std::string user = "kirby";
    std::string path = "/Users/masonkirby/Desktop/Data_Framework";
    blender_usd_delegate test(user);
    std::string usdFile = "/Users/masonkirby/Desktop/Worker/Worker.usd";
    test.saveAs(path, user);

    return 0;
}