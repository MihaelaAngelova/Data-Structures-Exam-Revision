// Да се напише функция bool duplicates (...), която проверява дали в контейнер има дублиращи се елементи.

template <template <typename> class Container, typename T>
bool duplicates(const Container<T>& container){
    for(T& element = container.begin(); element != container.end(); element++){
        for(T& another = std::next(element); another != container.end(); another++){
            if(*element == *another){
                return true;
            }
        }
    }
    return false;
}