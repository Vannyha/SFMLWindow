#include <SFML/Graphics.hpp>
#include <stdlib.h> // srand, rand
#include <deque>
#include <iostream>

class Window {
public:
    int sizex, sizey;
    int colorR,colorG,colorB;
    int posx,posy;
    int priority = 0;
};

class Manager{
public:
    std::deque<Window> windows; // Контейнер, который никогда не меняет внутри себя порядок окон. Можно только добавить в конце новые или удалить существующие
    int priornow = -1; // Вспомогательная переменная для отслеживания приоритетного окна
    void newindow(){ // Функция создания нового окна со случайным размером, цветом и позицией по x и y
        Window bufferwindow;
        bufferwindow.sizex = rand()%930+20;
        bufferwindow.sizey = rand()%510+20;
        bufferwindow.posx = rand()%930+20;
        bufferwindow.posy = rand()%510+20;
        bufferwindow.colorR = rand()%254+0;
        bufferwindow.colorG = rand()%254+0;
        bufferwindow.colorB = rand()%254+0;
        windows.push_back(bufferwindow);
    };
    void setpriority(int a){
        int size = windows.size();
        if (a >= size){
            a = size - 1;
        }
        a = size - a - 1;
        windows.at(a).priority = 1;
        priornow = a;
    }
    void removepriority() {
        if (priornow != -1) {
            windows.at(priornow).priority = 0;
            priornow = -1;
        }
    }

};


int main()
{
    srand(time(0));
    Manager manager1; // Создаём экземпляр класса "Менеджер окон"
    int p, j, o, pr, i; // Вспомогательные переменные для цикла отрисовки графики.
    char w;
    int num;
    std::cout << "Make new window - n" << std::endl;
    std::cout << "Make a window on top of others - h" << std::endl;
    std::cout << "Return the window to its place - l" << std::endl;





    sf::RenderWindow window(sf::VideoMode(1920, 1080), "test");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(); // Очистка предыдущего кадра

        i = manager1.windows.size(); //Определяем количество открытых окон, которые нужно рисовать
        pr = manager1.priornow;
        for (j = 0; j < i; j++){
            sf::RectangleShape rectangle(sf::Vector2f(manager1.windows.at(j).sizex,manager1.windows.at(j).sizey));
            rectangle.setFillColor(sf::Color(manager1.windows.at(j).colorR,manager1.windows.at(j).colorG,manager1.windows.at(j).colorB));
            rectangle.setPosition(manager1.windows.at(j).posx,manager1.windows.at(j).posy);
            rectangle.setOutlineThickness(10);
            o = j*10;
            if (o > 254){
                o = 254;
            }
            rectangle.setOutlineColor(sf::Color(o, o, o));
            window.draw(rectangle);
        }
        if (pr != -1){
            sf::RectangleShape rectangle(sf::Vector2f(manager1.windows.at(pr).sizex, manager1.windows.at(pr).sizey));
            rectangle.setFillColor(sf::Color(manager1.windows.at(pr).colorR, manager1.windows.at(pr).colorG,
                                             manager1.windows.at(pr).colorB));
            rectangle.setPosition(manager1.windows.at(pr).posx, manager1.windows.at(pr).posy);
            rectangle.setOutlineThickness(10);
            rectangle.setOutlineColor(sf::Color(254, 50, 50));
            window.draw(rectangle);
            p++;
        }



        window.display(); // Отрисовали, ждём команду из консоли, что делать дальше
        std::cin >> w;
        if (w == 'n'){
            manager1.newindow();
        }
        if (w == 'h'){
            if (manager1.priornow == -1){
                std::cout << "Choose number of window" << std::endl;
                std::cin >> num;
                if (num < 0){
                    std::cout << "Number from 0 to" << i-1 << std::endl;
                }
                else {
                    manager1.setpriority(num);
                }
            }
            else {
                std::cout << "First clear the priority for window - 'l'" << std::endl;
            }
        }
        if (w == 'l'){
            manager1.removepriority();
        }



    }

    return 0;
}