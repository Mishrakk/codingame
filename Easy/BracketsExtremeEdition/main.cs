using System;
using System.Collections.Generic;

class Solution
{
    static void Main(string[] args)
    {
        string expression = Console.ReadLine();
        Console.Error.WriteLine(expression);
        Stack<char> stack = new Stack<char>();
        string output = "true";
        for (int i = 0; i < expression.Length; i++)
        {
            char input = expression[i];
            if (input == '(' || input == '[' || input == '{')
            {
                stack.Push(input);
            }
            else if (input == ')' || input == ']' || input == '}')
            {
                if (stack.Count == 0)
                {
                    output = "false";
                    break;
                }
                else if (stack.Peek() == '(' && input == ')' ||
                    stack.Peek() == '[' && input == ']' ||
                    stack.Peek() == '{' && input == '}')
                {
                    stack.Pop();
                }
                else
                {
                    output = "false";
                    break;
                }
            }
        }
        if (stack.Count > 0)
        {
            output = "false";
        }
        Console.WriteLine(output);
    }
}
