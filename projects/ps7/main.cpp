// Copyright 2024 Wendy Carvalho
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;

int main(int argc, char* argv[]) {
  std::string logFileName = argv[1];
  std::string rprtFileName, line, timestamp, tmp, day, serviceName;
  std::stringstream boots, services;

  std::map<std::string, std::stringstream> serviceMap;
  std::vector<std::string> serviceNames = {
      "Logging",           "DatabaseInitialize",
      "MessagingService",  "HealthMonitorService",
      "Persistence",       "ConfigurationService",
      "LandingPadService", "PortConfigurationService",
      "CacheService",      "ThemingService",
      "StagingService",    "DeviceIOService",
      "BellService",       "GateService",
      "ReaderDataService", "BiometricService",
      "StateManager",      "OfflineSmartviewService",
      "AVFeedbackService", "DatabaseThreads",
      "SoftLoadService",   "WATCHDOG",
      "ProtocolService",   "DiagnosticsService"};
  for (const auto& serviceName : serviceNames) {
    serviceMap[serviceName] = std::stringstream();
  }
  std::vector<std::string> notStarted;

  std::ifstream log(logFileName);

  std::string _date = "\\d{4}-\\d{2}-\\d{2}\\s";
  std::string _time = "\\d{2}:\\d{2}:\\d{2}[:.]";
  std::string _start = "\\s(.*log.c.166.*)";
  std::string _success =
      "\\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector";

  std::regex reStart(_date + _time + _start);
  std::regex reDone(_date + _time + _success);
  std::regex serviceStart(
      "Starting Service\\.\\s\\s([A-Za-z]+)\\s(\\d+(?:\\.\\d+)*)");
  std::regex serviceDone(
      "Service started "
      "successfully\\.\\s\\s([A-Za-z]+)\\s(\\d+(?:\\.\\d+)*)\\s(.(\\d+)\\s(ms)."
      ")");
  std::smatch match;

  if (!log.is_open()) {
    std::cout << "could not open file" << std::endl;
    exit(1);
  }
  int lineCnt = 1;
  int iniCnt = 0, sucCnt = 0;
  bool booting = false;
  ptime t1, t2;

  while (getline(log, line)) {
    if (std::regex_search(line, reStart)) {
      if (booting) {
        boots << "**** Incomplete boot ****\n\nServices\n";
        for (auto& each : serviceMap) {
          boots << "\t" << each.first << std::endl;
          if (each.second.str().empty()) {
            boots << "\t\tStart: Not started(" << logFileName << ")"
                  << std::endl;
            boots << "\t\tStart: Not completed(" << logFileName << ")"
                  << std::endl;
            boots << "\t\tElapsed Time:" << std::endl;
            notStarted.push_back(each.first);
          } else {
            boots << each.second.str();
          }
        }
        boots << "*** Services not successfully started: " << std::endl;
        for (auto& e2 : notStarted) {
          boots << e2 << ", ";
        }
        boots << "\n\n";
        for (const auto& serviceName : serviceNames) {
          serviceMap[serviceName] = std::stringstream();
        }
        notStarted.clear();
      }
      timestamp = line.substr(11, 8);
      day = line.substr(0, 10);
      date d(from_simple_string(day));
      ptime pt(d, time_duration(std::stoi(timestamp.substr(0, 2)),
                                std::stoi(timestamp.substr(3, 2)),
                                std::stoi(timestamp.substr(6, 2))));
      t1 = pt;
      boots << "=== Device boot ===" << std::endl;
      boots << lineCnt << "(" << logFileName << "): " << line.substr(0, 19)
            << " Boot Start" << std::endl;
      booting = true;
      iniCnt++;
    } else if (std::regex_search(line, match, serviceStart)) {
      if (booting) {
        serviceMap[match[1]] << "\t" << match[1] << std::endl;
        serviceMap[match[1]] << "\t\tStart: " << lineCnt << "(" << logFileName
                             << ")" << std::endl;
      }
    } else if (std::regex_search(line, match, serviceDone)) {
      if (booting) {
        serviceMap[match[1]] << "\t\tCompleted: " << std::to_string(lineCnt)
                             << "(" << logFileName << ")" << std::endl;
        serviceMap[match[1]] << "\t\tElapsed Time: " << match[4] << " ms"
                             << "\n";
      }
    } else if (std::regex_search(line, reDone)) {
      if (booting) {
        timestamp = line.substr(11, 8);
        day = line.substr(0, 10);
        date d(from_simple_string(day));
        ptime pt(d, time_duration(std::stoi(timestamp.substr(0, 2)),
                                  std::stoi(timestamp.substr(3, 2)),
                                  std::stoi(timestamp.substr(6, 2))));
        t2 = pt;
        time_duration totalTime = t2 - t1;
        boots << lineCnt << "(" << logFileName << "): " << line.substr(0, 19)
              << " Boot Completed" << std::endl;
        boots << "\tBoot Time: " << totalTime.total_milliseconds() << "ms\n"
              << std::endl;
        boots << "Services\n";
        for (auto& each : serviceMap) {
          boots << each.second.str();
        }
        for (const auto& serviceName : serviceNames) {
          serviceMap[serviceName] = std::stringstream();
        }
        booting = false;
        sucCnt++;
      } else {
        boots << "**** Incomplete boot ****\n\nServices\n";
        for (auto& each : serviceMap) {
          boots << "\t" << each.first << std::endl;
          if (each.second.str().empty()) {
            boots << "\t\tStart: Not started(" << logFileName << ")"
                  << std::endl;
            boots << "\t\tStart: Not completed(" << logFileName << ")"
                  << std::endl;
            boots << "\t\tElapsed Time:\n" << std::endl;
            notStarted.push_back(each.first);
          } else {
            boots << each.second.str();
          }
        }
        boots << "*** Services not successfully started: " << std::endl;
        for (auto& e2 : notStarted) {
          boots << e2 << ", ";
        }
        boots << "\n\n";
        for (const auto& serviceName : serviceNames) {
          serviceMap[serviceName] = std::stringstream();
        }
        notStarted.clear();
      }
    }
    lineCnt++;
  }

  std::ofstream report;
  report.open(logFileName + ".rpt");
  report << "Device Boot Report\n" << std::endl;
  report << "InTouch log file: " << logFileName << std::endl;
  report << "Lines Scanned: " << lineCnt - 1 << "\n" << std::endl;
  report << "Device boot count: initiated = " << iniCnt
         << ", completed: " << sucCnt << "\n\n"
         << std::endl;
  report << boots.rdbuf();

  report.close();
  log.close();

  return 0;
}
