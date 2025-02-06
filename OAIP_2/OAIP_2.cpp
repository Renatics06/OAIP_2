#include <iostream>
#include <Windows.h>

using namespace std;

struct Queue { 
    int info;
    Queue *next, *prev;
}*begin, *end;

void InQueue(Queue** b, Queue** e, int in) {
    Queue* t = new Queue;
    t->info = in;   
    *b = *e = t;
    t->next = t->prev = NULL;
}

void Add_Queue(int kod, Queue** b, Queue** e, int in) {
    Queue* t = new Queue;
    t->info = in;
    if (kod == 0) {
        t->prev = NULL;
        t->next = *b;
        (*b)->prev = t;
        *b = t;
    }
    else {
        t->next = NULL;
        t->prev = *e;
        (*e)->next = t;
        *e = t;
    }
}

void View(int kod, Queue* t) {
    while (t != NULL) {
        cout << t->info << endl;
        if (kod == 0) t = t->next;
        else t = t->prev;
    }
}

void Del_All(Queue** p) {
    while (*p != NULL) {
        Queue* t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void Del_chet(Queue*& b, Queue*& e)
{
    while (b != NULL && b->info % 2 == 0)
    {
        Queue* del = b;
        b = b->next;
        if (b != NULL) b->prev = NULL;
        delete del;
    }
    if (b == NULL){
        e = NULL;
        return;
    }
    else if (b->next == NULL)
    {
        return;
    }
    Queue* t = b;
    while (t->next->next)
    {
        if (t->next->info % 2 == 0)
        {
            Queue* del = t->next;
            t->next = t->next->next;
            t->next->prev = t;
            delete del;
        }
        else
        {
            t = t->next;
        }
    }
    if (e->info % 2 == 0)
    {
        Queue* del = e;
        e = t;
        e->next = NULL;
        delete del;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Queue *begin = NULL, *end = NULL;
    int choise, i, in, n, kod1;

    bool check = false;

    char Str[2][10] = { "Begin ", "End " };

    while (true)
    {
        cout << "1.Создать очередь\n2.Добавить элемент в очередь\n3.Посмотреть очередь\n" <<
            "4.Удалтить четные\n" <<
            "5.Удалить очередь\n0.Выход\n";
        cin >> choise;
        /*if (choise == 2 || check == false) cout << "Сначала создать надо >:( !!!\n"; choise = 1; cout << "Я сам выберу 1 потому что ты тупой\n";*/
        if (choise == 1) {
            if (begin != NULL) {
                Del_All(&begin);
                cout << "Память очищена!\n";
            }
            else
            {
                cout << "Очередь создана\n";
                cout << "Введите число\n";
                cin >> in;
                InQueue(&begin, &end, in);
                check = true;
            }
        }
        else if (choise == 2) {
            Queue *t;
            cout << "Info = "; cin >> in;
            cout << "Add Begin - 0, Add End - 1 : "; cin >> kod1;
            Add_Queue(kod1, &begin, &end, in);
            if (kod1 == 0) t = begin;
            else t = end;
            cout << "Add to " << Str[kod1] << " " << t->info << endl;
        }
        else if (choise == 3) {
            cout << "View Begin - 0, View End - 1 : ";  cin >> kod1;
            Queue* t;
            if (kod1 == 0) {
                t = begin;
                cout << "-- Begin --" << endl;
            }
            else {
                t = end;
                cout << "--- End --" << endl;
            }
            View(kod1, t);
        }
        else if (choise == 4) {
            if (begin == NULL) continue;
            Add_Queue(0, &begin, &end, 99);
            Del_chet(begin, end);
            begin = begin->next;
            begin->prev = NULL;
        }
        else if (choise == 5) {
            Del_All(&begin);
        }
        else if (choise == 0) {
            break;
        }
        continue;
    }
    return 0;

}