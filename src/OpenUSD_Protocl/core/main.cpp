#include "UsdBridgeProtocol.h"
#include <iostream>

int main() {
    UsdBridgeProtocol protocol;

    // Register test handlers
    protocol.registerHandler(MessageType::IMPORT_USD, [](const UsdBridgeMessage& msg) {
        std::cout << "✅ [Handler] Importing USD: " << msg.usd_path() << std::endl;
    });

    protocol.registerHandler(MessageType::SYNC_ANIMATION, [](const UsdBridgeMessage& msg) {
        std::cout << "🎞️  [Handler] Syncing animation for: " << msg.usd_path() << std::endl;
    });

    // Test case 1: Valid import
    UsdBridgeMessage importMsg("IMPORT_USD", "/path/to/file.usd");
    protocol.dispatch(importMsg);

    // Test case 2: Valid sync
    UsdBridgeMessage syncMsg("SYNC_ANIMATION", "/path/to/anim.usd");
    protocol.dispatch(syncMsg);

    // Test case 3: Unknown type
    UsdBridgeMessage unknownMsg("INVALID_TYPE", "/nope");
    protocol.dispatch(unknownMsg);

    return 0;
}
