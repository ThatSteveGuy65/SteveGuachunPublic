# ifndef COMP_NET_HPP
# define COMP_NET_HPP

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

class Network {
public:
  Network(const std::string& devices,
             const std::string& communication_link);
  
  Network(const Network& rhs) = delete;
  Network& operator=(const Network& rhs) = delete;
  ~Network() = default;
  bool AreConnected(std::string device_1, std::string device_2) const;
  bool AreConnectedSpecific(std::string device_1, std::string device_2, const std::string& connection) const;
  int ShortestPathLenght(std::string device_1, std::string device_2) const;
  int ShortestPathLenghtSpecific(std::string device_1, std::string device_2, const std::string& connection) const;
  std::vector<std::string> GetPath(std::string device, int communication_links) const;
  size_t CountTopology() const;
  size_t CountTopology(const std::string& relationship) const;
  size_t CountTopologySpecific(const std::vector<std::string>& relationships) const;
  

private:
  std::vector<std::string> verticies_all_devices_;
  std::map<std::string, std::vector<int>> verticies_Specific_;

  std::list<std::string>& GetNextToList(std::string vertex);

  std::map<std::string, std::list<std::string>> All_devices_graph_;

  std::map<std::string, std::set<std::pair<std::string, std::string>>> Specific_devices_graph_;

  std::map<std::string, std::list<int>> ConnectionsList_;
};

std::vector<int> FGraph(
    const std::map<int, std::set<std::pair<int, std::string>>>& graph,
    const std::string& relationship);

#endif
