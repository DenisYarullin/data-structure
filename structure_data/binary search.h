#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

//� ������� ���� �� ����� ���� �����.
//����� �������� ������ �������� ���� ���������� ����� �������� ��� �������� ������ �������.
//����� �������� ������ ��� ������ �������� ���� ���������� ������ �������� ��� �������� ������� �������.

template <typename T>
class BinaryTreeNode
{
private:
	T value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
public:
	BinaryTreeNode(T value_) : value(value_), left(nullptr), right(nullptr) {}
	int CompareTo(T otherValue) const;
};


/// ���������� ������� ���� � ������.
/// ��������� ������������ �� ���� Value.
/// ����� ���������� 1, ���� �������� �������� ���� ������,
/// ��� ����������� ������, -1, ���� ������ � 0, ���� ��� �����
template <typename T>
int BinaryTreeNode<T>::CompareTo(T otherValue) const
{
	if (value > otherValue)
		return 1;
	else if (value < otherValue)
		return -1;
	else
		return 0;
}


template <typename T>
class BinaryTree
{
private:
	int count;
	BinaryTreeNode *head;
public:
	BinaryTree() : count(0), head(nullptr) {}
	void Add(T value);
	bool Contains(T value);
	bool Remove(T value);
	void Clear();
	int Count();
	void PreOrderTraversal();
	void PostOrderTraversal();
	void InOrderTraversal();
private:
	void AddTo(BinaryTreeNode<T> *node, T value);
};

// ����������� �������.
template <typename T>
void BinaryTree<T>::AddTo(BinaryTreeNode<T> *node, T value)
{
	// ������ 1: ����������� �������� ������ �������� ����
	if (node->CompareTo(value) > 0)
	{
		// ���� ��� ������ ���������, ��������� �������� � ������ �������,
		if (node->left == nullptr)
		{
			node->left = new BinaryTreeNode(value);
		}
		else
		{
			// � ��������� ������ ��������� ��� ������ ���������
			AddTo(node->left, value);
		}
	}
	// ������ 2: ����������� �������� ������ ��� ����� �������� ����
	else
	{
		// ���� ��� ������� ���������, ��������� �������� � ������� �������,
		if (node->right == nullptr)
		{
			node->right = new BinaryTreeNode(value);
		}
		else
		{
			// � ��������� ������ ��������� ��� ������� ���������.
			AddTo(node->right, value);
		}
	}
}

template <typename T>
void BinaryTree<T>::Add(T value)
{
	// ������ 1: ���� ������ ������, ������ ������� �������� ����.
	if (head == nullptr)
	{
		head = new BinaryTreeNode(value);
	}
	// ������ 2: ������ �� ������ => 
	// ���� ���������� ����� ��� �������.
	else
	{
		AddTo(head, value);
	}

	count++;
}

template <typename T>
bool BinaryTree<T>::Remove(T value)
{

}

template <typename T>
bool BinaryTree<T>::Contains(T value)
{
	return true;
}

#endif // BINARY_SEARCH_H_

