#include "Base.h"
#include "Application.h"

Base::~Base()
{
    for (int i = 0; i < children.size(); ++i) delete children[i];
}

string Base::getName()
{
    return name;
}

void Base::setName(string name)
{
    this->name = name;
}

Base* Base::getParent()
{
    return parent;
}

void Base::setParent(Base* newParent)
{
    if (parent)
    {
        for (int i = 0; i < parent->children.size(); ++i)
        {
            if (parent->children[i] == this) parent->children.erase(parent->children.begin() + i);
        }
    }
    // меняем себе родителя и добавляем себя в список детей нового родителя
    parent = newParent;
    if (parent)
    {
        parent->children.push_back(this);
    }
}


void Base::print(string s)
{
    cout << endl << s << getName();
    for (auto child : children)
        child->print(s + "    ");

}

Base* Base::search(string name)
{
    if (this->name == name)
        return this;
    if (!this->children.empty())
    {
        for (auto ptrChild : this->children)
        {
            auto result = ptrChild->search(name);
            if (result)
                return result;
        }
    }
    return nullptr;
}

bool Base::setState(int s)
{
    if (this->parent == nullptr)
    {
        this->state = s;
        return true;
    }
    if (parent->state == 0 && s != 0)
    {
        return false;
    }
    state = s;
    if (state == 0)
    {
        for (int i = 0; i < children.size(); ++i)
        {
            children[i]->setState(0);
        }
    }
    return true;
}

int Base::getState()
{
    return state;
}

void Base::printWithState(string s)
{
    if (getState() != 0)
        cout << endl << s << getName() << " is ready";
    else
        cout << endl << s << getName() << " is not ready";
    for (auto child : children)
        child->printWithState(s + "    ");
}

// новые или измененные методы

Base::Base(Base* parent, string name, int number)
{
    this->number = number;
    this->name = name;
    this->parent = parent;
    current=this;
    state = 1;
    if (parent){
        parent->children.push_back(this);
    }
}

Base* Base::getByPath(string path)
{
    string name;
    int posOfSlash;

    if (path == "/")
        // это корневой объект
        return this;

    if (path == ".")
        // текущий объект
        return current;

    else if (path.substr(0, 2) == "//")
    {
        // ищем объект по уникальному имени от головного (можно использовать ранееописанный метод поиска по имени)
        name = path.substr(2);
        return search(name);
    }

    // позиция слеша
    // S.find(str, pos = 0) - искать первое входение строки str начиная с позиции pos.
    posOfSlash = path.find('/', 1);
    if (path[0] == '/')
    {
        if (posOfSlash != -1)
            // если есть слеши кроме первого
        {
            // выделяем имя
            name = path.substr(1, posOfSlash - 1);
            // проходимся по детям
            for (auto childPtr : this->children)
            {
                // если среди них есть ребенок с таким именем
                if (childPtr->getName() == name)
                {
                    // рекурсивно возвращаем (для следующего)
                    return childPtr->getByPath(path.substr(posOfSlash));
                }
            }
        }
        else
            // если слеш только в начале
        {
            name = path.substr(1);
            // извлекли имя

            // ищем нужного среди детей
            for (auto childPtr : this->children)
            {
                if (childPtr->getName() == name)
                    return childPtr;
            }
        }
    }
    // если координата задана относительно текущего
    if (path[0] != '/' && path.find('/') != -1)
        // ищем этот объект от текущего (используя метод рекурсивно)
        return current->getByPath("/" + path);
    return nullptr;

}

void Base::setCurrent(Base* current)
{
    this->current = current;
}
Base* Base::getCurrent()
{
    return current;
}

// new

void Base::setConnection(Base* c, TYPE_SIGNAL s, TYPE_HANDLER h)
// установка связи
{
    connections.push_back(new Connection(c, s, h));
}

void Base::deleteConnection(Base* c, TYPE_SIGNAL s, TYPE_HANDLER h)
// удаление связи
{
    for (int i = 0; i < connections.size(); ++i)
    {
        if (connections[i]->connected == c && connections[i]->signal == s && connections[i]->handler == h)
            connections.erase(connections.begin() + i);
    }
}

void Base::emitSignal(TYPE_SIGNAL s, string str)
// отправка сигнала
{
    // если объект не готов
    if (state == 0) return;

    // отправляем сигнал
    (this->*s)(str);
    for (int i = 0; i < connections.size(); ++i)
    {
        if (connections[i]->signal == s)
        {
            // получаем сигнал
            if (connections[i]->connected->state != 0) (connections[i]->connected->*connections[i]->handler)(str);
        }
    }
}

int Base::getNumber()
{
    return number;
}



string Base::getPath()
// возвращает полный путь
{
    if (!parent) return "/";
    string path = getName();
    Base* ptr = parent;
    while (ptr->getParent())
    {
        path = ptr->getName() + "/" + path;
        ptr = ptr->getParent();
    }
    return "/" + path;
}

