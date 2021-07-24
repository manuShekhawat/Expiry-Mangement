/*Objective : 
1. The code allows user to store items with their expiry dates. It makes easy to store items and keep an eye on the items and their time before expiry remaining.
2. it allows MULTIPLE USER FUNCTIONALITY which makes it more systematic to manage.
3. it can be used at general stores also where getting data for each and every item gets very messy as the number of items are increased. 
4. A decent UI adds simplicity to the application.
*/

/*
Input/Output : 
First Page:
1. At the start of program , it asks the user to login with its username and password.
2. user can create a new acount also if she is new with the application.

Second Page : user can enter particular number to perform given sort of operations:
1.Add new item : Adds a new item to the user's account.
          input : 1.takes in item name.
                  2.item description (or any info related to item)
                  3.item's expiry date in dd/mm/yyyy format.
                  
2.Show expired items : Shows items which have crossed their expired date. 

3.Show all items : Shows all items which are present in user's account with their item ids, name, details, and time remaining to expire.
 
4.Remove an item : Every item is assigned id . user can enter an item's id to remove that particular item. user can check item id by pressing '3' or show items at second page.

5.Remove all expired items : Clears all items from the list which have passed their expiry date.

6.Logout and Save: saves all the changes user had made and stores them in a file.

*/

#include <ctime>
#include <vector>
#include <fstream>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<algorithm>
#include<string>
#include<cstring>

using namespace std;
bool loggedIn=false;
#include "item.cpp"
#include "user.cpp"
#include "Manager.cpp"

int main()
{
	Manager mg;
	mg.start();
	while(!loggedIn)
			mg.loginPage();
	while(loggedIn)
			mg.showMenu();
	cout<<"Thank You!!"<<endl;
	return 0;
}
