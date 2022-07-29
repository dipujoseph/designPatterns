#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/*
SOLID : First one -Single responsibility principle
Real life example :  Code developer should not be handling office stationery management
Code example
 Jounnal entry class should handle only add, removal of entries
 Saving/Persistance should not be handled. Reason
1. There might be other classes also which need to be saved. So this could be managed by a seperate class e.g Persistance Manager :) 
2.May decide to save to database instead of file. All class would have to undergo change

*/
struct Journal
{
  string title;
  vector<string> entries;

  explicit Journal(const string& title)
    : title{title}
  {
  }

  void add(const string& entry);

  // persistence is a separate concern
  void save(const string& filename);
};

void Journal::add(const string& entry)
{
  static int count = 1;
  entries.push_back(std::to_string(count++)
    + ": " + entry);
}

void Journal::save(const string& filename)
{
  ofstream ofs(filename);
  for (auto& s : entries)
  {
    ofs << s << endl;
    cout <<s <<endl;
  }
}

struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto &s : j.entries)
    {
      ofs << s << endl;
      cout << s;
    }
  }
};

int main()
{
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  //journal.save("diary.txt");

  PersistenceManager pm;
  pm.save(journal, "diary.txt");
}