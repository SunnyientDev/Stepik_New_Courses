#include <iostream>
#include <vector>
using namespace std;

class BasClass
{
public:
	string ObjectName, Path;
  int ClassNum;
  vector <BasClass*> Ders;
	vector <BasClass*>::iterator  it_Der;

//constructor
	BasClass(string ObjectName, int ClassNum, string Path){
    this->ObjectName = ObjectName;
    this->ClassNum = ClassNum;
    this->Path = Path;
  }

//Getters
  string getName(){ return ObjectName; }
  string getPath(){	return Path; }

//Pointers
	BasClass* ObjectSearch(string ObjectName){
    BasClass* ptr;
    if(this->getName() == ObjectName) return this;
    for (BasClass* ind : Ders) { ptr = ind->ObjectSearch(ObjectName); if(ptr != 0) return ptr; }
    return 0;
  }

	BasClass* Ptr1(string PathName){
    string OutPut = "";
    int ind = 1;

    this->Path = PathName;
    while(ind != PathName.length() && PathName[ind] != '/'){ OutPut += PathName[ind]; ind++; }
    PathName.erase(0, ind);

    if (PathName == "") return ObjectSearch("/" + OutPut, OutPut);
      else return Ptr2("/" + OutPut, PathName, ObjectSearch(OutPut));
  }

	BasClass* Ptr2(string Path, string name, BasClass* p_parent){
    string OutPut = "";
    int ind = 1;

    Path = Path + "/";

      while (ind != name.length() && name[ind] != '/') {
        Path += name[ind]; OutPut += name[ind];
        ind++;
      }
      
      name.erase(0, ind);
      if(name == "") return ObjectSearch(Path, OutPut);
      else return Ptr2(Path, name, ObjectSearch(OutPut));
  }

  BasClass* ObjectSearch(string Path, string ObjectName){
    BasClass* ptr;
    if (this->getName() == ObjectName && this->getPath() == Path) return this;
    for (BasClass* ind : Ders) {
      ptr = ind->get_obj1(Path, ObjectName);
      if (ptr != 0) return ptr;
    }
    return 0;
  }

	BasClass* get_obj1(string Path, string ObjectName){
    BasClass* ptr;
    if (this->getName() == ObjectName && this->getPath() + "/" + ObjectName == Path) return this;
    for (BasClass* ind : Ders) {
      ptr = ind->get_obj1(Path, ObjectName);
      if (ptr != 0) return ptr;
    }
    return 0;
  }

	BasClass* KeySymSearch(string KeySym){
    string OutPut = "";
    if (KeySym[0] == '/' && KeySym[1] == '/') {
      KeySym.erase(0, 2);
      return ObjectSearch(KeySym);
    }
    else return Ptr1(KeySym);
  }

//Add function
	void Add(BasClass* p_child){ this->Ders.push_back(p_child); }

//Print functions
	void ShowTree(){ Print(this, 0); }

	void Print(BasClass* RootName, int Lay){
    string Space;
    if(Lay > 0) Space.append(4 * Lay, ' ');
    cout << Space << RootName->getName() << "\n";

    if (RootName->Ders.size() == 0) return;
    RootName->it_Der = RootName->Ders.begin();

    while (RootName->it_Der != RootName->Ders.end()) {
      Print((BasClass*)(*RootName->it_Der), Lay + 1);
      RootName->it_Der++;
    }
  }
};

class Class_1 : public BasClass{
  public:	Class_1(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
};

class Class_2 : public BasClass{
  public: Class_2(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
};

class Class_3 : public BasClass{
  public:	Class_3(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
};

class Class_4 : public BasClass{
  public:	Class_4(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
};

class Class_5 : public BasClass{
  public: Class_5(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
}; 

class Class_6 : public BasClass{
  public: Class_6(string ObjectName, int ClassNum, string Path) :BasClass(ObjectName, ClassNum, Path) {};
};

int main(){
	string RootName, Path; cin >> RootName >> Path;
	int ClassNum, State;
	
	BasClass* MainRoot;
	BasClass* PtrToClass = 0;
	Class_1 Root(RootName, 1, "");

	cout << "Object tree";
	while (Path != "endtree") {
		cin >> RootName >> ClassNum >> State;
		MainRoot = Root.Ptr1(Path);
		switch (ClassNum) {
      case 2: PtrToClass = new Class_2(RootName, State, Path); break;
      case 3: PtrToClass = new Class_3(RootName, State, Path); break;
      case 4:	PtrToClass = new Class_4(RootName, State, Path); break;
      case 5: PtrToClass = new Class_5(RootName, State, Path); break;
      case 6: PtrToClass = new Class_6(RootName, State, Path); break;
		}
		MainRoot->Add(PtrToClass);
		cin >> Path;
	}
	Root.ShowTree();

	string KeySym; cin >> KeySym;
	while (KeySym != "//") {
		MainRoot = Root.KeySymSearch(KeySym);
		if (MainRoot != 0) cout << "\n" << KeySym << " Object name: " << MainRoot->getName();
		  else cout << "\n" << KeySym << " Object not found";
		cin >> KeySym;
	}
	return 0;
}
