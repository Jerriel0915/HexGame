#include "../include/MCTS.h"
#include "../include/Board.h"
#include <stdexcept>
#include <cmath>
#include <random>
#include <assert.h>
#include <iostream>

Board MCTS::choose(const Board& node) {
	if (node.is_terminal()) {
		throw std::runtime_error("choose called on terminal node");
	}

	if (children.find(node) == children.end()) {
		return node.find_random_child();	//< 如果没有子节点，则随机选择一个子节点
	}

	auto score = [&](const Board& n) {
		if (N[n] == 0) {
			return -INFINITY;  // 避免选择未访问过的节点
		}
		return Q[n] / N[n];  // 平均奖励
		};

	return *std::max_element(children[node].begin(), children[node].end(), [&](const Board& a, const Board& b) {
		return score(a) < score(b);
		});
}

void MCTS::do_rollout(Board& node) {
	std::vector<Board> path = select(node);

	Board leaf = path.back();  // 获取路径中的最后一个节点
	expand(leaf);  // 扩展叶节点
	float reward = simulate(leaf);  // 模拟游戏并获取奖励
	backpropagate(path, reward);  // 反向传播更新路径中的节点
}

std::vector<Board> MCTS::select(const Board& node) {
	std::vector<Board> path;
	Board current_node = node;

	while (true) {
		path.emplace_back(current_node);
		if (!children.count(current_node) || children[current_node].empty()) {
			break;
		}

		std::vector<Board> unexplored;
		for (const auto& child : children[current_node]) {
			if (!children.count(child)) {  // 如果子节点未被访问过
				unexplored.emplace_back(child);
			}
		}

		if (!unexplored.empty()) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, unexplored.size() - 1);
			Board next = unexplored[dist(gen)];  // 随机选择一个未探索的子节点
			path.emplace_back(next);
		}

		current_node = uct_select(current_node);  // 使用UCT选择下一个节点
	}
	return path;
}

Board MCTS::uct_select(const Board& node) {
	// 确保所有子节点都已被扩展（即都存在于 children map 中）
	for (const auto& child : children[node]) {
		assert(children.count(child) > 0 && "UCT select called before all children were expanded");
	}

	// 计算uct值
	float log_N_vertex = std::log(N[node]);
	auto uct = [&](const Board& n) {
		return Q[n] / N[n] + exploration_constant * std::sqrt(log_N_vertex / N[n]);
		};
	return *std::max_element(children[node].begin(), children[node].end(), [&](const Board& a, const Board& b) {
		return uct(a) < uct(b);
		});
}

void MCTS::expand(const Board& node) {
	if (children.find(node) == children.end()) {
		children[node] = node.find_children();  // 获取当前节点的所有子节点
	}
}

float MCTS::simulate(Board node) {
	Camp perspective = node.getTurn();  // 记录模拟开始时的玩家

	while (!node.is_terminal()) {
		node = node.find_random_child();  // 模拟下棋
	}

	// 奖励结果视角应是 initial player（perspective）
	float reward = node.reward(perspective);  // 传入起始视角
	//std::cout << "Simulated reward: " << reward << std::endl;
	return reward;
}



void MCTS::backpropagate(const std::vector<Board>& path, float reward) {
	for (auto it = path.rbegin(); it != path.rend(); it++) {
		const Board& node = *it;
		N[node]++;  // 增加访问次数
		Q[node] += reward;  // 更新奖励总值
		reward = 1.0f - reward;
	}

	for (auto it = path.rbegin(); it != path.rend(); it++) {
		//std::cout << "Node: " << it->getTurn() << " Q: " << Q[*it] << " N: " << N[*it] << std::endl;
	}
}