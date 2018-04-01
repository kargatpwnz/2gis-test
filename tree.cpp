#include <iostream>
#include <fstream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

#include "tree.h"

Tree::Tree() {
}

Tree::~Tree() {
  for (auto x : root_->children)
    delete x;
  delete root_;
}

void Tree::PrintTree() {
  Print(root_, 0);
}

void Tree::Print(TreeNode *root, int level) {
  for (int i = 0; i < level; ++i)
    std::cout << "\t";
  PrintValue(root);
  for (auto x : root->children) {
    Print(x, level + 1);
  }
}

void Tree::Test() {
  auto *node1 = new TreeNode("qwe");
  auto *node2 = new TreeNode("baz");
  auto *node3 = new TreeNode(12);
  auto *node4 = new TreeNode(13.2);
  auto *node5 = new TreeNode("bar");
  auto *node6 = new TreeNode(15);
  node6->children.push_back(new TreeNode(22));
  root_->children.push_back(node1);
  root_->children.push_back(node2);
  root_->children.push_back(new TreeNode("asd"));

  root_->children[0]->children.push_back(node3);
  root_->children[0]->children.push_back(node4);

  root_->children[1]->children.push_back(node5);
  root_->children[1]->children.push_back(node6);

}

void Tree::Serialize(std::ofstream &stream) {
  Serialize(stream, root_);
}

void Tree::Serialize(std::ofstream &stream, TreeNode *root) {
  if (root == nullptr) {
    stream << "nullptr";
    return;
  }

  OutputValueToStream(stream, root);
  stream << std::endl;

  for (auto &x : root->children) {
    OutputValueToStream(stream, x);
    stream << " ";
  }
  stream << std::endl;

  for (auto &x : root->children)
    Serialize(stream, x);

}

void Tree::Deserialize(std::ifstream &stream) {
  std::string parent;
  std::string children;

  // First string - parent
  // Second string - children
  while (getline(stream, parent)) {
    getline(stream, children);
    boost::trim(parent);
    boost::trim(children);

    // Inserting parent key to map
    TreeNode *key_node;
    try {
      double value = std::stod(parent);
      key_node = new TreeNode(value);
    } catch (std::invalid_argument) {
      key_node = new TreeNode(parent);
    }

    if (children.empty())
      continue;
    parent_children_map_[key_node] = std::vector<class TreeNode *>({});

    std::vector<std::string> split_values;
    boost::split(split_values, children, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);

    // Add children to parent key
    for (const auto &str_value : split_values) {
      if (str_value.empty())
        continue;

      try {
        double value = std::stod(str_value);
        parent_children_map_[key_node].push_back(new TreeNode(value));
      } catch (std::invalid_argument) {
        parent_children_map_[key_node].push_back(new TreeNode(str_value));
      }
    }
  }

  MapToTree();
}

void Tree::MapToTree() {
  // In the map begin stored root of tree, because map isn't sorted
  // so I'm able to get first element in map as root

  auto it = parent_children_map_.begin();
  root_ = it->first;
  root_->children = it->second;
  parent_children_map_.erase(it);

  // Starting dfs and restoring tree
  Dfs(root_);
}

void Tree::OutputValueToStream(std::ofstream &stream, TreeNode *root) {
  if (root->IsInt)
    stream << root->int_value << " ";
  else if (root->IsString)
    stream << root->string_value << " ";
  else if (root->IsDouble)
    stream << root->double_value << " ";
}

void Tree::PrintValue(TreeNode *root) {
  if (root->IsInt)
    std::cout << root->int_value << std::endl;
  else if (root->IsString)
    std::cout << root->string_value << std::endl;
  else if (root->IsDouble)
    std::cout << root->double_value << std::endl;
}

bool Tree::CompareNodes(TreeNode *node1, TreeNode *node2) {
  if (node1->IsString && node2->IsString)
    return node1->string_value == node2->string_value;
  if (node1->IsDouble && node2->IsDouble)
    return node1->double_value == node2->double_value;
  else
    return false;

}

void Tree::Dfs(TreeNode *root) {
  for (auto &x : parent_children_map_) {
    if (CompareNodes(x.first, root))
      root->children = x.second;
  }

  for (auto &x : root->children) {
    Dfs(x);
  }
}