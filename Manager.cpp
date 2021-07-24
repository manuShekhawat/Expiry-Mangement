class Manager
{
	User user;
	vector<User> users;
	fstream data;
	int noOfUsers=0;

  public:
  
	void start();
	void loginPage();
	bool isUser(string uname);
	bool login();
	void createAccount();
	void showMenu();
	void close();
};

void Manager::start()
{
	data.open("data.dat",ios::in | ios::out | ios::binary); 
	if(!data)
	{
		cout<<"File not found!!!!  \n"<<"Creating New file......"<<endl;
		data.open("data.dat", ios::out | ios::binary);
	}
	else
	{
		string n;
		data.seekg(0,ios::beg);
		getline(data, n);
		noOfUsers=stoi(n);
		
		string name,pass;
		Item it(0);
		User temp(0);
		for(int i=0;i<noOfUsers;i++)
		{
			
			temp=User(i);
			getline(data, name);
			getline(data, pass);
			temp.putUsername(name);
			temp.putPass(pass);
			getline(data, n);
			temp.noOfItems =stoi(n);
		
			for(int j=0;j<temp.noOfItems;j++)
			{
				it=Item(j);
				it.load(data);
				temp.items.push_back(it);
			}
			
			getline(data, n);
			temp.noOfExpiredItems=stoi(n);
			for(int j=0;j<temp.noOfExpiredItems;j++)
			{
				it=Item(j);
				it.load(data);
				temp.expiredItems.push_back(it);
			}
			users.push_back(temp);
		}
	}

	cout << "WELCOME TO EXPIRY MANAGEMENT SYSTEM\n\nPress any key to go to login page" << endl;
	getch();
	system("cls");
}


void Manager::close()
{
	int i;
	for ( i=0; i<users.size();i++)
		if(users[i].getUsername()==user.getUsername())
			break;
	
	users[i]=user;
	noOfUsers=users.size();
	data.seekp(0,ios::beg);
	data<<noOfUsers<<"\n";
	
	for(int i=0;i<noOfUsers;i++)
	{
		data<<users[i].getUsername()<<"\n"<<users[i].getPass()<<"\n";
		users[i].noOfItems=users[i].items.size();
		data<<users[i].noOfItems<<"\n";
		for(int j=0;j<users[i].noOfItems;j++)
		{
			users[i].items[j].store(data);
		}
			
		users[i].noOfExpiredItems=users[i].expiredItems.size();
		data<<users[i].noOfExpiredItems<<"\n";
		for(int j=0;j<users[i].noOfExpiredItems;j++)
		{
			users[i].expiredItems[j].store(data);
		}
	}
	data<<"\n";
	data.close();
	loggedIn=false;
}

void Manager::loginPage()
{
	cout << "Hello User!!"
			"\n1.Login"
			"\n2.New User? Create Account"
			"\n\nChoose from above option : ";
	int ch;
	cin >> ch;
	switch (ch)
	{
		case 1:
		{
			loggedIn=login();
			break;
		}
		case 2:
		{
			createAccount();
			loggedIn=true;
			break;
		}
	}
}

bool Manager::isUser(string uname)
{
	
	for (int i=0; i<users.size();i++)
		if(users[i].getUsername()==uname)
			return true;
		
	return false;
}

bool Manager::login()
{
	string uname;
	string pass;
	cout << "Enter Username : "; cin >> uname;
	fflush(stdin);
	if (isUser(uname))
	{
		int i=0;
		for ( i=0; i<users.size();i++)
			if(users[i].getUsername()==uname)
				break;
		user=users[i];
		PasswordEnter:
		cout << "Enter password : "; cin >> pass;
		
		if (user.verifyPassword(pass))
		{
			system("cls");
			return true;
		}
		else
		{
			system("cls");
			cout<<"Password didn't match!!! Please try again"<<endl;
			goto PasswordEnter;
		}
	}
	else
	{
		cout<<"No such username found!!!"<<endl;
		return false;
	}
	
}

void Manager::createAccount()
{
	string uname;
	string pass,confirmPass;
	cout<<"Enter Username : "; cin>>uname;
	ReEnter:
	cout<<"Enter Password : "; cin>>pass;
	cout<<"Confirm Password : "; cin>>confirmPass;
	if(pass.compare(confirmPass)!=0)
	{
		cout<<"Password didn't match!!!\nPlease re-enter password"<<endl;
		system("cls");
		goto ReEnter;
	}	
	user.putUsername(uname);
	user.putPass(pass);
	users.push_back(user);
	noOfUsers++;
	system("cls");
	cout<<"Account created successfully!!"<<endl<<endl;
}

void Manager::showMenu()
{
	system("cls");
	cout<<"Hello "<<user.getUsername()<<endl<<endl;
	cout<<"1.Add new item"
	      "\n2.Show expired items"
	      "\n3.Show all items"
	      "\n4.Remove an item"
	      "\n5.Remove all expired items"
	      "\n6.Logout and Save"<<endl<<endl;
	int ch;
	cout<<"What would you like to do : ";
	fflush(stdin);
	cin>>ch;
	
	switch (ch)
	{
		case 1 :
		{
			user.addItem();
			break;
		}
		case 2 :
		{
			user.showExpired();
			break;
		}
		case 3 :
		{
			user.showAll();
			break;
		}
		case 4 :
		{
			user.removeItem();
			break;
		}
		case 5 :
		{
			user.removeAllExpired();
			break;
		}
		case 6 :
		{
			close();
			break;
		 }
		 default :
		 cout<<"Invalid input!!! Please enter correct option";
	}
}

