
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Time
{
    short h = 0;
    short m = 0;
    short s = 0;

    bool operator<(const Time& other) const
    {
        if (h != other.h) return h < other.h;
        if (m != other.m) return m < other.m;
        return s < other.s;
    }
};

class Train
{
private:
    int number;
    Time departureTime;
    string destination;

public:

    Train() : number(0) {}

    Train(int number, Time time, string destination)
        : number(number), departureTime(time), destination(destination) {
    }

    int getNumber() const
    {
        return number;
    }

    Time getTime() const
    {
        return departureTime;
    }

    string getDestination() const
    {
        return destination;
    }

    void setTime(Time time)
    {
        departureTime = time;
    }

    void Show() const
    {
        cout << "Train: " << number
            << " | Time: "
            << departureTime.h << ":"
            << setw(2) << setfill('0') << departureTime.m << ":"
            << setw(2) << departureTime.s
            << setfill(' ')
            << " | Destination: " << destination << endl;
    }

    friend ostream& operator<<(ostream& out, const Train& train)
    {
        out << train.number << " "
            << train.departureTime.h << " "
            << train.departureTime.m << " "
            << train.departureTime.s << " "
            << quoted(train.destination);

        return out;
    }

    friend istream& operator>>(istream& in, Train& train)
    {
        in >> train.number
            >> train.departureTime.h
            >> train.departureTime.m
            >> train.departureTime.s
            >> quoted(train.destination);

        return in;
    }
};

class Railway
{
private:
    vector<Train> trains;

public:

    void AddTrain()
    {
        int number;
        Time time;
        string destination;

        cout << "Enter train number: ";
        cin >> number;

        cout << "Enter departure time (h m s): ";
        cin >> time.h >> time.m >> time.s;

        cout << "Enter destination: ";
        cin.ignore();
        getline(cin, destination);

        trains.push_back(Train(number, time, destination));

        cout << "Train added!\n";
    }

    void ShowAll()
    {
        for (int i = 0; i < trains.size(); i++)
        {
            trains[i].Show();
        }
    }

    void FindTrain(int number)
    {
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                trains[i].Show();
                return;
            }
        }

        cout << "Train not found!\n";
    }

    void EditTime(int number)
    {
        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getNumber() == number)
            {
                Time time;

                cout << "Enter new time (h m s): ";
                cin >> time.h >> time.m >> time.s;

                trains[i].setTime(time);

                cout << "Time updated!\n";
                return;
            }
        }

        cout << "Train not found!\n";
    }

    void SortTrains()
    {
        sort(trains.begin(), trains.end(),
            [](const Train& a, const Train& b)
            {
                return a.getTime() < b.getTime();
            });

        cout << "Trains sorted!\n";
    }

    void ShowByDestination(string destination)
    {
        bool found = false;

        for (int i = 0; i < trains.size(); i++)
        {
            if (trains[i].getDestination() == destination)
            {
                trains[i].Show();
                found = true;
            }
        }

        if (!found)
            cout << "No trains found!\n";
    }
    void SaveToFile()
    {
        ofstream file("trains.txt");

        if (!file.is_open())
        {
            cout << "File error!\n";
            return;
        }

        for (int i = 0; i < trains.size(); i++)
        {
            file << trains[i] << endl;
        }

        file.close();

        cout << "Data saved!\n";
    }

    void LoadFromFile()
    {
        ifstream file("trains.txt");

        if (!file.is_open())
        {
            cout << "File error!\n";
            return;
        }

        trains.clear();

        Train train;

        while (file >> train)
        {
            trains.push_back(train);
        }

        file.close();

        cout << "Data loaded!\n";
    }
};

int main()
{
    Railway railway;

    int choice;

    do
    {
        cout << "\n===== RAILWAY STATION =====\n";
        cout << "1. Add train\n";
        cout << "2. Show all trains\n";
        cout << "3. Find train\n";
        cout << "4. Edit departure time\n";
        cout << "5. Sort trains\n";
        cout << "6. Show by destination\n";
        cout << "7. Save to file\n";
        cout << "8. Load from file\n";
        cout << "0. Exit\n";

        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            railway.AddTrain();
            break;

        case 2:
            railway.ShowAll();
            break;

        case 3:
        {
            int number;
            cout << "Enter number: ";
            cin >> number;
            railway.FindTrain(number);
            break;
        }

        case 4:
        {
            int number;
            cout << "Enter number: ";
            cin >> number;
            railway.EditTime(number);
            break;
        }

        case 5:
            railway.SortTrains();
            break;

        case 6:
        {
            string destination;
            cout << "Enter destination: ";
            cin.ignore();
            getline(cin, destination);
            railway.ShowByDestination(destination);
            break;
        }

        case 7:
            railway.SaveToFile();
            break;

        case 8:
            railway.LoadFromFile();
            break;

        case 0:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Wrong choice!\n";
        }

    } while (choice != 0);

    return 0;
}

