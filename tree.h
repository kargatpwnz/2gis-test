#ifndef TWO_GIS_TREE_H_
#define TWO_GIS_TREE_H_

#include <string>
#include <vector>
#include <map>

class TreeNode {
 public:
  union {
    std::string string_value;
    double double_value;
    int int_value;
  };

  bool IsInt = false;
  bool IsDouble = false;
  bool IsString = false;

  std::vector<class TreeNode*> children;

  TreeNode(std::string string_value) : string_value(std::move(string_value)) {
    IsString = true;
  }

  TreeNode(double double_value) : double_value(double_value) {
    IsDouble = true;

  }

  TreeNode(int int_value) : int_value(int_value) {
    IsInt = true;
  }

  virtual ~TreeNode() {

  }
};

class Tree {
 public:
  Tree();
  virtual ~Tree();

  void Test();
  void PrintTree();
  void Serialize(std::ofstream &stream);

  void Serialize(std::ofstream &stream, TreeNode *root);

  void Deserialize(std::ifstream &stream);
  void Deserialize(std::ifstream &stream, TreeNode *root);

 private:
  void Print(TreeNode *root, int level);
  void MapToTree();
  void OutputValueToStream(std::ofstream &stream, TreeNode *root);
  void PrintValue(TreeNode *root);
  bool CompareNodes(TreeNode *node1, TreeNode *node2);
  void Dfs(TreeNode *root);

  TreeNode *root_;
  std::map<class TreeNode *, std::vector<class TreeNode *>> parent_children_map_;
};

#endif //TWO_GIS_TREE_H_
