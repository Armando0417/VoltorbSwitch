#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class A {

    public:
        int a;
        int b;

        A() {
            a = 5;
            b = 5;
        }

        virtual void upgrade() {
            a = 10;
        }


};

class B : public A {

    public:
        B() {
            a = 5;
            b = 5;
        }
        void upgrade() override {
            b = 10;
        }

};

int main() {

    std::vector<unique_ptr<A>> v;

    v.push_back(make_unique<A>());
    v.push_back(make_unique<B>());


    v[0]->upgrade();


    cout << v[0]->a << endl;

    v[1]->upgrade();

    cout << v[1]->b << endl;


    return 0;
}