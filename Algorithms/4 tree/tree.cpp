#include "BinarySearchTree.h"
#include <iostream>

void testBaseMethods();
void testExtraMethods();

int main()
{
  setlocale(LC_ALL, "rus");
  testBaseMethods();
  testExtraMethods();
  return 0;
}

void testBaseMethods()
{
  std::cout << "Test begin " << std::endl;
  BinarySearchTree<int> tree;

  std::cout << "Add: " << 20 << std::endl;
  tree.insert(6);
  std::cout << "Add: " << 5 << std::endl;
  tree.insert(1);
  std::cout << "Add: " << 4 << std::endl;
  tree.insert(2);
  std::cout << "Add: " << 6 << std::endl;
  tree.insert(10);

  std::cout << "Add: " << 50 << std::endl;
  tree.insert(8);
  std::cout << "Add: " << 60 << std::endl;
  tree.insert(7);
  std::cout << "Add: " << 40 << std::endl;
  tree.insert(14);
  std::cout << "Add: " << 39 << std::endl;
  tree.insert(16);
  std::cout << "Add: " << 41 << std::endl;
  tree.insert(15);
  tree.deleteKey(14);

  std::cout << "\nPrint tree:" << std::endl;
  tree.print(std::cout);

  std::cout << " Инфиксный обход дерева (итеративный):";
  tree.iterativeInorderWalk();

  std::cout << " Инфиксный обход дерева (рекурсивный)";
  tree.inorderWalk();

  std::cout << "\nCount: " << tree.getCount() << std::endl;
  std::cout << "Height: " << tree.getHeight() << std::endl;

  std::cout << "Delete list 39: " << std::endl;
  tree.deleteKey(39);
  tree.print(std::cout);

  std::cout << "Delete root: " << std::endl;
  tree.deleteKey(20);
  tree.print(std::cout);

  std::cout << "Delete inner node: " << 50 << std::endl;
  tree.deleteKey(50);
  tree.print(std::cout);

  std::cout << "Move trees: \n";
  BinarySearchTree<int> treeMove = std::move(tree);
  tree.print(std::cout);
  treeMove.print(std::cout);
}


void testExtraMethods()
{
  std::cout << "\nTest 2 begin " << std::endl;

  BinarySearchTree<int> tree1;
  tree1.insert(0);
  tree1.insert(-10);
  tree1.insert(-11);
  tree1.insert(-9);
  tree1.insert(2);
  tree1.insert(1);
  tree1.insert(3);

  std::cout << "First tree: ";
  tree1.print(std::cout);
  std::cout << "Count: " << tree1.getCount() << std::endl;
  std::cout << "Height: " << tree1.getHeight() << std::endl;

  BinarySearchTree<int> tree2;
  tree2.insert(0);
  tree2.insert(-10);
  tree2.insert(-11);
  tree2.insert(-9);
  tree2.insert(2);
  tree2.insert(1);
  tree2.insert(3);
  std::cout << "Second tree: ";
  tree2.print(std::cout);
  std::cout << "Count: " << tree2.getCount() << std::endl;
  std::cout << "Height: " << tree2.getHeight() << std::endl;

  std::cout << ((tree1 == tree2) ? "Trees are equal\n" : "Trees are not equal\n");

  std::cout << "Delete list 3 :\n " << std::endl;
  tree1.deleteKey(3);
  tree1.print(std::cout);
  tree2.print(std::cout);
  std::cout << ((tree1 == tree2) ? "Trees are equal\n" : "Trees are not equal\n");

}