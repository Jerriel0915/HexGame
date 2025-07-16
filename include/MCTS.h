#ifndef MCTS_H
#define MTCS_H

#include "Board.h"
#include <unordered_map>
#include <vector>

class MCTS {
private:
	std::unordered_map<Board, float, Board::Hash> Q;	//< 节点的奖励总值
	std::unordered_map<Board, int, Board::Hash> N;		//< 节点的访问次数
	std::unordered_map<Board, std::vector<Board>, Board::Hash> children;	//< 节点的子节点
	float exploration_constant = 1.0;	//< 探索常数

public:
	MCTS(const float _exploration_constant = 1)
		: exploration_constant(_exploration_constant) {}

	/**
	 * @brief 选择最佳的子节点
	 * @param node 棋盘状态节点
	 * @return Board 返回选择的子节点
	 */
	Board choose(const Board& node);

	/**
	 * @brief 扩展
	 * @param node 棋盘状态节点
	 */
	void do_rollout(Board& node);

	/**
	 * @brief 选择一个未探索的节点
	 * @param node 棋盘状态节点
	 * @return vector<Board> 一个未探索的子节点
	 */
	std::vector<Board> select(const Board& node);

	/**
	 * @brief 使用uct策略选择节点
	 * @param node 棋盘状态节点
	 * @return Board 返回选择的子节点
	 */
	Board uct_select(const Board& node);

	/**
	 * @brief 扩展节点的子节点
	 * @param node 棋盘状态节点
	 */
	void expand(const Board& node);

	/**
	 * @brief 进行随机模拟
	 * @param node 棋盘状态节点
	 * @return 奖励值
	 */
	float simulate(Board node);

	/**
	 * @brief 反向传播更新父节点的Q值与N值
	 * @param path 搜索路径
	 * @param reward 奖励值
	 */
	void backpropagate(const std::vector<Board>& path, float reward);
};

#endif // !MCTS_H