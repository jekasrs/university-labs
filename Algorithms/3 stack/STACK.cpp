#include <iostream>
#include "StackArray.cpp"
bool TestEvaluate();
bool TestSteck();
bool CheckBalanceBrackets(const char* , int stackSize = 30);
bool GetPostfixFromInfix(const char* infix, char* postfix, size_t stackSize = 30);
int EvaluatePostfix(const char* infix, size_t stackSize = 30);
bool TestCheckBalanceBrackets();

int main()
{
  setlocale(LC_ALL, "Rus");
  TestCheckBalanceBrackets();
  TestSteck();
  TestEvaluate();
  return 0;
}

bool CheckBalanceBrackets(const char* text, int stackSize) {
  StackArray<char> stack(stackSize);
  bool isTrue = true;
  try {
    for (int i = 0; *(text + i) != '\0' && isTrue == true; i++) {
      switch (*(text + i))
      {
      case '(': stack.push(*(text + i)); break;
      case '[': stack.push(*(text + i)); break;
      case '{': stack.push(*(text + i)); break;
      case ')':
        if (stack.pop() != '(')
        {
          isTrue = false;
        }
        break;
      case ']':
        if (stack.pop() != '[')
        {
          isTrue = false;
        }
        break;
      case '}':
        if (stack.pop() != '{')
        {
          isTrue = false;
        }
      }
    }
  }
  catch (...) {
    return false;
  }
  if (stack.getTop()) {
    return false;
  }
  else return isTrue;
}
bool GetPostfixFromInfix(const char* infix, char* postfixi, size_t stackSize) {
  StackArray<char> stack(stackSize);
  bool isTrue = true;
  char lastInStack;
  int num = 0;
  char pre_item = ' ';
  int availableSigns = 0;
  int i = 0;
  
  try {
    if (!CheckBalanceBrackets(infix, stackSize)) {
      throw std::invalid_argument("Ошибка в скобках!");
      return false;
    }
    for (i; *(infix + i) != '\0' && isTrue == true; i++) {
      if (!((*(infix + i) > 41) && (*(infix + i) < 58)) && *(infix + i) != ' ' && *(infix + i) != '(' && *(infix + i) != ')') {
        throw std::invalid_argument("Incorrect symbols");
      }
      switch (*(infix + i)) {

      case '(':
        availableSigns++;
        stack.push(*(infix + i));
        pre_item = '(';
        break;

      case '0':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '0';
        num++;
        pre_item = '0';
        break;

      case '1':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '1';
        num++;
        pre_item = '1';
        break;
      case '2':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '2';
        num++;
        pre_item = '2';
        break;
      case '3':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '3';
        num++;
        pre_item = '3';
        break;
      case '4':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '4';
        num++;
        pre_item = '4';
        break;
      case '5':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '5';
        num++;
        pre_item = '5';
        break;
      case '6':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '6';
        num++;
        pre_item = '6';
        break;
      case '7':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '7';
        num++;
        pre_item = '7';
        break;
      case '8':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '8';
        num++;
        pre_item = '8';
        break;
      case '9':
        if (pre_item > 47 && pre_item < 58) throw std::invalid_argument("Incorrect number");
        *(postfixi + num) = '9';
        num++;
        pre_item = '9';
        break;

      case '+':
        if (pre_item > 41 && pre_item < 48) throw std::invalid_argument("Incorrect signs");
        if (availableSigns==0)  throw std::invalid_argument("Не полная скобочная форма");
        pre_item = '+';
        stack.push(*(infix + i));
        availableSigns--;
        break;
      case '-':
        if (pre_item > 41 && pre_item < 48) throw std::invalid_argument("Incorrect signs");
        if (availableSigns == 0)  throw std::invalid_argument("Не полная скобочная форма");
        if (pre_item == '(') {
          *(postfixi + num) = '0';
          num++;
        }
        pre_item = '-';
        stack.push(*(infix + i));
        availableSigns--;
        break;
      case '/':
        if (pre_item > 41 && pre_item < 48) throw std::invalid_argument("Incorrect signs");
        if (availableSigns == 0)  throw std::invalid_argument("Не полная скобочная форма");
        pre_item = '/';
        stack.push(*(infix + i));
        availableSigns--;
        break;
      case '*':
        if (pre_item > 41 && pre_item < 48) throw std::invalid_argument("Incorrect signs");
        if (availableSigns == 0)  throw std::invalid_argument("Не полная скобочная форма");
        pre_item = '*';
        stack.push(*(infix + i));
        availableSigns--;
        break;
      case ')':
        do {
          lastInStack = stack.pop();
          if (lastInStack != '(') {
            *(postfixi + num) = lastInStack;
            num++;
          }

        } while (lastInStack != '(');

      }
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what()<< std::endl;
    return false;
  }
  if (i == 1) return false;
  else return true;
}
int EvaluatePostfix(const char* infix, size_t stackSize) { 
  StackArray<int> stack(stackSize);
  int tempsub = 0;
  int tempdev = 0;
  char* postfixi = new char[stackSize];
  try {
    if (!(GetPostfixFromInfix(infix, postfixi, stackSize))){
      throw std::invalid_argument("Incorrect Formula");
    }
    

    for (int i = 0; *(postfixi + i) != '\0'; i++) { // ( + )
      switch (*(postfixi + i)) {

      case '0': stack.push(0); break;
      case '1': stack.push(1); break;
      case '2': stack.push(2); break;
      case '3': stack.push(3); break;
      case '4': stack.push(4); break;
      case '5': stack.push(5); break;
      case '6': stack.push(6); break;
      case '7': stack.push(7); break;
      case '8': stack.push(8); break;
      case '9': stack.push(9); break;

      case '+':
        stack.push(stack.pop() + stack.pop());
        break;
      case '-':
        tempsub = stack.pop();
        stack.push(stack.pop() - tempsub);
        break;
      case '/':
        tempdev = stack.pop();
        stack.push(stack.pop() / tempdev);
        break;
      case '*':
        stack.push(stack.pop() * stack.pop());
        break;
      }
    }
    delete[] postfixi;
    
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    delete[] postfixi;
    return 3;
  }
  return stack.pop();
}

bool TestCheckBalanceBrackets()
{
  std::cout << std::endl<< "Test TestCheckBalanceBrackets" << std::endl<< std::endl;
  const char* text00 = " ok ";
  std::cout << text00 << ": " << (CheckBalanceBrackets(text00) ? "right" : "wrong") << std::endl;
  const char* text01 = "( ) ok ";
  std::cout << text01 << ": " << (CheckBalanceBrackets(text01) ? "right" : "wrong") << std::endl;
  const char* text02 = "( ( [] ) ) ok ";
  std::cout << text02 << ": " << (CheckBalanceBrackets(text02) ? "right" : "wrong") << std::endl;
  const char* text03 = "( ( [ { } [ ] ( [ ] ) ] ) ) OK";
  std::cout << text03 << ": " << (CheckBalanceBrackets(text03) ? "right" : "wrong") << std::endl;
  const char* text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  std::cout << text04 << ": " << (CheckBalanceBrackets(text04) ? "right" : "wrong") << std::endl;
  const char* text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  std::cout << text05 << ": " << (CheckBalanceBrackets(text05) ? "right" : "wrong") << std::endl;
  const char* text06 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";
  std::cout << text06 << ": " << (CheckBalanceBrackets(text06) ? "right" : "wrong") << std::endl;
  return true;
}
bool TestEvaluate() {
  try {

    std::cout << std::endl<< "Test TestEvaluate" << std::endl<< std::endl;
    
    std::cout << "(1+2*5+1-1*9)" << std::endl;
    std::cout << EvaluatePostfix("(1+2*5+1-1*9)") << std::endl;

    std::cout << "(5 * 3 + 3 * 5)" << std::endl;
    std::cout << EvaluatePostfix("(5 * 3 + 3 * 5)") << std::endl; 

    std::cout << "((5 * 3) + (3 * 5))" << std::endl;
    std::cout << EvaluatePostfix("((5 * 3) + (3 * 5))") << std::endl;

    std::cout << "(2+1)" << std::endl;
    std::cout << EvaluatePostfix("(2+1)") << std::endl;

    std::cout << "(3*0)" << std::endl;
    std::cout << EvaluatePostfix("(3*0)") << std::endl;

    std::cout << "(4/2)" << std::endl;
    std::cout << EvaluatePostfix("(4/2)") << std::endl;

    std::cout << "((-1)+9)" << std::endl;
    std::cout << EvaluatePostfix("((-1)+9)") << std::endl;

    std::cout << "((1-2)*4)" << std::endl;
    std::cout << EvaluatePostfix("((1-2)*4)") << std::endl;

    std::cout << "(((1-2))*(-4))" << std::endl;
    std::cout << EvaluatePostfix("(((1-2))*(-4))") << std::endl;

    std::cout << "((((1+3)*(1+3))*((1+3)*(1+3)))*(((1+3)*(1+3))*((1+3)*(1+3))))" << std::endl;
    std::cout << EvaluatePostfix("((((1+3)*(1+3))*((1+3)*(1+3)))*(((1+3)*(1+3))*((1+3)*(1+3))))", 50) << std::endl;
    
    std::cout << "((11-2)*4)" << std::endl;
    std::cout << EvaluatePostfix("((11-2)*4)") << std::endl;

    std::cout << "(((1a-2))*(-4))" << std::endl;
    std::cout << EvaluatePostfix("(((1a-2))*(-4))") << std::endl;

    std::cout << "((01-2)*4)" << std::endl;
    std::cout << EvaluatePostfix("((01-2)*4)") << std::endl;

    std::cout << "(((1-2))=(-4))" << std::endl;
    std::cout << EvaluatePostfix("(((1-2))=(-4))") << std::endl;

    std::cout << "1" << std::endl;
    std::cout << EvaluatePostfix("1") << std::endl;

    std::cout << "(-1)" << std::endl;
    std::cout << EvaluatePostfix("(-1)") << std::endl;

    std::cout << "( + )" << std::endl;
    std::cout << EvaluatePostfix("( + )") << std::endl;

    std::cout << "(5-2)*3)" << std::endl;
    std::cout << EvaluatePostfix("(5-2)*3)") << std::endl;

    std::cout << "{ 3 + 2 }" << std::endl;
    std::cout << EvaluatePostfix("{ 3 + 2 }") << std::endl;

    std::cout << "[2-2)3)" << std::endl;
    std::cout << EvaluatePostfix("[2-2)3)") << std::endl;

    std::cout << " " << std::endl;
    std::cout << EvaluatePostfix(" ") << std::endl;

    
  }
  catch (std::exception& e) {
    std::cerr << e.what();
    return 3;
  }
  return 0;
}
bool TestSteck() {
  std::cout << std::endl<< "Test TestSteck" << std::endl<<std::endl;
  try {
    StackArray<int> stack1(2);
    stack1.push(20);
    stack1.push(10);
    // stack1.push(1); -- overflow
    // stack1.pop();
    // stack1.pop();
    // stack1.pop();  -- undeflow 
    // StackArray<int> stack2(-1); // --wrongsize

    StackArray<int> stack3(1); // оператор копирования 
    stack3 = stack1;
    std::cout << stack3.pop() << std::endl << stack3.pop() << std::endl;

    StackArray<int> stack4 = std::move(stack1); // конструктор перемещения 
    std::cout << stack4.pop() << std::endl << stack4.pop() << std::endl;
  }
  catch (std::exception& e) {
    std::cerr << e.what();
    return 3;
  }
  return 0;
}