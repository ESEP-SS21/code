/*
 * Logger.h
 *
 *  Created on: 06.05.2021
 *      Author: jendr
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#define LOG_DEBUG \
    if(Logger::getLogger().getLoggingLevel() < DEBUG); \
    else Logger::getLogger().log("DEBUG")
#define LOG_WARNING \
    if(Logger::getLogger().getLoggingLevel() < WARNING); \
    else Logger::getLogger().log("WARNING")
#define LOG_ERROR \
    if(Logger::getLogger().getLoggingLevel() < ERROR); \
    else Logger::getLogger().log("ERROR")

#define LOG_SET_LEVEL(value) Logger::getLogger().setLoggingLevel(value);
#define LOG_SCOPE LogScope logscope(__FUNCTION__);

using namespace std;

enum LEVEL  {ERROR,WARNING,DEBUG};

class Logger{
public:
    static Logger& getLogger(){// Meyers Singleton.
        static Logger Instance;// Will be delete at the end.
        return Instance;
    }
    ofstream& log(string s){// return ofstream, so cascading <<..<<..<< is possible.
        logfile_<<time(NULL)<<" "<<s<<" ";// time ticks in seconds. Check OS for more accurate timer.
        return logfile_;
    }
    void setLoggingLevel(LEVEL level){
        logfile_<<"setting output level to "<<level<<endl;
        logginglevel_ = level;}
    LEVEL getLoggingLevel(){return logginglevel_;}
private:
    Logger()// make these private because of singleton.
    : logginglevel_(DEBUG)// set default level
    {       logfile_.open("logging.txt",ios::trunc);
            logfile_<<"LOGFILE. Build: "<<__DATE__<<", "<<__TIME__<<endl;
            }
    ~Logger(){      logfile_<<"END OF LOGFILE"<<endl; logfile_.close();}

    LEVEL logginglevel_;
    ofstream logfile_;
};

class LogScope{
public:
    LogScope(const string& s) : logger_(Logger::getLogger()) , functionname_(s){
        logger_.log("SCOPE")<<"entering "<<functionname_<<" \n";
    }
    ~LogScope(){
        logger_.log("SCOPE")<<"exiting "<<functionname_<<" \n";
    }
private:
    Logger& logger_;
    string functionname_;
};

#endif /* SRC_UTILS_LOGGING_LOGGER_H_ */
