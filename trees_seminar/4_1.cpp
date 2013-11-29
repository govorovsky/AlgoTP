#include <iostream>
#include <cstdio>

struct CNode {
    int Key;
    int Height;
    int Amount; // будем хранить в каждом узле число вершин  справа + слева
    CNode* Left;
    CNode* Right;
	CNode(int key) : Key(key), Height(1), Left(0), Right(0),  Amount(1) {}
};

int Height(CNode* node)
{
	return node == 0 ? 0 : node->Height;
}

int Amount(CNode* node) // возвращаем количество вершин в правом и левом поддереве узла
{
	return node == 0 ? 0 : node->Amount;
}

int BalanceFactor(CNode* node)
{
	return Height(node->Right) - Height(node->Left);
}

void FixHeight(CNode* node)
{
    int Height_Left = Height(node->Left);
    int Height_Right = Height(node->Right);
    node->Height = (Height_Left > Height_Right ? Height_Left : Height_Right)+1;
}
void FixAmount(CNode* node)
{
    node->Amount = Amount(node->Right) + Amount(node->Left) + 1;
}

CNode* RotateRight(CNode* p)
{
    CNode* q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    FixHeight(p);
    FixHeight(q);
    FixAmount(p); //фиксим число вершин 
    FixAmount(q);
    return q;
}

CNode* RotateLeft(CNode* q)
{
    CNode* p = q->Right;
    q->Right = p->Left;
    p->Left = q;
    FixHeight(q);
    FixHeight(p);
    FixAmount(q); //фиксим число вершин 
    FixAmount(p);
    return p;
}

CNode* Balance(CNode* p)
{
    if( BalanceFactor(p) == 2 )
    {
        if( BalanceFactor(p->Right) < 0 ) {
            p->Right = RotateRight(p->Right); // большой поворот
        }
        return RotateLeft(p);
    }
    if( BalanceFactor(p)==-2 )
    {
        if( BalanceFactor(p->Left) > 0  ) {
            p->Left = RotateLeft(p->Left); 
        }
        return RotateRight(p);
    }
    // необходимо фиксить число вершин так как оно могло измениться
    FixHeight(p);
    FixAmount(p);
    return p; 
}

CNode* Insert(CNode* p, int key, int answer)
{
    if( p == 0 ) {
        std::cout << answer << "\n";
		return new CNode(key);
    }
    if( key < p->Key ) {
        // идем налево и прибавляем в ответ количество вершин больших key
        answer += Amount(p->Right) + 1;
        p->Left = Insert(p->Left, key, answer);
    }
    else {
        // иначе направо и ничего не прибавляем, так как значения < key нам не нужны
        p->Right = Insert(p->Right, key, answer);
    }
    return Balance(p);
}

CNode* FindMin(CNode* p)
{
    return p->Left == 0 ? p : FindMin(p->Left);
}

CNode* RemoveMin(CNode* p)
{
    if( p->Left == 0 )
        return p->Right;
    p->Left = RemoveMin(p->Left);
    return Balance(p);
}

CNode* Remove(CNode* p, int position)
{
    if( p == 0  || position > Amount(p) ) return 0;
    int current_amnt = Amount(p->Right) + 1;
    // удаляем по позиции солдата
	if( position == current_amnt ) {
       
        CNode* Left = p->Left;
        CNode* Right = p->Right;
        delete p;
        if( Right == 0 ) return Left;
        CNode* min = FindMin(Right);
        min->Right = RemoveMin(Right);
        min->Left = Left;
        return Balance(min);
    }

    if( position < current_amnt )
        p->Right = Remove(p->Right, position);
    else 
        p->Left = Remove(p->Left, position - current_amnt);	
    return Balance(p);
}

void Delete(CNode* node)
{
	if (!node) return;
	Delete(node->Left);
	Delete(node->Right);
	delete node;
}

int main()
{
	CNode* root = 0;
    int n;
    std::cin >> n;
    for(int i = 0;i < n; i++) {
        int comm;
		int key;
		std::cin >> comm >> key;
		if( comm ==  1 ) {
			root = Insert(root, key, 0);
		} else {
			root = Remove(root, key + 1);
		}
	}

	Delete(root);

	return 0;
}
