#include "logger.hpp"

int main() {
    // Test a basic, noncoupled logger
    Logger decoupled("Decoupled", LogLevel::INFO);

    // ERROR and INFO level messages should be visible
    decoupled.error("Can you see me? #1");
    decoupled.info("Can you see me? #2");

    // DEBUG level messages should not
    decoupled.debug("Shouldn't see me! #2.5");
}
