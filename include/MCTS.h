#ifndef MCTS_H
#define MTCS_H

#include "Board.h"
#include <unordered_map>
#include <vector>

class MCTS {
private:
	std::unordered_map<Board, float, Board::Hash> Q;	//< �ڵ�Ľ�����ֵ
	std::unordered_map<Board, int, Board::Hash> N;		//< �ڵ�ķ��ʴ���
	std::unordered_map<Board, std::vector<Board>, Board::Hash> children;	//< �ڵ���ӽڵ�
	float exploration_constant = 1.0;	//< ̽������

public:
	MCTS(const float _exploration_constant = 1)
		: exploration_constant(_exploration_constant) {}

	/**
	 * @brief ѡ����ѵ��ӽڵ�
	 * @param node ����״̬�ڵ�
	 * @return Board ����ѡ����ӽڵ�
	 */
	Board choose(const Board& node);

	/**
	 * @brief ��չ
	 * @param node ����״̬�ڵ�
	 */
	void do_rollout(Board& node);

	/**
	 * @brief ѡ��һ��δ̽���Ľڵ�
	 * @param node ����״̬�ڵ�
	 * @return vector<Board> һ��δ̽�����ӽڵ�
	 */
	std::vector<Board> select(const Board& node);

	/**
	 * @brief ʹ��uct����ѡ��ڵ�
	 * @param node ����״̬�ڵ�
	 * @return Board ����ѡ����ӽڵ�
	 */
	Board uct_select(const Board& node);

	/**
	 * @brief ��չ�ڵ���ӽڵ�
	 * @param node ����״̬�ڵ�
	 */
	void expand(const Board& node);

	/**
	 * @brief �������ģ��
	 * @param node ����״̬�ڵ�
	 * @return ����ֵ
	 */
	float simulate(Board node);

	/**
	 * @brief ���򴫲����¸��ڵ��Qֵ��Nֵ
	 * @param path ����·��
	 * @param reward ����ֵ
	 */
	void backpropagate(const std::vector<Board>& path, float reward);
};

#endif // !MCTS_H