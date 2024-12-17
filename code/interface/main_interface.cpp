#include<iostream>
#include "../src/card-deck/CardDeck.h"

int main() {
    CardDeck deck; // Создаём колоду по умолчанию (52 карты)
    int choice;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать колоду с указанным количеством карт\n";
        std::cout << "2. Добавить случайную карту\n";
        std::cout << "3. Удалить карту по индексу\n";
        std::cout << "4. Получить карту по индексу\n";
        std::cout << "5. Отсортировать карты\n";
        std::cout << "6. Перемешать карты\n";
        std::cout << "7. Соединить две колоды (+)\n";
        std::cout << "8. Проверить на дубликаты (is_twink)\n";
        std::cout << "9. Найти карты по масти\n";
        std::cout << "10. Вывести количество карт в колоде\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";

        while (!(std::cin >> choice)) {
            std::cout << "Неверный ввод. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                int new_count;
                std::cout << "Введите количество карт: ";
                std::cin >> new_count;
                deck = std::move(CardDeck(new_count));
                break;
            }
            case 2: deck.addRandomCard(); break; 
            case 3: {
                int index;
                std::cout << "Введите индекс карты для удаления: ";
                std::cin >> index;
                try {
                    deck.deleteCardByIndex(index);
                } catch (const std::out_of_range& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 4: {
                int index;
                std::cout << "Введите индекс карты: ";
                std::cin >> index;
                if(index > deck.getCount() - 1){
                    std::cout << "Не верный индекс";
                }
                else{
                    std::cout << deck.getCards()[index]->outputCard();
                }
                 break;
            }
            case 5: {
                bool reversed;
                std::cout << "Обратный порядок сортировки (1 - да, 0 - нет): ";
                std::cin >> reversed;
                deck.sortCards(reversed);
                break;
            }
            case 6: deck.shuffle(); break;
            case 7: {
                CardDeck deck2(20); // Создаем вторую колоду для примера
                deck = deck + deck2;
                break;
            }
            case 8: std::cout << "Есть ли дубликаты: " << deck.is_twink() << std::endl; break;
            case 9: {
                int suit;
                std::cout << "Введите номер масти (0-3): ";
                std::cin >> suit;
                CardDeck suitDeck = deck.suitFinder(suit);
                std::cout << "Количество карт в найденной масти: " << suitDeck.getCount() << std::endl;
                break;
            }
            case 10: std::cout << "Количество карт в колоде: " << deck.getCount() << std::endl; break;
            case 0: {
                std::cout << "Выход...\n";
                break;
            }
            default: std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);

    return 0;
}

