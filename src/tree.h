#pragma once

#include <map>
#include <memory>
#include <variant>
#include <vector>

class TreeNode;

using node_ptr = std::unique_ptr<TreeNode>;
using data_t = std::variant<int, double, std::string>;

class TreeNode {
public:
	explicit TreeNode(std::variant<int, double, std::string> data) : value(std::move(data)) {}

	static std::vector<node_ptr> ParseChildren(const std::string & str);
	static data_t ParseString(const std::string & str);

public:
	data_t value;
	std::vector<std::unique_ptr<TreeNode>> children;
};

class Tree {
public:
	void PrintTree() const;
	void Serialize(std::ostream & stream);
	void Deserialize(std::istream & iss);

private:
	void Serialize(std::ostream & oss, const node_ptr & root);
	void Print(const node_ptr & root, int level) const;

private:
	node_ptr root_;
};

