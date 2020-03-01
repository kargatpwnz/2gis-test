#include "tree.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>

#include <boost/algorithm/string.hpp>



namespace std {

ostream& operator<<(ostream& os, const data_t & data) {
	visit([&os](auto c) { os << c; }, data);
	return os;
}

}

void Tree::PrintTree() const {
	if (root_)
		Print(root_, 0);
}

void Tree::Print(const node_ptr & root, int level) const {
	for (int i = 0; i < level; ++i)
		std::cout << '\t';

	std::cout << root->value;
	std::cout << '\n';
	for (const auto & x : root->children) {
		Print(x, level + 1);
	}
}

void Tree::Serialize(std::ostream & stream) {
	Serialize(stream, root_);
}

void Tree::Serialize(std::ostream & oss, const node_ptr & root) {
	std::queue<TreeNode *> queue;

	if (root_)
		queue.push(root_.get());

	while (!queue.empty()) {
		const auto & the_node = *queue.front();
		oss << the_node.value << '\n';
		bool first = true;
		for (const auto & ch : the_node.children) {
			if (!first)
				oss << ' ';
			first = false;
			oss << ch->value;
			if (!ch->children.empty())
				queue.push(ch.get());
		}
		queue.pop();
		oss << '\n';
	}

}

void Tree::Deserialize(std::istream & iss) {
	std::string parent;
	std::string children;

	// First string - parent
	// Second string - children
	std::queue<TreeNode *> queue;
	while (getline(iss, parent)) {
		boost::trim(parent);

		auto data = TreeNode::ParseString(parent);
		if (queue.empty()) {
			root_ = std::make_unique<TreeNode>(TreeNode::ParseString(parent));
			queue.push(root_.get());
		} else {
			for (; !queue.empty(); queue.pop())
				if (queue.front()->value == data)
					break;

			if (queue.empty())
				throw std::runtime_error("error while doing BFS");
		}

		getline(iss, children);
		boost::trim(children);

		if (children.empty()) {
			queue.pop();
			continue;
		}

		queue.front()->children = TreeNode::ParseChildren(children);
		for (const auto & child : queue.front()->children) {
			queue.push(child.get());
		}

		queue.pop();
	}
}

std::vector<node_ptr> TreeNode::ParseChildren(const std::string & str) {
	std::vector<node_ptr> retval;

	std::vector<std::string> split_values;
	boost::split(split_values, str, boost::algorithm::is_any_of(" "), boost::algorithm::token_compress_on);
	retval.reserve(split_values.size());

	for (const auto & str_value : split_values) {
		if (str_value.empty())
			continue;
		retval.push_back(std::make_unique<TreeNode>(TreeNode::ParseString(str_value)));
	}
	return retval;
}

data_t TreeNode::ParseString(const std::string & str) {
	try {
		std::size_t pos = 0;
		int v = std::stoi(str, &pos);
		if (pos == str.size())
			return v;
	} catch (...) {}
	try {
		std::size_t pos = 0;
		double v = std::stod(str, &pos);
		if (pos == str.size())
			return v;
	} catch (...) {}

	return std::move(str);
}
