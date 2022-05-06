#ifndef NOTATIONCONVERTER_H_INCLUDED
#define NOTATIONCONVERTER_H_INCLUDED
#include <string>
#include"NotationConverterInterface.hpp"
// Ahmed El Maliki- U18019330
// This project will be implemented using a deque
// this deque will be implemented as a stack- The functions for add back and delete back  and get back are defined, but we will not be using them.
// This deque is implemented using a doubly Linked list


class DoublyNode {


        DoublyNode* next;
        DoublyNode* prev;
        std::string data;


        friend class NotationConverter;



};


class NotationConverter: public NotationConverterInterface
{
private:
    DoublyNode* head;
    DoublyNode* trail;

protected:
    void addfront(std::string s);
    void addback(std::string s);
    std::string deletefront();
    std::string deleteback();
    int number_of_nodes=0;


public:
     NotationConverter();
    ~NotationConverter();
    std::string  getfront();
    std::string  getback();
    int listSize();
    bool isOperator(const std::string &s);//helper method
    bool isAlpha(const std::string &s);//helper method
    bool isSpace(const std::string &s);//helper method
    bool isBadInput(const std::string &s);//helper method
    int assignPrec(const std::string &s);//helper method






        bool is_empty() const {// if doubly linked list is empty
             return (number_of_nodes== 0);

        }

         std::string postfixToInfix(std::string inStr) ;
         std::string postfixToPrefix(std::string inStr) ;

         std::string infixToPostfix(std::string inStr) ;
         std::string infixToPrefix(std::string inStr) ;

         std::string prefixToInfix(std::string inStr) ;
         std::string prefixToPostfix(std::string inStr) ;




};




#endif // NOTATIONCONVERTER_H_INCLUDED
