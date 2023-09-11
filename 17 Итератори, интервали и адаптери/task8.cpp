// Да се напише фунцкия bool palindrom (...), която проверява дали редицата от 
// елементите на даден контейнер обрзува палиндром (т.е. дали се чете еднакво 
// както отляво надясно така и отдяно наляво).

#include <iostream>

template<template <typename> class Container, typename T>
bool palindrom(const Container<T>& container){
    T& start = container.begin();
    T& end = std::prev(container.end());

    while(start < end){
        if(*start != *end){
            return false;
        }
        start++;
        end--;
    }
    return true;
}