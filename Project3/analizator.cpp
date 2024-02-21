#include "analizator.h"

Analizator::Analizator():
    prefix(Container()), postfix(Container()), stack(Container())
{

}

Analizator::Analizator(int marimeMax):
	prefix(Container(marimeMax)), postfix(Container(marimeMax)), stack(Container(marimeMax))
{

}

Analizator::~Analizator()
{

}

void Analizator::adauga(string str)
{
    bool push = 0;
    int start = 0;
    int end = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (operatori.find(str[i])>=0 && operatori.find(str[i]) < operatori.length())
        {
            
            end = i - 1;
            if (start <= end)
            {
                prefix.push(str.substr(start, end - start + 1));
            }
            prefix.push(str.substr(i,1));
            start = i + 1;
        }
    }
   
    if (start != str.length())
    {
       prefix.push(str.substr(start, str.length() - start));
    }
}

int Analizator::orderOf(char chr)
{
    if (chr == '+' || chr == '-')
        return 1;
    if (chr == '*' || chr == '/')
        return 2;
    if (chr == '^' || chr == '#')
        return 3;
    if (chr == '(')
        return 4;
    if (chr == ')')
        return 5;
    if (chr == '[')
        return 6;
    if (chr == ']')
        return 7;

        return 0;
}

const string Analizator::operatori = "+-^*#/()[]";
void Analizator::prelucreaza()
{
    if (prefix.getMarimeStack() == 0)
    {
        return;
    }
    while (stack.getMarimeStack() != 0)
    {
        stack.pop();
    }

    while (postfix.getMarimeStack() != 0)
    {
        postfix.pop();
    }
    
    while (prefix.getMarimeStack() != 0)
    {
        string str=prefix.pop_back();
        int orderNew = orderOf(str[0]);
        int orderTop = 0;
        

        
        if (stack.getMarimeStack() != 0)
        {   
            orderTop = orderOf(stack[stack.getMarimeStack() - 1][0]);
        }
       
        if (orderNew == 0)
            postfix.push(str);

        if (orderNew == 1)
        {
            if (orderTop == 2 || orderTop == 3)
                postfix.push(stack.pop());
            stack.push(str);
        }

        if (orderNew == 2)
        {
            if (orderTop == 3)
                postfix.push(stack.pop());
            stack.push(str);
        }

        if (orderNew == 3 || orderNew == 4 || orderNew == 6)
            stack.push(str);

        if (orderNew == 5)
        {
            while (orderTop != 4)
            {
                postfix.push(stack.pop());
                orderTop = orderOf(stack[stack.getMarimeStack() - 1][0]);
            }
            stack.pop();
        }

        if (orderNew == 7)
        {
            while (orderTop != 6)
            {
                postfix.push(stack.pop());
                orderTop = orderOf(stack[stack.getMarimeStack() - 1][0]);
                
            }
            stack.pop();
        }
    }

    
    while (stack.getMarimeStack() != 0)
    {
        string str = stack.pop();
        postfix.push(str);
    }
    

}

Container Analizator::getPostfix()
{
    return postfix;
}
Container Analizator::getPreFix()
{
    return this->prefix;
}
Container Analizator::getStack()
{
    return this->stack;
}

void Analizator::setStack(Container _stack)
{
    this->stack = _stack;
}
void Analizator::setPreFix(Container _prefix)
{
    this->prefix = _prefix;
}
void Analizator::setPostFix(Container _postfix)
{
    this->postfix = _postfix;
}
