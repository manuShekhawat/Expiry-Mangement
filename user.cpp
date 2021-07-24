class User
{
	string username;
	string password;
	
	
	public:
	vector<Item> items;
	vector<Item> expiredItems;
	int noOfItems=0, noOfExpiredItems=0;
	User(int i){}
	User(){}
	string getUsername();
	string getPass();
	void putUsername(string u);
	void putPass(string p);
	void addItem();
	void showExpired();
	void showAll();
	void removeItem();
	void removeAllExpired();
	bool verifyPassword(string p);
	bool operator ==(User u1)
	{
		if((u1.password.compare(password)==0) && (u1.username.compare(username)==0))
		return true;
	}
};

string User::getUsername()
{
	return username;
}

string User::getPass()
{
	return password;
}

void User::putUsername(string u)
{
	username=u;
}

void User::putPass(string p)
{
	password=p;
}

void User::addItem()
{
	Item itm=Item();
	items.push_back(itm);
	cout<<"Item added successfully!!!!"<<endl;
	cout<<"Press any key to return to main menu :"<<endl;
	fflush(stdin);
	getch();
}

void User::showExpired()
{
	auto itr=items.begin();
	//update expired list and
	for(int i=0;i<items.size();i++)
	{
		if(items[i].isExpired())
		{
			expiredItems.push_back(items[i]);
			itr=items.begin()+i;
			items.erase(itr);
			i--;
		}
	}
	//show all expired items
	for(int i=0;i<expiredItems.size();i++)
	{
		//display each expired here
		cout<<i+1<<". ";
		expiredItems[i].display();		
	}
	cout<<"Press any key to return to main menu :"<<endl;
	fflush(stdin);
	getch();
}

void User::showAll()
{
	//show all items by sorting them by recently expiring first
	sort(items.begin(), items.end(), isLess);
		
	for(int i=0;i<items.size();i++)
	{
		//display each item here
		cout<<i+1<<". "; items[i].display();
	}
	cout<<"Press any key to return to main menu :"<<endl;
	fflush(stdin);
	getch();
}

void User::removeItem()
{
	int id;
	auto itr=items.begin();
	//remove by id
	cout<<"Enter Item id to remove : "; cin>>id;
	itr=items.begin()+id-1;
	items.erase(itr);
	cout<<"Item removed successfully!!!!"<<endl;
	cout<<"Press any key to return to main menu :"<<endl;
	getch();
}

void User::removeAllExpired()
{
	expiredItems.clear();
	cout<<"All expired items successfully removed!!!!"<<endl;
	cout<<"Press any key to return to main menu :"<<endl;
	getch();
}

bool User::verifyPassword(string p)
{
	if(password==p)
		return true;
	else
		return false;
}