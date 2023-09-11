// Да се дефинира функция map, която прилага едноаргументна 
// функция f : int → int към всеки от елементите на произволен 
// контейнер с числа (int). Да се дефнира и шаблон на функцията 
// за контейнер с произолен тип на елементите.

#include <iostream>
#include <functional>
#include <vector>

template<template <typename> class Container, typename T>
void map(const Container<T>& container, std::function<T(T)>f){
       for(T& i: container){
        i = f(i);
       }
}
