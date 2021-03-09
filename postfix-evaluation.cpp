#include <iostream>
#include <stack>
#include <ctype.h>
#include <string>
#include <cmath>

using namespace std;

struct node {
    string data;
    node* left = nullptr; 
    node* right = nullptr;
};

node* newNode(char data) {
    node* n = new node;
    string tmp = "";
    tmp += data;
    n->data = tmp;
    return n;
}

node* build(string& expression) {
    expression = '(' + expression + ')';
    stack<node*> nodeStack;
    stack<char> charStack;

    // Term1, Term2, Operation
    node *t1, *t2, *op;

    // Priority
    int p[1 << 7] = {0};

    p['+'] = p['-'] = 1;
    p['/'] = p['*'] = 2;
    p['^'] = 3;
    p[')'] = 0;

    for (size_t i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ') {
            cout << '.';
            continue;
        }
        if (expression[i] == '(')
            charStack.push(expression[i]);
        // Place the operands in the node stack
        else if (isalpha(expression[i]) || isdigit(expression[i])) {
            if (i > 0 && isalpha(expression[i - 1]) || isdigit(expression[i - 1]))
                t1->data += expression[i];
            else {
                t1 = newNode(expression[i]);
                nodeStack.push(t1);
            }
        }
        // Encountered an operator
        else if (p[expression[i]] > 0) {
            while (!charStack.empty() && charStack.top() != '(' 
                && ((expression[i] != '^' && p[charStack.top()] >= p[expression[i]])
                    || (expression[i] == '^' && p[charStack.top()] > p['^']))) {
                    
                op = newNode(charStack.top());
                charStack.pop();

                t1 = nodeStack.top();
                nodeStack.pop();
                
                t2 = nodeStack.top();
                nodeStack.pop();

                op->right = t1;
                op->left = t2;

                nodeStack.push(op);
            }
            
            charStack.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!charStack.empty() && charStack.top() != '(') {
                op = newNode(charStack.top());
                charStack.pop();

                t1 = nodeStack.top();
                nodeStack.pop();
                
                t2 = nodeStack.top();
                nodeStack.pop();

                op->right = t1;
                op->left = t2;

                nodeStack.push(op);
            }
            charStack.pop();
        }
    }
    op = nodeStack.top();
    return op;
}

void postfix(node* root) {
    if (root) {
        postfix(root->left);
        postfix(root->right);
        cout << root->data << ' ';
    }
}

int toInt(string s)  
{  
    int num = 0, i = 0;  

    if(s[0] == '-') ++i;
        
    for (; i < s.length(); i++)  
        num = num * 10 + (int(s[i]) - 48);    
    
    if(s[0] == '-') num *= -1;
        
    return num;  
}  

double eval(node* root) {
    if (!root)
        return 0;

    if (!root->left && !root->right)  
        return toInt(root->data);  
    
    // Evaluate left subtree  
    double l_val = eval(root->left);  
  
    // Evaluate right subtree  
    double r_val = eval(root->right);  

        // Check which operator to apply  
    if (root->data == "+")  
        return l_val + r_val;  
  
    if (root->data == "-")  
        return l_val -r_val;  
  
    if (root->data == "*")  
        return l_val * r_val;  
  
    if (root->data == "^")
        return pow(l_val, r_val);
    return l_val/r_val;  

}

int main() {
    string s;
    cout << "Input an expression:\n";
    cin >> s;
    node* tree = build(s);
    cout << "= " << eval(tree);
    cout << "\nTo postfix notation: ";
    postfix(tree);
}
