#include <iostream>
#include <cassert>

class XY {
    int x;
    int y;
public:
    XY(int in_x, int in_y) {
        setXY(in_x, in_y);
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setXY(int in_x, int in_y) {
        x = check(in_x);
        y = check(in_y);
    }

    int check(int i) {
        return i < 0 ? 0 : i;
    }
};

class Window {
    XY *left_up_corner;
    XY *size;
public:
    Window(int in_left_up_corner_x, int in_left_up_corner_y, int in_x, int in_y, XY *monitor_size) {
        left_up_corner = new XY(in_left_up_corner_x, in_left_up_corner_y);
        size = new XY(in_x, in_y);

        assert((monitor_size->getX() - left_up_corner->getX() - size->getX()) > 0);
        assert((monitor_size->getY() - left_up_corner->getY() - size->getY()) > 0);

        std::cout << "Monitor size (" << monitor_size->getX() << ":" << monitor_size->getY() << ")" << std::endl;
        std::cout << "Created new window. Left up corner (" << left_up_corner->getX() << ":" << left_up_corner->getY()
                  << ")" << " size (" << size->getX() << ":" << size->getY() << ")" << std::endl;
    }

    void move(int x, int y, XY *monitor_size) {
        if (((monitor_size->getX() - x - size->getX()) < 0) ||
            ((monitor_size->getY() - y - size->getY()) < 0)) {
            std::cout << "Wrong input!" << std::endl;
        } else {
            left_up_corner->setXY(x, y);
        }
    }

    void resize(int x, int y, XY *monitor_size) {
        if (((monitor_size->getX() - left_up_corner->getX() - x) < 0) ||
            ((monitor_size->getY() - left_up_corner->getY() - y) < 0)) {
            std::cout << "Wrong input!" << std::endl;
        } else {
            size->setXY(x, y);
        }
    }

    XY *getSize() {
        return size;
    }

    XY *getleft_up_corner() {
        return left_up_corner;
    }
};

class Monitor {
    XY *size = nullptr;
    Window *window = nullptr;
public:
    Monitor(int in_x, int in_y) {
        size = new XY(in_x, in_y);
        window = new Window(0, 0, 10, 10, size);
    }

    void display() {
        int c_x = window->getleft_up_corner()->getX();
        int c_y = window->getleft_up_corner()->getY();

        int w_x = window->getSize()->getX();
        int w_y = window->getSize()->getY();

        for (int y = 0; y < size->getY(); ++y) {
            for (int x = 0; x < size->getX(); ++x) {
                if ((c_x <= x) && ((w_x + c_x) > x)
                 && (c_y <= y) && ((c_y + w_y) > y)) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                };
            }
            std::cout << std::endl;
        }
    }

    XY *getSize() {
        return size;
    }

    Window *getWindow() {
        return window;
    }
};

int main() {

    Monitor *monitor = new Monitor(80, 50);

    std::string command;
    do {
        std::cout << "Input command: ";
        std::cin >> command;
        if (command == "move") {
            int x, y;
            std::cout << "input the coordinates of the upper left corner (80 50): ";
            std::cin >> x >> y;
            monitor->getWindow()->move(x, y, monitor->getSize());
        } else if (command == "resize") {
            int x, y;
            std::cout << "input window size (80 50): ";
            std::cin >> x >> y;
            monitor->getWindow()->resize(x, y, monitor->getSize());
        } else if (command == "display") {
            monitor->display();
        }
    } while (command != "close");


    return 0;
}
