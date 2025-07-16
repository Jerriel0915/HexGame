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
		return node.find_random_child();	//< ���û���ӽڵ㣬�����ѡ��һ���ӽڵ�
	}

	auto score = [&](const Board& n) {
		if (N[n] == 0) {
			return -INFINITY;  // ����ѡ��δ���ʹ��Ľڵ�
		}
		return Q[n] / N[n];  // ƽ������
		};

	return *std::max_element(children[node].begin(), children[node].end(), [&](const Board& a, const Board& b) {
		return score(a) < score(b);
		});
}

void MCTS::do_rollout(Board& node) {
	std::vector<Board> path = select(node);

	Board leaf = path.back();  // ��ȡ·���е����һ���ڵ�
	expand(leaf);  // ��չҶ�ڵ�
	float reward = simulate(leaf);  // ģ����Ϸ����ȡ����
	backpropagate(path, reward);  // ���򴫲�����·���еĽڵ�
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
			if (!children.count(child)) {  // ����ӽڵ�δ�����ʹ�
				unexplored.emplace_back(child);
			}
		}

		if (!unexplored.empty()) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(0, unexplored.size() - 1);
			Board next = unexplored[dist(gen)];  // ���ѡ��һ��δ̽�����ӽڵ�
			path.emplace_back(next);
		}

		current_node = uct_select(current_node);  // ʹ��UCTѡ����һ���ڵ�
	}
	return path;
}

Board MCTS::uct_select(const Board& node) {
	// ȷ�������ӽڵ㶼�ѱ���չ������������ children map �У�
	for (const auto& child : children[node]) {
		assert(children.count(child) > 0 && "UCT select called before all children were expanded");
	}

	// ����uctֵ
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
		children[node] = node.find_children();  // ��ȡ��ǰ�ڵ�������ӽڵ�
	}
}

float MCTS::simulate(Board node) {
	Camp perspective = node.getTurn();  // ��¼ģ�⿪ʼʱ�����

	while (!node.is_terminal()) {
		node = node.find_random_child();  // ģ������
	}

	// ��������ӽ�Ӧ�� initial player��perspective��
	float reward = node.reward(perspective);  // ������ʼ�ӽ�
	//std::cout << "Simulated reward: " << reward << std::endl;
	return reward;
}



void MCTS::backpropagate(const std::vector<Board>& path, float reward) {
	for (auto it = path.rbegin(); it != path.rend(); it++) {
		const Board& node = *it;
		N[node]++;  // ���ӷ��ʴ���
		Q[node] += reward;  // ���½�����ֵ
		reward = 1.0f - reward;
	}

	for (auto it = path.rbegin(); it != path.rend(); it++) {
		//std::cout << "Node: " << it->getTurn() << " Q: " << Q[*it] << " N: " << N[*it] << std::endl;
	}
}