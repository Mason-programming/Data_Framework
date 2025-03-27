#include "processCommand.h"

int main(int argc, char* argv[]) {


    std::string usdPath = "/Users/masonkirby/Desktop/test_usd/SirArchibald/stage.usd";
    ProcessCommand blenderCmd("/Applications/Blender.app/Contents/MacOS/Blender", usdPath, "layout");
    //blenderCmd.setDepartment("layout"); // Or detect from env
    blenderCmd.launch();

    return 0;
}
