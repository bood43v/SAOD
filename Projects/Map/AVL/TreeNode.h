/// Класс узел дерева
/// @author Будаев Г.Б.
#pragma once


/// <summary>
/// шаблонный класс узел бинарного дерева
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class TreeNode
{
private:
    TreeNode<T>* left; /// левый потомок
    TreeNode<T>* right;/// правый потомок
    T data;            /// данные

public:

    /// Конструктор без параметров
    TreeNode() : 
        data(NULL), left(nullptr), right(nullptr) {};

    /// Конструктор
    TreeNode(const T& data_, TreeNode<T>* left_ = nullptr, TreeNode<T>* right_ = nullptr) :
        data(data_), left(left_), right(right_) {};

    /// Конструктор копирования
    TreeNode(const TreeNode<T>& node) : data(node.data), left(nullptr), right(nullptr)
    {
        if (node.left) {
            left = new TreeNode<T>(*node.left);
        }
        if (node.right) {
            right = new TreeNode<T>(*node.right);
        }
    }

    ///// Конструктор перемещения
    //TreeNode(TreeNode<T>&& node) noexcept : data(node.data), left(node.left), right(node.right)
    //{
    //    node.left = nullptr;
    //    node.right = nullptr;
    //    std::cout << "Move Constructor" << std::endl;
    //}

    virtual ~TreeNode()
    {
        DeleteTree(this);
    }

    /// Вернуть указатель на левого потомка
    TreeNode<T>* Left() const {
        return left;
    };


    /// Вернуть указатель на правого потомка
    TreeNode<T>* Right() const {
        return right;
    };

    /// Установить левого потомка
    void SetLeft(TreeNode<T>* node_)
    {
        left = node_;
    }

    /// Установить прпвого потомка
    void SetRight(TreeNode<T>* node_)
    {
        right = node_;
    }

    /// Установить прпвого потомка
    void SetData(T data_)
    {
        data = data_;
    }

    /// Вернуть данные
    T Data() const
    {
        return data;
    }

    /// Поиск узла в дереве с возвратом указателя на узел, если он есть
    TreeNode<T>* Search(const T& key)
    {
        // node - указатель на текущий узел дерева (изначально на корень)
        TreeNode<T>* node = this;
        // если nullptr - дерево пустое
        if (node == nullptr) return nullptr;

        // пока не дошли до листа
        while (node != nullptr)
        {
            // если узел найден - выход
            if (key == node->Data())
                break;
            // иначе поиск в левом и правом поддереве, в зависимости от < или > текущего узла
            else
            {
                //root_ = t;
                if (key < node->Data())
                    node = node->Left();
                else
                    node = node->Right();
            }
        }
        // позвращаем указатель на найденный узел
        return node;
    }

    /// Поиск узла в дереве с возвратом указателя на узел, если он есть
    TreeNode<T>* SearchParent(const T& key)
    {
        // указатель на текущий узел
        TreeNode<T>* node = this;
        // указатель на родителя текущего узла
        TreeNode<T>* parent = nullptr;

        // если узел не найден - nullptr
        if (node->Search(key) == nullptr) return nullptr;
        // если искомый узел - корень -> возвращаем nullptr (нет родителя)
        if (node->Data() == key) return nullptr;

        // пока не дойдем до листа
        while (node != nullptr)
        {
            // если есть левый/правый потомок и он является искомым, то запоминаем родителя и выходим
            if ((node->Left() != nullptr && key == node->Left()->Data()) || (node->Right() != nullptr && key == node->Right()->Data()) )
            {
                parent = node;
                break;
            }  
            // иначе двигаемся по дереву влево/вправо
            else
            {
                if (key < node->Data())
                   node = node->Left();
                else
                   node = node->Right();
            }
        }
        
        // возвращаем указатель на родителя
        return parent;
    }



    /// <summary>
    /// Количество узлов - размер дерева
    /// </summary>
    /// <returns></returns>
    int Size()
    {
        if (this != nullptr) {
            // кол-во элементов в левом и правом поддереве
            int left, right;
            // указатель на текущий узел
            TreeNode<T>* node = this;
            // если нет потомков -> 1 узел(текущий)
            if (node->Left() == nullptr && node->Right() == nullptr)
                return 1;

            // если есть левое поддерево -> рекурсивно вызываем Size()
            if (node->Left() != nullptr)
                left = node->Left()->Size();
            // иначе возвращаем 0
            else left = 0;

            // если есть правое поддерево -> рекурсивно вызываем Size()
            if (node->Right() != nullptr)
                right = node->Right()->Size();
            // иначе возвращаем 0
            else right = 0;

            // возвращаем кол-во узлов в левом и правом поддереве +1 (корень дерева)
            return left + right + 1;
        }
        else return 0;
    }

    /// Глубина дерева
    int Depth() {
        // node - указатель на текущий узел
        TreeNode<T>* node = this;
        // глубина левого, правого поддерева и конечная глубина
        int depthLeft, depthRight, depth;
        /// Если дерево пустое
        if (node == nullptr) {
            depth = -1;
        }
        // иначе рекурсивно вызываем Depth()
        else {
            depthLeft = node->Left()->Depth();
            depthRight = node->Right()->Depth();
            // depth равен 1 + наибольшее из depthLeft и depthRight
            depth = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
        }
        return depth;
    }

    /// Поиск минимального в ветке (или дереве)
    TreeNode<T>* FindMin() {
        TreeNode<T>* curr = this;
        if (curr == nullptr) return nullptr;
        while (curr->Left() != nullptr)
            curr = curr->Left();
        return curr;
    }

    /// Поиск максимального в ветке (или дереве)
    TreeNode<T>* FindMax() {
        TreeNode<T>* curr = this;
        if (curr == nullptr) return nullptr;
        while (curr->Right() != nullptr)
            curr = curr->Right();
        return curr;
    }

    /// Следующий наибольший узел
    TreeNode<T>* Successor(const T &key) {
        /// текущий узел
        TreeNode<T>* curr = Search(key);
        /// если пустой
        if (curr == nullptr) return nullptr;
        /// если есть правый потомок ищем его самого левого потомка
        if (curr->Right() != nullptr) {
            return curr->Right()->FindMin();
        }
        /// если нет
        else {
            TreeNode<T>* successor = nullptr;
            /// то запоминаем предка
            TreeNode<T>* ancestor = this;
            while (ancestor != curr) {
                if (curr->Data() < ancestor->Data()) {
                    successor = ancestor;
                    ancestor = ancestor->Left();
                }
                else
                    ancestor = ancestor->Right();
            }
            return successor;
        }
    }


    /// Вставка узла
    void Insert(const T& key)
    {
        /// Eсли такого узла нет
        if (this->Search(key) == nullptr)
        {
            // t — текущий узел, parent — предыдущий узел
            TreeNode<T>* t = this, * parent = nullptr, * newNode;
            newNode = new TreeNode<T>(key);
            // Дойти до конца ветки
            while (t != nullptr)
            {
                // обновить указатель parent и идти направо или налево
                parent = t;
                if (key < t->Data())
                    t = t->Left();
                else
                    t = t->Right();
            }
            // если узлов нет, то вставить в качестве корневого узла
            if (parent->Data() == NULL)
                this->SetData(newNode->Data());
            // если key меньше родительского узла, вставить в качестве левого сына
            else if (key < parent->Data())
                parent->SetLeft(newNode);

            else
                // если key больше родительского узла
                parent->SetRight(newNode);
        }

    }

   
    /// Удаление узла - возвращаем указатель корень дерева с удаленным узлом
    TreeNode<T>* Remove(TreeNode<T>* root, const T& key) {
        TreeNode<T>* parent;

        /// Если пусто
        if (root == nullptr) return nullptr;

        if (key < root->Data()) {
            /// Рекурсивно удаляем значение из левого поддерева
            root->SetLeft(Remove(root->Left(), key));
        }
        else if (key > root->Data()) {
            /// Рекурсивно удаляем значение из правого поддерева
            root->SetRight(Remove(root->Right(), key));
        }
        /// Найден узел, который нужно удалить
        else {
            if (root->Left() == nullptr && root->Right() == nullptr) {
                /// Узел не имеет потомков
                delete root;
                root = nullptr;
            }
            else if (root->Left() == nullptr) {
                /// Узел имеет только правого потомка
                parent = root;
                root = root->Right();
                delete parent;
            }
            else if (root->Right() == nullptr) {
                /// Узел имеет только левого потомка
                parent = root;
                root = root->Left();
                delete parent;
            }
            else {
                // Узел имеет оба потомка
                TreeNode<T>* parent = root->Right()->FindMin();
                root->SetData(parent->Data());
                root->SetRight(Remove(root->Right(), parent->Data()));
            }
        }
        return root;
    }






    /// Печать 
    void PrintNodeData()
    {
        if (this != nullptr)
        {
            std::cout << "Data of node: " << this->Data() << std::endl;
        }
        else
        {
            std::cout << "Node is null" << std::endl;
        }
    }

    /// Обход LNR и вывод в массив
    void AddToArrayLNR(T arr[], int &i)
    {
        if (this != nullptr)
        {
            this->Left()->AddToArrayLNR(arr, i);
            arr[i] = this->Data();
            i++;
            this->Right()->AddToArrayLNR(arr, i);
        }
    }

    /// Обход NLR и вывод в массив
    void AddToArrayNLR(T arr[], int &i)
    {
        if (this == nullptr)
            return;
        arr[i] = this->Data();
        i++;
        this->Left()->AddToArrayNLR(arr, i);
        this->Right()->AddToArrayNLR(arr, i);
    }

    /// Обход RLN и вывод в массив
    void AddToArrayRNL(T arr[], int &i)
    {
        if (this == nullptr)
            return;
        this->Right()->AddToArrayRNL(arr, i);
        arr[i] = this->Data();
        i++;
        this->Left()->AddToArrayRNL(arr, i);
    }


    /// Копирование дерева
    TreeNode<T>* CopyTree()
    {
        const TreeNode<T>* root = this;
        /// root - указатель на текущий узел
        if (root == nullptr)
            return nullptr;

        /// Создаем новое дерево и задаем ему значение корня первого дерева
        TreeNode<T>* newRoot = new TreeNode<T>(root->Data());
        /// Рекурсивно вызываем метод для левого и правого поддерева
        newRoot->SetLeft(root->Left()->CopyTree());
        newRoot->SetRight(root->Right()->CopyTree());

        return newRoot;
    }


};

/// Удаление дерева
template<typename T>
void DeleteTree(TreeNode<T>* root) {
    if (root) {
        DeleteTree(root->Left());
        DeleteTree(root->Right());
        root = nullptr;
        delete root;
    }
}

// Функция для обхода дерева и применения функции к каждому элементу
template<typename T>
void apply(TreeNode<T>* root, T(*func)(T)) {
    if (root != nullptr) {
        // Применяем функцию к текущему элементу
        root->SetData(func(root->Data()));
        // Рекурсивно обходим левое и правое поддеревья
        apply(root->Left(), func);
        apply(root->Right(), func);
    }
}
// Функция для возведения числа в квадрат
template<typename T>
T double_(T x) {
    return 2 * x;
}