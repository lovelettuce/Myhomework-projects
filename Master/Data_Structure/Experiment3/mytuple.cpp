//
// Created by 杨雨劼 on 2023/11/13.
//

#include "mytuple.h"
using std::cout, std::cin, std::endl;
using namespace TUPLE;

//-----------------------mytuple::---------------------

void Mytuple::transpose (Mytuple &A)  {
    TupleNode* p = A.header_;
    //遍历链表，交换行列信息
    while (p) {
        int tempIndex = p->row_;
        p->row_ = p->column_;
        p->column_ = tempIndex;
        p = p->next_;
    }
    cout << "<Mytuple> The Matrix has been transposed."
         << endl << endl;
}

void Mytuple::reloadTuple(Mytuple &A) {
    TupleNode* p = A.header_, *pPre = A.header_;
    if (!A.header_) {
        //三元组为空，无法删除结点
        cout << "The tuple has no element." << endl;
    }
    else {
        int i = 0, zeroElem = 0;
        while (p) {
            if (p->value_ == 0) {
                //删除零元素
                if (p == A.header_) {
                    //被删除元素是头指针所指的结点
                    p = p->next_;
                    delete A.header_;
                    A.header_ = p;
                }
                else {
                    //被删除元素不是头指针所指的结点
                    pPre->next_ = p->next_;
                    TupleNode* temp = p;
                    p = p->next_;
                    delete temp;
                }
                zeroElem++;
            }
            else {
                //遍历链表
                p = p->next_;
                if (i >= 1) {
                    pPre = pPre->next_;
                }
                i++;
            }
        }
        if (zeroElem) {
            //ZeroElem记录被删除的零元素个数
            cout << "<DeleteZeroElement> ";
            cout << zeroElem << " 0-element was deleted from the tuple." << endl;
        }
    }
    p = A.header_; int newLength = 0;
    while (p) {
        //遍历链表，更新链表长度信息
        newLength++;
        p = p->next_;
    }
    A.length_ = newLength;
}

//'+'运算符重载：左操作数可变，右操作数不可变(const &)
Mytuple& Mytuple::operator + (const Mytuple &B) {
    //算法思想：两个无序单链表的合并，原被加数链表指针指向新链表，加数链表不可改动
    TupleNode *pa = nullptr, *paPre = nullptr, *pb = B.header_;
    while (pb) {
        pa = this->header_, paPre = header_;
        int i = 0;
        //加数指针不变，遍历一遍被加数链表
        while (pa) {
            //行列信息相同，对应值相加
            if (pa->row_ == pb->row_ && pa->column_ == pb->column_) {
                pa->value_ += pb->value_;
                break;
            }
            pa = pa->next_;
            if (i >= 1) //指向指针的前一个结点
                paPre = paPre->next_;
            if (!pa) {
                //遍历完整个链表都没有相同元素，则在被加数表尾添加结点实现0+加数
                TupleNode *newNode = new TupleNode(pb->row_, pb->column_, pb->value_);
                paPre->next_ = newNode;
            }
            i++;
        }
        pb = pb->next_;
    }
    return *this;
}

//'-'运算符重载：原理与'+'运算符重载类似
Mytuple& Mytuple::operator - (const Mytuple &B)
{
    TupleNode *pa = nullptr, *paPre = nullptr, *pb = B.header_;
    while (pb) {
        pa = this->header_, paPre = header_;
        int i = 0;
        while (pa) {
            if (pa->row_ == pb->row_ && pa->column_ == pb->column_) {
                pa->value_ -= pb->value_;
                break;
            }
            pa = pa->next_;
            if (i >= 1)
                paPre = paPre->next_;
            if (!pa) {
                TupleNode *newNode = new TupleNode(pb->row_, pb->column_, 0 - pb->value_);
                paPre->next_ = newNode;
            }
            i++;
        }
        pb = pb->next_;
    }
    return *this;
}

/* '*'运算符重载：第一种情况：三元组 * double
 * 隐式调用对象(使用this)，返回对象的拷贝且不能改变对象， 函数体用const修饰
 */
Mytuple Mytuple::operator * (double multiplier) const
{
    //算法思想：遍历一遍链表，对所有元素都乘上乘数
    Mytuple temp;
    TupleNode* p = this->header_;
    while (p) {
        p->value_ *= multiplier;
        p = p->next_;
    }
    temp = *this;
    return temp;
}

//'='运算符重载：将右操作数的对象拷贝给左操作数的对象
Mytuple& Mytuple::operator = (const Mytuple &B)
{
    //左右操作数相同：自我赋值
    if (this == &B) {
        return *this;
    }

    //防止内存泄露
    if (this != &B) {
        if (header_ != nullptr) {
            delete header_;
            header_ = nullptr;
        }
    }

    TupleNode* p = B.header_;
    //重新对调用对象建立链表，使元素和右操作数的对象的元素一样
    while (p) {
        TupleNode* newNode = new TupleNode(p->row_, p->column_, p->value_);
        if (!this->header_) {
            this->header_ = newNode;
        } else {
            newNode->next_ = this->header_;
            this->header_ = newNode;
        }
        p = p->next_;
    }
    return *this;
}

//-------------------Mymatrix::----------------------

Mymatrix::Mymatrix() {
    //构造函数：构造一个全0方阵
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = 0;
        }
    }
}

void Mymatrix::getRandomMatrix() {
    cout << "<Mymatrix> The matrix has been initialized:"
         << endl;
    bool IsMatrixZero = true;
    //若随机出来的方阵仍全0，则重新随机
    while (IsMatrixZero) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //随机数生成，用switch控制零元素出现概率：p = n-1/n
                switch (rand() % 4) {
                    case 0: {
                        matrix[i][j] = (double)(rand() % 10);
                        IsMatrixZero = false;
                    }
                        break;
                    default: {
                        matrix[i][j] = 0;
                    }
                        break;
                }
            }
        }
    }
    //打印生成的方阵
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Mymatrix::storeInTuple(Mytuple& T) {
    //保证三元组T是空链表
    if (T.header_) {
        delete T.header_;
        T.header_ = nullptr;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //遍历一遍方阵，找到非零元素建立链表
            if (matrix[i][j] != 0) {
                TupleNode* temp = new TupleNode(i, j, matrix[i][j]);
                if (!T.header_) {
                    //若头指针为空
                    T.header_ = temp;
                } else {
                    //若头指针不为空
                    temp->next_ = T.header_;
                    T.header_ = temp;
                }
            }
        }
    }
    cout << "<Mymatrix> The [matrix] has been stored into [tuple]."
         << endl << endl;
}

void Mymatrix::showMatrix (Mytuple &T) {
    cout << "<Mytuple> Show Matrix" << endl;
    Mymatrix newMatrix;
    //在显示信息前更新三元组信息，并删除多余的零元素结点
    Mytuple::reloadTuple(T);
    TupleNode* p = T.header_;
    //修改零方阵的信息，使之成为三元组对应的方阵
    while (p) {
        newMatrix.matrix[p->row_][p->column_] = p->value_;
        p = p->next_;
    }
    //打印方阵信息
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << newMatrix.matrix[i][j] << "   ";
        }
        cout << endl;
    }
    //非零元素的个数
    cout << "Numbers of Non-0 Element: " << T.length_ << endl
         << endl;
}