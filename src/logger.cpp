/**
 * @file logger.cpp
 * @author Andrew Obler (andrewobler@gmail.com)
 * @brief Implementation of functions in logger.hpp.
 * @version 0.1
 * @date 2019-10-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <cstring>
#include <fstream>
#include <iostream>

#include "logger.hpp"

// Mapping from LogLevel to actual level names as header strings
static char* levelToString[4] = {
    "[SILENT]: ",
    "[ERROR]: ",
    "[INFO]: ",
    "[DEBUG]: "
};

Logger::Logger(char* name, LogLevel level) {
    this->name = name;
    
    // Build the header for this logger
    this->header = new char[strlen(name) + 4];
    this->header[0] = '[';
    strncpy(this->header + 1, name, strlen(name));
    strcpy(this->header + 1 + strlen(name), "] ");

    this->level = level;
    this->logFilePath = "";
    this->coupled = false;
}

Logger::Logger(char* name, LogLevel level, char* logFilePath)
    : Logger(name, level)
{
    logFile.open(logFilePath, std::fstream::out | std::fstream::ate);
    if (!logFile) {
        std::cerr << "[Logger] [ERROR]: Unable to open logfile \"" << logFilePath <<"\" for output"
                  << std::endl;
        return;
    }
    this->logFilePath = logFilePath;
    this->coupled = true;
}

Logger::~Logger() {
    // If the logfile is open, close it
    if (coupled) {
        logFile.close();
    }
}

void Logger::log(LogLevel msgLevel, char* msg) {
    // If coupled, write to the logfile
    if (coupled) {
        logFile << header << levelToString[(unsigned int) level] << msg << std::endl;
    }

    // Write to the console if specified by the log level
    // TODO: support for nonstandard cout
    if ((unsigned int) msgLevel <= (unsigned int) level) {
        std::cout << header << levelToString[(unsigned int) level] << msg << std::endl;
    }
}

void Logger::error(char* msg) {
    log(LogLevel::ERROR, msg);
}

void Logger::info(char* msg) {
    log(LogLevel::INFO, msg);
}

void Logger::debug(char* msg) {
    log(LogLevel::DEBUG, msg);
}
