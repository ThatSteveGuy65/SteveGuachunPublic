#include "Comp_net.hpp"

#include <fstream>
#include <map>
#include <queue>
#include <utility>



std::vector<int> FGraph(
    const std::map<int, std::set<std::pair<int, std::string>>>& graph,
    const std::string& connection) {
  std::vector<int> output;

  for (const auto& [key, value] : graph) {
    for (const auto& pair : value) {
      if (pair.second == connection) {
        output.push_back(key);
        break;
      }
    }
  }
  return output;
}

Network::Network(const std::string& devices,
                       const std::string& communication_link) {
  std::ifstream device(devices);
  std::string add;
  while (device >> add) {
    All_devices_graph_.insert({add, std::list<std::string>()});
    Specific_devices_graph_.insert({add, std::set<std::pair<std::string, std::string>>()});
    verticies_all_devices_.push_back(add);
  }

  std::ifstream relations(communication_link);
  std::string device_one;
  std::string device_two;
  std::string connection;
  
  while (relations >> device_one  >> device_two >> connection) {
    All_devices_graph_[device_one].push_back(device_two);
    All_devices_graph_[device_two].push_back(device_one);

    Specific_devices_graph_[device_one].insert(std::make_pair(device_two, connection));
    Specific_devices_graph_[device_two].insert(std::make_pair(device_one, connection));
  }
}

std::list<std::string>& Network::GetNextToList(std::string vertex) {
  return All_devices_graph_[vertex];
}
// all correct dont edit
//bool AreConnected(std::string device_1, std::string device_2) const
bool Network::AreConnected(std::string device_1, std::string device_2) const  {
  std::queue<std::string> que;
  std::map<std::string, std::string> seen;

  que.push(device_1);
  seen.insert({device_1, device_1});

  while (!que.empty()) {
    std::string current = que.front();
    if (current == device_2) {
      return true;
    }
    for (std::string a : All_devices_graph_.at(current)) {
        if (seen.count(a) == 0) {
            que.push(a);
            seen.insert({a, a});
        }
    }
    que.pop();
  }
  return false;
}


// in each pair the first is the device and the second is the connection

bool Network::AreConnectedSpecific(std::string device_1,
                            std::string device_2,
                            const std::string& connection) const {
  std::queue<std::string> que;
  std::map<std::string, std::string> seen;

  que.push(device_1);
  seen.insert({device_1, device_1});

  while (!que.empty()) {
    std::string current = que.front();
    if (current == device_2) {
      return true;
    }
    for (std::pair<std::string, std::string> pair : Specific_devices_graph_.at(current)) {
      if (seen.count(pair.first) == 0 && pair.second == connection) {
        que.push(pair.first);
        seen.insert({pair.first, pair.first});
      }
    }
    que.pop();
  }
  return false;
}

/// all correct dont edit
int Network::ShortestPathLenght(std::string device_1, std::string device_2) const {
  std::queue<std::pair<std::string, int>> que;
  std::unordered_map<std::string, std::string> seen;

  que.push(std::pair(device_1, 0));
  seen.insert({device_1, device_1});

  while (!que.empty()) {
    std::pair current = que.front();
    if (current.first == device_2) {
      return current.second;
    }
    for (std::string a : All_devices_graph_.at(current.first)) {
      if (seen.count(a) == 0) {
        que.push(std::pair(a, current.second + 1));
        seen.insert({a, a});
      }
    }
    que.pop();
  }
  return -1;
}

int Network::ShortestPathLenghtSpecific(std::string device_1,
                           std::string device_2,
                           const std::string& connection) const {
  std::queue<std::pair<std::string, int>> que;
  std::map<std::string, std::string> seen;

  que.push(std::pair(device_1, 0));
  seen.insert({device_1, device_1});

  while (!que.empty()) {
    std::pair current = que.front();
    if (current.first == device_2) {
      return current.second;
    }
    for (std::pair<std::string, std::string> a : Specific_devices_graph_.at(current.first)) {
      if (seen.count(a.first) == 0 && a.second == connection) {
        que.push(std::pair(a.first, current.second + 1));
        seen.insert({a.first, a.first});
      }
    }
    que.pop();
  }
  return -1;
}

/// all correct dont edit
/// gets number of steps away
std::vector<std::string> Network::GetPath(std::string device, int connection_links) const {
  std::vector<std::string> output;
  std::list<std::pair<std::string, int>> lenghts;
  std::queue<std::pair<std::string, int>> que;
  std::map<std::string, std::string> seen;

  que.push(std::pair(device, 0));
  seen.insert({device, device});

  while (!que.empty()) {
    std::pair current = que.front();
    lenghts.push_back(current);
    for (std::string a : All_devices_graph_.at(current.first)) {
      if (seen.count(a) == 0) {
        que.push(std::pair(a, current.second + 1));
        seen.insert({a, a});
      }
    }
    que.pop();
  }
  for (std::pair a : lenghts) {
    if (a.second == connection_links) {
      output.push_back(a.first);
    }
  }
  return output;
}

/// correct dont edit

size_t Network::CountTopology() const {
  unsigned int output = 0;
  std::queue<std::string> que;
  std::map<std::string, std::string> used;
  std::vector<std::string> vert = verticies_all_devices_;
  if (vert.empty()) {
    return output;
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    used.insert({vert.at(i), "not seen"});
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    if (used[vert.at(i)] == "not seen") {
      std::string insert = vert.at(i);
      que.push(insert);
      used[insert] = "In queue";
      output++;
      while (!que.empty()) {
        std::string current = que.front();
        for (std::string node : All_devices_graph_.at(current)) {
          if (used[node] == "not seen") {
            used[node] = "In queue";
            que.push(node);
          }
        }
        used[current] = "left queue";
        que.pop();
      }
    }
  }
  return output;
}

// std::map<int, std::set<std::pair<int, std::string>>> Specific_devices_graph_;

size_t Network::CountTopology(const std::string& connection) const {
  unsigned int output = 0;
  std::queue<std::string> que;
  std::map<std::string, std::string> used;
  std::vector<std::string> vert = verticies_all_devices_;
  if (vert.empty()) {
    return output;
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    used.insert({vert.at(i), "not seen"});
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    if (used[vert.at(i)] == "not seen") {
      std::string insert = vert.at(i);
      que.push(insert);
      used[insert] = "In queue";
      output++;
      while (!que.empty()) {
        std::string current = que.front();
        for (std::pair<std::string, std::string> node : Specific_devices_graph_.at(current)) {
          if (used[node.first] == "not seen" && node.second == connection) {
            used[node.first] = "In queue";
            que.push(node.first);
          }
        }
        used[current] = "left queue";
        que.pop();
      }
    }
  }
  return output;
}

size_t Network::CountTopologySpecific(
    const std::vector<std::string>& relationships) const {
  std::set<std::string> real;
  for (std::string i : relationships) {
    real.insert(i);
  }
  unsigned int output = 0;
  std::queue<std::string> que;
  std::map<std::string, std::string> used;
  std::vector<std::string> vert = verticies_all_devices_;
  if (vert.empty()) {
    return output;
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    used.insert({vert.at(i), "not seen"});
  }
  for (unsigned int i = 0; i < vert.size(); i++) {
    if (used[vert.at(i)] == "not seen") {
      std::string insert = vert.at(i);
      que.push(insert);
      used[insert] = "In queue";
      output++;
      while (!que.empty()) {
        std::string current = que.front();
        for (std::pair<std::string, std::string> node : Specific_devices_graph_.at(current)) {
          if (used[node.first] == "not seen" && real.count(node.second)  == 0) {
            used[node.first] = "In queue";
            que.push(node.first);
          }
        }
        used[current] = "left queue";
        que.pop();
      }
    }
  }
  return output;
}