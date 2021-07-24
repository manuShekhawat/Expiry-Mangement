class Item
{
	int dd, mm, yyyy;
	char name[50];
	string details;

  public:
 	Item(int i){}
	Item()
	{
		string detailWord;
		system("cls");
		cout << " Enter item name : ";
		fflush(stdin);
		cin.get(name, 50,'\n');
		int length = 100;
		string ok = "exit";
		details ="";
		cout << "Enter details(Max 100 words)\nHint : Type\"exit\" to confirm and save\n\n";
		int i = 0;
		do
		{
			if (i == length)
			{
				cout << "Max word limit reached!!\nSaving....";
				break;
			}
			cin >> detailWord;
			details+=detailWord+" ";
			i++;
		} while (detailWord != ok);

		cout << "Enter date of expiry (Please enter in format dd mm yyyy) \n";
		cin >> dd >> mm >> yyyy;
	}

	bool isExpired();
	void display_time_remaining();
	void display();
	void load(fstream& data);
	void store(fstream& data);
	friend bool isLess(Item i1, Item i2);
};

void Item::load(fstream& data)
{
	string n;
	getline(data, n);
	dd=stoi(n);
	
	getline(data, n);
	mm=stoi(n);
	
	getline(data, n);
	yyyy=stoi(n);
	
	getline(data, n);
	strcpy(name, n.c_str());
	
	getline(data, details);
}

void Item::store(fstream& data)
{
	
	data<<dd<<"\n"<<mm<<"\n"<<yyyy<<"\n";
	data<<name<<"\n";
	data<<details<<"\n";
}

void Item::display()
{
	cout << name << "\n";
	string det(details);
	det.erase(det.end()-5, det.end());
	cout<<det<<endl;
	cout << "Date of Expiry : " << dd << "/" << mm << "/" << yyyy << endl;
	display_time_remaining();
	cout<<endl;
	
}

bool Item::isExpired()
{
	time_t t = time(0);
	tm *now = localtime(&t);
	int cr_yyyy = now->tm_year + 1900;
	int cr_mm = now->tm_mon + 1;
	int cr_dd = now->tm_mday;
	if (cr_yyyy < yyyy)
	{
		return false;
	}
	else if (cr_yyyy > yyyy)
	{
		return true;
	}
	else
	{
		if (cr_mm < mm)
		{
			return false;
		}
		else if (cr_mm > mm)
		{
			return true;
		}
		else
		{
			if (cr_dd < dd)
			{
				return false;
			}
			else if (cr_dd > dd)
			{
				return true;
			}
			else
			{
				return true;
			}
		}
	}
}

void Item::display_time_remaining()
{
	int expiry_date = dd, expiry_month = mm, expiry_year = yyyy, current_date, current_month, current_year;
	time_t t = time(0);
	tm *now = localtime(&t);
	current_year = now->tm_year + 1900;
	current_month = now->tm_mon + 1;
	current_date = now->tm_mday;

	int month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (current_date > expiry_date)
	{
		expiry_date = expiry_date + month[current_month - 1];
		expiry_month = expiry_month - 1;
	}
	if (current_month > expiry_month)
	{
		expiry_year = expiry_year - 1;
		expiry_month = expiry_month + 12;
	}
	int calculated_date = expiry_date - current_date;
	int calculated_month = expiry_month - current_month;
	int calculated_year = expiry_year - current_year;
	if (!isExpired())
		cout << calculated_year << " years " << calculated_month << " months " << calculated_date << " days remaining\n";
	else
		cout <<"Already Expired\n ";
}

bool isLess(Item i1, Item i2)
{
	if (i1.yyyy < i2.yyyy)
	{
		return true;
	}
	else if (i1.yyyy > i2.yyyy)
	{
		return false;
	}
	else
	{
		if (i1.mm < i2.mm)
		{
			return true;
		}
		else if (i1.mm > i2.mm)
		{
			return false;
		}
		else
		{
			if (i1.dd < i2.dd)
			{
				return true;
			}
			else if (i1.dd > i2.dd)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}