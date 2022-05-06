#include<iostream>
#include <sstream>
#include <iomanip>
#include "NotationConverter.hpp"
#include <string>
//Ahmed El Maliki
// This file defines all the mothods in headerfile

NotationConverter::NotationConverter():NotationConverterInterface()// constructor
{

    head = new DoublyNode;
    trail= new DoublyNode;
    head->next=trail;
    trail->prev=head;


}

NotationConverter::~NotationConverter(){// deconstructor


    while (!is_empty()) deletefront();
    delete head;
    delete trail;
 }



std::string NotationConverter::deletefront(){// popfront

 std::string temp=head->data;
 DoublyNode* old = head;
 head = old->next;
 delete old;
 number_of_nodes--;
 return temp;

}
std::string NotationConverter::deleteback(){//popback

std::string temp=trail->data;
DoublyNode* old = trail;
trail=old->prev;
delete old;
number_of_nodes--;
return temp;

}

void NotationConverter:: addfront(std::string s){//pushfront




DoublyNode* temp = new DoublyNode;
temp->data=s;
temp->next=head;
head=temp;
number_of_nodes++;

}





void NotationConverter:: addback(std::string s){//pushback
DoublyNode* temp = new DoublyNode;
temp->data=s;
temp->prev=trail;
trail=temp;
number_of_nodes++;

}

std::string NotationConverter::getback(){//top_back

return trail->data;


}


std::string  NotationConverter::getfront(){//top_front


return head->data;
}


int NotationConverter::listSize(){

return number_of_nodes;
}

std::string NotationConverter::postfixToInfix(std::string inStr) {


    std::stringstream ss(inStr);

    while(!ss.eof()) {

        std::string ret;
        std::string temp;

        temp += ss.get();
         if(isBadInput(temp))
            throw("Error: Bad input");

        if(isSpace(temp)) {
            continue;
        }


        else if(isOperator(temp)) {

            ret += "(" + deletefront() + " " + temp + " " + deletefront() + ")";
            addfront(ret);

        }



        else if(isAlpha(temp)) {

            addfront(temp);
        }


        else {

            continue;

        }

    }

    return getfront();
}






std::string NotationConverter::postfixToPrefix(std::string inStr){


    std::stringstream ss(inStr);

    while(!ss.eof()) {

        std::string ret;

        std::string temp;

        temp += ss.get();
        if(isBadInput(temp))
            throw("Error: Bad input");





        if(isSpace(temp)) {

            continue;

        }


        else if(isAlpha(temp)) {

            addfront(temp);

        }





        else if(isOperator(temp)) {

            ret += temp + " " + deletefront() + " " + deletefront();
            addfront(ret);

        }



        else {

            continue;

        }

    }

    return getfront();

}







std::string NotationConverter::infixToPostfix(std::string inStr) {



    std::string ret;

    std::stringstream ss(inStr);

    while(!ss.eof()) {

        int curPrec = 0;

        std::string temp;

        temp += ss.get();
        if(isBadInput(temp))
            throw("Error: Bad input");



        if(isOperator(temp)) {
            curPrec = assignPrec(temp);

        }

        if(isSpace(temp)) {

            continue;

        }

        else if(isAlpha(temp)) {

            ret += " " + temp;

        }

        else if(temp == "(") {

            addfront(temp);

        }

        else if(temp == ")") {

            while(!is_empty() && getfront() != "(")
                ret += " " + deletefront();
            if(!is_empty() && getfront() == "(")
                deletefront();

        }

        else if(isOperator(temp)) {

            while(!is_empty() && curPrec <= assignPrec(getfront()))
                ret += " " + deletefront();

            addfront(temp);

        }

    }

    while(!is_empty())
        ret += " " + deletefront();

    return ret.substr(1);

}



std::string NotationConverter::infixToPrefix(std::string inStr) {



    std::string temporary=inStr;
    std::string clone=infixToPostfix(temporary);
    std::string result= postfixToPrefix(clone);
    while(!is_empty())
    deletefront();//clearstack

    return result;


}



std::string NotationConverter::prefixToInfix(std::string inStr) {


    std::string rev;

    for(int i = inStr.length()-1; i > -1; i--)

        rev += inStr.at(i);

    std::stringstream ss(rev);

    while(!ss.eof()) {

        std::string ret;

        std::string temp;

        temp += ss.get();
        if(isBadInput(temp))
            throw("Error: Bad input");




        if(isSpace(temp)) {

            continue;

        }

        else if(isAlpha(temp)) {

            addfront(temp);

        }

        else if(isOperator(temp)) {

            std::string temp_a = deletefront();

            std::string temp_b = deletefront();

            ret += "(" + temp_a + " " + temp + " " + temp_b + ")";

            addfront(ret);
        }

    }


    return getfront();

}


std::string NotationConverter::prefixToPostfix(std::string inStr) {

    std::string temporary=inStr;
    std::string clone=prefixToInfix(temporary);
    std::string result=infixToPostfix(clone);
    while(!is_empty())
    deletefront();//clearstack
    return result;

}



bool NotationConverter::isOperator(const std::string &s) {

    bool ret = false;

    if (s == "+" || s == "-" || s == "*" || s == "/")
        ret = true;

    return ret;

}



bool NotationConverter::isAlpha(const std::string &s) {

    bool ret = false;

    if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" || s == "F" || s == "G" || s == "H" || s == "I" || s == "J" || s == "K" || s == "L" || s == "M" || s == "N" || s == "O" || s == "P" || s == "Q" || s == "R" ||s == "S" || s == "T" || s == "U" || s == "V" || s == "W" || s == "X" || s == "Y" || s == "Z" || s == "a" || s == "b" || s == "c" || s == "d" || s == "e" || s == "f" || s == "g" || s == "h" || s == "i" || s == "j" || s == "k" || s == "l" || s == "m" || s == "n" || s == "o" || s == "p" || s == "q" || s == "r" ||s == "s" || s == "t" || s == "u" || s == "v" || s == "w" || s == "x" || s == "y" || s == "z")
        ret = true;

    return ret;

}



bool NotationConverter::isSpace(const std::string &s) {

    bool ret = false;

    if (s == " ")
        ret = true;

    return ret;

}


bool NotationConverter::isBadInput(const std::string &s) {

    bool ret = false;

    if (s == "!" || s == "@" || s == "#" || s == "%" || s == "^" || s == "&" || s == "_" || s == "=" || s == "{" || s == "}" || s == "[" || s == "]" || s == "|" || s == "\\" || s == "\"" || s == "'" || s == "<" || s == ">" ||s == "," || s == "." || s == "~" || s == "`" || s == "?" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9" || s == "0")
        ret = true;

    return ret;

}



int NotationConverter::assignPrec(const std::string &s) {

    int ret;

    if(s == "+")
        ret = 1;

    else if(s == "-")
        ret = 2;

    else if(s == "/")
        ret = 3;

    else if(s == "*")
        ret = 4;

    else
        ret = 0;

    return ret;
}
