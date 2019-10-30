/**
 * @file logger.hpp
 * @author Andrew Obler (andrewobler@gmail.com)
 * @brief Logger class and utilities for nice-looking console and file logging.
 * @version 0.1
 * @date 2019-10-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include <fstream>

/**
 * The "level" of a logger, indicating which messages will be printed to the console in addition
 * to being written to the logfile. Note that all messages will be logged to the logfile (if one
 * is specified) regardless of the log level.
 */
enum class LogLevel : unsigned int {
    /**
     * The logger will not print any messages and will only log to the logfile.
     */
    SILENT,

    /**
     * The logger will print out error messages only.
     */
    ERROR,

    /**
     * The logger will print out error and info messages.
     */
    INFO,

    /**
     * The logger will print out all messages, including error, info and debug messages.
     */
    DEBUG
};

/**
 * An instance of a logger, which can be called upon to print messages to the console and/or write
 * them to a logfile.
 */
class Logger {
    private:
        /**
         * The name of this logger, prefixed to every message logged to indicate the source.
         */
        char* name;

        /**
         * A header that precedes every messgae from this logger. Has the form [name].
         */
        char* header;

        /**
         * A log level specifying which messages will be printed out to the console.
         */
        LogLevel level;

        /**
         * A relative or absolute path to the logfile. If not specified, an empty string.
         */
        char* logFilePath;

        /**
         * The logfile coupled to this logger. If there is no such file, undefined.
         */
        std::fstream logFile;

        /**
         * Whether this logger is coupled to a logfile. If so, all messages will be written to the
         * file at Logger::logFilePath; otherwise, messages will only be printed to the console
         * according to Logger::level.
         */
        bool coupled;

        /**
         * Log a message, writing it to the logfile if necessary and printing it to the console
         * according to the logger's level.
         * 
         * @param msgLevel the level of the message, i.e. ERROR, INFO, or DEBUG
         * @param msg the message to log
         */
        void log(LogLevel msgLevel, char* msg);

    public:
        /**
         * Create an uncoupled logger, with no corresponding logfile.
         * 
         * @param name the name of the logger
         * @param level the logging level
         */
        Logger(char* name, LogLevel level);

        /**
         * Create a logger that is coupled to a logfile.
         * 
         * @param name the name of the logger
         * @param level the logging level
         * @param logFilePath the relative or absolute path to the logfile (will be created if
         *                    it does not yet exist)
         */
        Logger(char* name, LogLevel level, char* logFilePath);

        /**
         * Destructor for a logger. Closes the logfile if open.
         */
        ~Logger();

        /**
         * Log a message at the ERROR level.
         * 
         * @param msg the message to log
         */
        void error(char* msg);

        /**
         * Log a message at the INFO level.
         * 
         * @param msg the message to log
         */
        void info(char* msg);

        /**
         * Log a message at the DEBUG level.
         * 
         * @param msg the message to log
         */
        void debug(char* msg);
};
