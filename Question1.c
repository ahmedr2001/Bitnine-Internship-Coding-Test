#include <stdio.h>
#include <stdlib.h>

#define GET_VARIABLE_NAME(Variable) (#Variable)

typedef unsigned long long ull;
typedef long long ll;

typedef enum TypeTag {
    ADD,
    SUB,
    MUL,
    DIV,
    ADD_FIB,
    SUB_FIB,
    MUL_FIB,
    DIV_FIB,
} TypeTag;

typedef struct Node {
    TypeTag type;
    int a;
    int b;
    ll result;
} Node;

/** DP Fibonacci up to n = 1e4 **/
void fib();
/** Iterative Fibonacci for n >= 1e4 (to avoid compiler crashes) **/
ull fibLargeN(int n);

void calcNodeResult(Node *node);

void calc(Node *node);

Node initNode(int a, int b)
{
    Node newNode;
    newNode.a = a;
    newNode.b = b;
    newNode.result = -1;
    return newNode;
}

void decideNodeType(Node *node, TypeTag typeTag)
{
    switch (typeTag)
    {
    case ADD:
        node->type = (node->a == NULL || node->b == NULL) ? ADD_FIB : ADD;
        break;
    case SUB:
        node->type = (node->a == NULL || node->b == NULL) ? SUB_FIB : SUB;
        break;
    case MUL:
        node->type = (node->a == NULL || node->b == NULL) ? MUL_FIB : MUL;
        break;
    case DIV:
        node->type = (node->a == NULL || node->b == NULL) ? DIV_FIB : DIV;
        break;    
    default:
        break;
    }    
}

Node makeNodeAddInt(int a, int b)
{
    Node newNode = initNode(a, b);
    decideNodeType(&newNode, ADD);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeAddNode(Node *ptr_a, Node *ptr_b)
{
    int res_a = (ptr_a) ? ptr_a->result : NULL;
    int res_b = (ptr_b) ? ptr_b->result : NULL;
    Node newNode = initNode(res_a, res_b);
    decideNodeType(&newNode, ADD);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeSubInt(int a, int b)
{
    Node newNode = initNode(a, b);
    decideNodeType(&newNode, SUB);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeSubNode(Node *ptr_a, Node *ptr_b)
{
    int res_a = (ptr_a) ? ptr_a->result : NULL;
    int res_b = (ptr_b) ? ptr_b->result : NULL;
    Node newNode = initNode(res_a, res_b);
    decideNodeType(&newNode, SUB);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeMulInt(int a, int b)
{
    Node newNode = initNode(a, b);
    decideNodeType(&newNode, MUL);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeMulNode(Node *ptr_a, Node *ptr_b)
{
    int res_a = (ptr_a) ? ptr_a->result : NULL;
    int res_b = (ptr_b) ? ptr_b->result : NULL;
    Node newNode = initNode(res_a, res_b);
    decideNodeType(&newNode, MUL);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeDivInt(int a, int b)
{
    Node newNode = initNode(a, b);
    decideNodeType(&newNode, DIV);
    calcNodeResult(&newNode);

    return newNode;
}

Node makeNodeDivNode(Node *ptr_a, Node *ptr_b)
{
    int res_a = (ptr_a) ? ptr_a->result : NULL;
    int res_b = (ptr_b) ? ptr_b->result : NULL;
    Node newNode = initNode(res_a, res_b);
    decideNodeType(&newNode, DIV);
    calcNodeResult(&newNode);

    return newNode;
}

#define makeFuncAdd _add
#define makeFuncSub _sub
#define makeFuncMul _mul
#define makeFuncDiv _div
#define _add(a, b) _Generic(a, int: makeNodeAddInt, Node *: makeNodeAddNode)(a, b)
#define _sub(a, b) _Generic(a, int: makeNodeSubInt, Node *: makeNodeSubNode)(a, b)
#define _mul(a, b) _Generic(a, int: makeNodeMulInt, Node *: makeNodeMulNode)(a, b)
#define _div(a, b) _Generic(a, int: makeNodeDivInt, Node *: makeNodeDivNode)(a, b)

ull fibArray[10000];

int main()
{
    fib();

    Node add = makeFuncAdd(10, 16);
    Node mul = makeFuncMul(15, 14);
    Node sub = makeFuncSub(&mul, &add);
    Node fibo = makeFuncSub(&sub, NULL);

    calc(&add);
    calc(&mul);
    calc(&sub);
    calc(&fibo);

    return 0;
}

void calc(Node *node)
{
    char *nodeName = GET_VARIABLE_NAME(node);
    TypeTag typeTag = node->type;
    int a = node->a;
    int b = node->b;
    ll result = node->result;
    if (result == -1) {
        if (typeTag == DIV) {
            if (a == 0) {
                perror("Error: Division by zero\n");
                return;
            }
        }
        else if (typeTag == ADD_FIB || typeTag == SUB_FIB 
                || typeTag == MUL_FIB || typeTag == DIV_FIB)
        {
            perror("Error: No Fibonacci Number at negative index\n");
            return;
        }
    }
    printf("%s : %lld\n", nodeName, result);
}

void calcNodeResult(Node *node)
{
    TypeTag typeTag = node->type;
    int a = (node->a) ? node->a : 0;
    int b = (node->b) ? node->b : 0;
    ll sum, sub, prod, div;
    ull fibo;
    switch (typeTag)
    {
    case ADD:
        sum = b + a;
        node->result = sum;
        break;
    case SUB:
        sub = b - a;
        node->result = sub;
        break;
    case MUL:
        prod = b * a;
        node->result = prod;
        break;
    case DIV:
        if (a != 0)
            div = b / a;
        else
            div = -1;
        node->result = div;
        break;
    case ADD_FIB:
        sum = b + a;
        if (sub <= 0) {
            node->result = -1;
            break;
        }
        if (sum >= 1e6) {
            fibo = fibLargeN(sum - 1);
        } else {
            fibo = fibArray[sum - 1];
        }
        node->result = fibo;
        break;
    case SUB_FIB:
        sub = b - a;
        if (sub <= 0) {
            node->result = -1;
            break;
        }
        if (sub >= 1e6) {
            fibo = fibLargeN(sub - 1);
        } else {
            fibo = fibArray[sub - 1];
        }
        node->result = fibo;
        break;
    case MUL_FIB:
        prod = b * a;
        if (prod <= 0) {
            node->result = -1;
            break;
        }
        if (prod >= 1e6) {
            fibo = fibLargeN(prod - 1);
        } else {
            fibo = fibArray[prod - 1];
        }
        node->result = fibo;
        break;
    case DIV_FIB:
        if (a != 0)
            div = b / a;
        else 
            div = -1;
        if (div <= 0) {
            node->result = -1;
            break;
        }
        if (div >= 1e6) {
            fibo = fibLargeN(div - 1);
        } else {
            fibo = fibArray[div - 1];
        }
        node->result = fibo;
        break;
    default:
        break;
    }
}

void fib()
{
    fibArray[0] = 0;
    fibArray[1] = 1;
    for (int i = 2; i < 1e4; i++) {
        fibArray[i] = fibArray[i - 1] + fibArray[i - 2];
    }
}

ull fibLargeN(int n)
{
    ull first = fibArray[9998];
    ull second = fibArray[9999];
    ull temp;
    for (int i = 1e4; i <= n; i++) {
        temp = first + second;
        first = second;
        second = temp;
    }

    return second;
}