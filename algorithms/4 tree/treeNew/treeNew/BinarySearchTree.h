#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack> // Для итеративного обхода дерева
#include <vector>// Для сравнения деревьев 
#include <queue>// Для обхода в ширину

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T> & src) = delete;
	BinarySearchTree(BinarySearchTree<T>&& src);
	BinarySearchTree<T>& operator= (const BinarySearchTree<T>& src) = delete;
	BinarySearchTree<T>& operator= (BinarySearchTree<T>&& src);

	// true, если все узлы деревьев одинаковые.
	bool operator== (const BinarySearchTree<T>& src);
	bool operator> (const BinarySearchTree<T>& src) = delete;
	bool operator< (const BinarySearchTree<T>& src) = delete;

	virtual ~BinarySearchTree();
	
	// Функция поиска по ключу в бинарном дереве поиска.
	bool iterativeSearch(const T& key) const;

  // Вставка нового элемента в дерево:
  // true,если элемент добавлен
	// false, если элемент уже был
	bool insert(const T& key);

	// Удаление элемента из дерева, 
	// не нарушающее порядка элементов
	// true,если элемент удален 
	// false, если элемента не было.
	bool deleteKey(const T& key);

	// Печать строкового изображения дерева в выходной поток out.
	void print(std::ostream& out) const;

	// Определение количества узлов дерева.
	int getCount() const;

	// Определение высоты дерева.
	int getHeight() const;

	// Инфиксный обход дерева (итеративный).
	void iterativeInorderWalk () const;

	// Инфиксный обход дерева (рекурсивный).
	void inorderWalk() const;

	// обход дерева в ширину 
	void acrossWideWalk() const;

	// похожи ли деревья ? 
	bool areSimilar(const BinarySearchTree& rhs) const;

private:
	template <class T>
	struct Node {
		T key_;            // Значение ключа, содержащееся в узле.
		Node<T>* left_;     // Указатель на левое поддерево.
		Node<T>* right_;    // Указатель на правое поддерево.
		Node<T>* p_;        // Указатель на  родителя.

		// Конструктор узла.
		Node(T key, Node<T>* left = nullptr, 
			Node<T>* right = nullptr, Node<T>* p = nullptr):
			key_(key),
			left_(left),
			right_(right),
			p_(p)
		{}
	};

	Node<T>* root_; // Дерево реализовано в виде указателя на корневой узел.

	// Метод свап.
	void swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right);

	// Рекурсивная функция для освобождения памяти -- используется в деструктуре 
	void deleteSubtree(Node<T>* node);

	// Рекурсивная функция для вывода изображения дерева в выходной поток в скобочной форме 
	void printNode(std::ostream& out, Node<T>* root) const;

	// Рекурсивная функция определения количества узлов дерева.
	int getCountSubTree(const Node<T>* node) const;

	// Рекурсивная функция определения высоты дерева.
  int getHeightSubTree(Node<T>* node) const;

	// Рекурсивная функция для организации обхода узлов дерева. ?
	void inorderWalk(Node<T>* node) const;

	// Функция поиска адреса узла по ключу в бинарном дереве поиска. ? 
	Node<T>* iterativeSearchNode(const T& key) const;

};

	template <class T>
	BinarySearchTree<T>::BinarySearchTree():
		root_(nullptr)
	{}

	template <class T>
	BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src)
	{
		root_ = src.root_;
		src.root_ = nullptr;
	}

	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src)
	{
		deleteSubtree(root_); // очистка l-value 
		root_ = src.root_;    // пермещение 
		src.root_ = nullptr;
	}

	// Память, занимается узлами дерева.
	template <class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		deleteSubtree(root_);
	}

	// Рекурсивная функция для освобождения памяти.
	template <class T>
	void BinarySearchTree<T>::deleteSubtree(Node<T>* node)
	{
		if (node != nullptr)
		{
			if (node->left_ != nullptr) // Очищаем левое поддерево.
			{
				deleteSubtree(node->left_);
			}
			if (node->right_ != nullptr) // Очищаем правое поддерево.
			{
				deleteSubtree(node->right_);
			}
      // Далее, мы уверены, что все поддеревья удалены.

			if (node->p_ == nullptr) // Если node - корень - удаляем его как корень.
			{
				root_ = nullptr;
				delete node;
			}
			else // Если мы удаляем какое-то поддерево 
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если node слева от своего родителя
				{
					node->p_->left_ = nullptr;
					delete node;
				}
				else if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если node справа от своего родителя
				{
					node->p_->right_ = nullptr;
					delete node;
				}
			}
		}
	}

	// Вставка нового элемента в дерево:
  // true,если элемент добавлен; false, если элемент уже был.
	template <class T>
	bool BinarySearchTree<T>::insert(const T& key)
	{
		Node<T>* x = root_; // Проверяемый узел.
		Node<T>* y = nullptr; // для родителя (изначально nullptr).

		if (root_ == nullptr) // Если дерево изначально пустое, то просто делаем корень.
		{
			Node<T>* newRoot = new Node<T>(key, nullptr, nullptr, nullptr);
			root_ = newRoot;
			return true;
		}

		while (x != nullptr) // Пока не нашли нужную пустую ячейку...
		{
			if (x->key_ == key) // Не добавляем элемент с ключем, который есть в дереве.
			{
				return false;
			}
			// Родителем становится проверяемый элемент, 
			// так как x пойдет глубже- он будет на 1 узел впереди.
			y = x;
			if (key < x->key_)
			{
				x = x->left_;
			}
			else
			{
				x = x->right_;
			}
		}
		// Смотрим, в какую сторону от родителя вставлять элемент.
		if (key < y->key_)
		{
			y->left_ = new Node<T>(key, nullptr, nullptr, y);
			return true;
		}
		else
		{
			y->right_ = new Node<T>(key, nullptr, nullptr, y);
			return true;
		}
	}

	// Метод свап.
	template <class T>
	void BinarySearchTree<T>::swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right)
	{
		std::swap(left.root_, right.root_); // Просто меняем указатели на корень.
	}

	// Печать дерева
	template <class T>
	void BinarySearchTree<T>::print(std::ostream& out) const
	{
		printNode(out, root_);
		out << std::endl;
	}

	// Рекурсивная функция для вывода узла в выходной поток
	template <class T>
	void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
	{
		out << '(';
		if (root != nullptr) {
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}

	// Определение высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeight() const
	{
		// В случае, если в дереве только корень - высота будет = 0.
		// В случае, если дерево пустое - высота будет = -1.
		return getHeightSubTree(root_) - 1;
	}

	// Рекурсивная функция определения высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeightSubTree(Node<T>* node) const
	{
		// Если узел пустой - возвращаем 0.
		if (node == nullptr)
		{
			return 0;
		}

		// Если узел непустой - возвращаем 1 + высота самого высокого ребенка.
		// 1 складываются рекурсивно
		return std::max(1 + getHeightSubTree(node->left_), 1 + getHeightSubTree(node->right_));
	}

	// Определение количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCount() const
	{
		return getCountSubTree(root_);
	}

	// Рекурсивная функция определения количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCountSubTree(const Node<T>* node) const
	{

		if (node == nullptr) {
			return 0;
		}

		// Если узел не пустой - возвращаем 1 + количество узлов снизу.
		return (1 + getCountSubTree(node->left_) + getCountSubTree(node->right_));
	}

	// Функция поиска по ключу в бинарном дереве поиска.
	template <class T>
	bool BinarySearchTree<T>::iterativeSearch(const T& key)  const
	{
		return (iterativeSearchNode(key) != nullptr);
	}

	// Функция поиска адреса узла по ключу в бинарном дереве поиска
	template <class T>
	BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
	{
		Node<T>* x = root_;
		while ((x != nullptr) && (x->key_ != key)) // Пока может происходить поиск :)
		{
			if (key < x->key_) // идем влево
			{
				x = x->left_; 
			}
			else // идем вправо
			{
				x = x->right_;
			}
		}
		return x;
	}

	// Инфиксный обход дерева (рекурсивный)
	template <class T>
	void BinarySearchTree<T>::inorderWalk() const
	{
		inorderWalk(root_);
		std::cout << "\n";
	}

	template<class T>
	void BinarySearchTree<T>::acrossWideWalk() const
	{
		std::queue<Node<T>*> q;
		q.push(root_);
		while (!(q.empty()))
		{
			Node<T>* temp = q.front();
			q.pop();
			if (temp->left_ != nullptr)
			{
				q.push(temp->left_);
			}
			if (temp->right_!= nullptr)
			{
				q.push(temp->right_);
			}
			std::cout << temp->key_ << " ";
		}
	}

	template<class T>
	bool BinarySearchTree<T>::areSimilar(const BinarySearchTree& rhs) const 
	{
		if (this->getHeight() == -1 && rhs.getHeight() == -1) return true;
		else if (this->getHeight() == -1) return false;

		std::queue<Node<T>*> q;
		q.push(root_);
		while (!(q.empty()))
		{
			Node<T>* top = q.front();
			q.pop();
			if (top->left_ != nullptr)
			{
				q.push(top->left_);
			}
			if (top->right_ != nullptr)
			{
				q.push(top->right_);
			}
			if (!(rhs.iterativeSearch(top->key_)))
			{
				return false;
			}
		}
		return true;
	}
	
	
	// Рекурсивная функция для организации обхода узлов дерева.
	template <class T>
	void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
	{
		if (node != nullptr) // Если узел ненулевой..
		{
			inorderWalk(node->left_); // Обходим его левых детей
			// -- мы пишем сначала листья( детей),
			//затем только внутренний узлы ( когда "встреться 2 раз")  
			std::cout << node->key_; // выводим его значение.
			std::cout << ", ";
			inorderWalk(node->right_); // Наконец, обходим его правых детей.
		}
	}

	// Инфиксный обход дерева (итеративный)
	template <class T>
	void BinarySearchTree<T>::iterativeInorderWalk() const
	{
		std::stack<Node<T>*> nodeStack; // Стек, хранящий указатели на узлы.
		Node<T>* current = root_; // Узел, в который смотрим. 
		while ((nodeStack.size() != 0) || (current != nullptr)) // Пока есть узлы в стеке или узел, ненулевой.
		{
			if (current != nullptr)
			{
				nodeStack.push(current); // Заносим в очередь на просмотр.
				current = current->left_; // Смотрим левого ребенка.
			}
			else // Если просматриваемый элемент нулевой (например, по левым детям просматриваемого узла дошли до nullptr)...
			{
				current = nodeStack.top(); // Достаем элемент со стека на просмотр и по нему идем вправо  // здесь можно использовать родителя вместо стека 
				nodeStack.pop();
				std::cout << current->key_; // Смотрим его значение
				std::cout << ", ";
				current = current->right_; // Переходим в правое поддерево
			}
		}
		std::cout << "\n";
	}

	// Удаление элемента из дерева, не нарушающее порядка элементов.
	template <class T>
	bool BinarySearchTree<T>::deleteKey(const T& key)
	{
		Node<T>* node = iterativeSearchNode(key); // Ищем узел, который собираемся удалить.
		if (node == nullptr)
		{
			return false;
		}

		// Удаляем лист.
		if ((node->left_ == nullptr) && (node->right_ == nullptr))
		{
			if (node->p_ == nullptr) // Если этот лист - корень...
			{
				root_ = nullptr;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот лист слева от родителя...
				{
					node->p_->left_= nullptr;
					node->key_ = 0;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот лист справа от родителя...
				{
					node->p_->right_ = nullptr;
					node->key_ = 0;
					delete node;
					return true;
				}
			}
		}

		else if (((node->left_ != nullptr) && (node->right_ == nullptr)))
		{ // Удаляем узел только с левым ребенком.
			if (node->p_ == nullptr) // Если этот узел - корень...
			{
				node->left_->p_ = nullptr;
				root_ = node->left_;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
				{
					node->left_->p_ = node->p_;
					node->p_->left_ = node->left_;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
				{
				node->left_->p_ = node->p_;
				node->p_->right_ = node->left_;
				delete node;
				return true;
				}
			}
		}
		else if (((node->left_ == nullptr) && (node->right_ != nullptr)))
		{ // Удаляем узел только с правым ребенком.
			if (node->p_ == nullptr) // Если этот узел - корень...
			{
				node->right_->p_ = nullptr;
				root_ = node->right_;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
				{
					node->right_->p_ = node->p_;
					node->p_->left_ = node->right_;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
				{
					node->right_->p_ = node->p_;
					node->p_->right_ = node->right_;
					delete node;
					return true;
				}
			}
		}
		else if (((node->left_ != nullptr) && (node->right_ != nullptr)))
		{ // Удаляем узел с обоими детьми. Будем искать минимальный(левый) элемент из правого поддерева.
			Node<T>* x  = node->right_; // Смотрим правое поддерево.
			while (x->left_ != nullptr) // Пока есть левые дети - будем идти по ним.
			{
				x = x->left_;
			} // Теперь x - минимальный элемент из правого поддерева.
			if ((x->p_->left_ != nullptr) && (x->p_->left_->key_ == x->key_)) // Если x - слева от своего родителя.
			{
				x->p_->left_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
				if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
				{
					x->right_->p_ = x->p_;
				}
			}
			if ((x->p_->right_ != nullptr) && (x->p_->right_->key_ == x->key_)) // Если x - справа от своего родителя.
			{
				x->p_->right_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
				if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
				{
					x->right_->p_ = x->p_;
				}
			}
			// У нас "в буфере" появился элемент x, которым мы должны заменить удаляемый элемент.
			// Вроде бы нужно поработать с указателями...
			// Но мы можем сделать проще - в удаляемом элементе поставить значение элемента x, а элемент x удалить.
			node->key_ = x->key_;
			delete x;
			return true;
		}
		return false;
	}

	// 9 Сравнение деревьев: true, если все узлы деревьев одинаковые.
	template <class T>
	bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
	{
		// Вектора, которые будут хранить последовательность элементов дерева после инфиксного обхода.
		std::vector<T> vec1;
		std::vector<T> vec2;
		// Указатели, которые ходят по дереву.
		Node<T>* node1 = root_;
		Node<T>* node2 = src.root_;
		// Стеки указателей для итеративных обходов деревьев.
		std::stack<Node<T>*> nodeStack1;
		std::stack<Node<T>*> nodeStack2;

		// Итеративно обходим оба дерева и заносим их в вектор.
		while ((nodeStack1.size() != 0) || (node1 != nullptr))
		{
			if (node1 != nullptr)
			{
				nodeStack1.push(node1); // Заносим в очередь на просмотр.
				node1 = node1->left_; // Смотрим левого ребенка.
			}
			else // Если просматриваемый элемент нулевой (например, по левым детям просматриваемого узла дошли до nullptr)...
			{
				node1 = nodeStack1.top(); // Достаем элемент со стека на просмотр и по нему идем вправо
				nodeStack1.pop();
				vec1.push_back(node1->key_); 
				node1 = node1->right_; // Переходим в правое поддерево
			}
		}
		while ((nodeStack2.size() != 0) || (node2 != nullptr))
		{
			if (node2 != nullptr)
			{
				nodeStack2.push(node2);
				node2 = node2->left_;
			}
			else
			{
				node2 = nodeStack2.top();
				nodeStack2.pop();
				vec2.push_back(node2->key_);
				node2 = node2->right_;
			}
		}

		return vec1 == vec2;
	}

#endif
