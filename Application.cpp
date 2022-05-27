#include "Application.h"
#include "Class1.h"
bool Application::buildTreeObjects()
{
    // вместо имени родителя - путь
    string path, childName;
    int cl;
    Base* parentPtr, *childPtr;

    cin >> path;

    setName(path);
    parentPtr = this;

    while (true)
    {
        cin >> path; // считываем путь к родителю
        if (path == "endtree")
        {
            cout << "Object tree";
            print("");
            return true; // дерево построенно и все хорошо
        }

        cin >> childName >> cl;

        parentPtr = getByPath(path); // находим родителя по пути и присваиваем parentPtr

        if (!parentPtr)
        {
            // произошла ошибка в построении дерева
            // (по заданной координате головной объект не найден)
            // например ошибка в наименовании или объекта еще нет в дереве
            cout << "Object tree";
            print("");
            cout << endl << "The head object " << path << " is not found";
            return false;
        }

        switch (cl)
        {
            case 2:
                childPtr = new Cl2(parentPtr, childName);
                break;
            case 3:
                childPtr = new Cl3(parentPtr, childName);
                break;
            case 4:
                childPtr = new Cl4(parentPtr, childName);
                break;
            case 5:
                childPtr = new Cl5(parentPtr, childName);
                break;
            case 6:
                childPtr = new Cl6(parentPtr, childName);
                break;
        }
    }

}

int Application::execApp()
{

    string command;

    while (true)
    {
        cin >> command;
        if (command == "END")
            return 0;


        if (command == "EMIT")
        {
            string path, text;
            cin >> path;
            getline(cin, text);
            if (getByPath(path))
            {
                Base* obj = getByPath(path);
                obj->emitSignal(obj->getSignalPtr(), text);
            } else {
                cout << endl << "Object " << path << " not found";
            }
            continue;
        }
        if (command == "SET_CONNECT")
            // установка связи
        {
            string pathFrom, pathTo;
            cin >> pathFrom >> pathTo;
            if (getByPath(pathFrom))
            {
                if (getByPath(pathTo))
                {
                    getByPath(pathFrom)->setConnection(getByPath(pathTo), getByPath(pathFrom)->getSignalPtr(), getByPath(pathTo)->getHandlerPtr());
                } else {
                    cout << endl << "Handler object " << pathTo << " not found";
                }
            } else {
                cout << endl << "Object " << pathFrom << " not found";
            }
        }

        if (command == "DELETE_CONNECT")
            // удаление
        {
            string pathFrom, pathTo;
            cin >> pathFrom >> pathTo;
            if (getByPath(pathFrom))
            {
                if (getByPath(pathTo))
                {
                    getByPath(pathFrom)->deleteConnection(getByPath(pathTo), getByPath(pathFrom)->getSignalPtr(), getByPath(pathTo)->getHandlerPtr());
                } else {
                    cout << endl << "Handler object " << pathTo << " not found";
                }
            } else {
                cout << endl << "Object " << pathFrom << " not found";
            }
        }
        if (command == "SET_CONDITION")
            // установка готовности объекта
        {
            string path;
            cin >> path;
            int state;
            cin >> state;
            if (getByPath(path))
            {
                getByPath(path)->setState(state);
            } else cout << endl << "Object " << path << " not found";
        }
    }
    return 0;
}

/**
int Application::execApp()
{

	string path, command;

	while (true)
	{
		cin >> command;
		if (command == "END")
			return 0;

		cin >> path;

		if (command == "FIND")
		{
			cout << endl << path; // выводим путь
			if (getByPath(path)) // если такой объект есть - находим его
				cout << "     Object name: " << getByPath(path)->getName();
			else
				cout << "     Object is not found";  // не найден
		}

		if (command == "SET")
		{
			if (getByPath(path)) // если такой объект есть
			{
				setCurrent(getByPath(path)); // устанавливаем его как текущий
				cout << endl << "Object is set: " << getCurrent()->getName(); // выводим
			} else
			{
				cout << endl << "Object is not found: " << getCurrent()->getName() << " " << path;
				continue;
			}
		}
	}
	return 0;
}
*/

// new
void Application::enterConnections()
{
    string from, to;
    while (true)
    {
        cin >> from;
        if (from == "end_of_connections")
        {
            return;
        }
        cin >> to;
        getByPath(from)->setConnection(getByPath(to), getByPath(from)->getSignalPtr(), getByPath(to)->getHandlerPtr());
    }
}

