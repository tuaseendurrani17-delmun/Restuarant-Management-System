#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

// ==================== UTILITY ====================
int getInt()
{
    int val;
    while(true)
    {
        cin>>val;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid! Enter a number: ";
        }
        else
        {
            cin.ignore(1000,'\n');
            return val;
        }
    }
}

double getDouble()
{
    double val;
    while(true)
    {
        cin>>val;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Invalid! Enter a number: ";
        }
        else
        {
            cin.ignore(1000,'\n');
            return val;
        }
    }
}

string getString()
{
    string val;
    getline(cin,val);
    while(val.empty())
    {
        cout<<"Cannot be empty. Try again: ";
        getline(cin,val);
    }
    return val;
}

// ==================== PERSON (Base Class) ====================
class Person
{
protected:
    string name;
    string phone;
    string password;
public:
    Person()
    {
        name="";
        phone="";
        password="";
    }
    void setName(string n)     { name=n; }
    void setPhone(string p)    { phone=p; }
    void setPassword(string p) { password=p; }
    string getName()     { return name; }
    string getPhone()    { return phone; }
    string getPassword() { return password; }
};

// ==================== CUSTOMER (Inherits Person) ====================
class Customer : public Person
{
private:
    int id;
public:
    Customer()
    {
        id=0;
    }
    void setID(int i) { id=i; }
    int getID()       { return id; }

    void display()
    {
        cout<<"\nID    : "<<id;
        cout<<"\nName  : "<<name;
        cout<<"\nPhone : "<<phone;
    }
};

// ==================== STAFF (Inherits Person) ====================
class Staff : public Person
{
private:
    int id;
public:
    Staff()
    {
        id=0;
    }
    void setID(int i) { id=i; }
    int getID()       { return id; }

    void display()
    {
        cout<<"\nID    : "<<id;
        cout<<"\nName  : "<<name;
        cout<<"\nPhone : "<<phone;
    }
};

// ==================== MENUITEM (Base Class) ====================
class MenuItem
{
protected:
    int    id;
    string itemName;
    double price;
    string type; 
    string extra; 
public:
    MenuItem()
    {
        id=0;
        itemName="";
        price=0;
        type="";
        extra="";
    }
    void setID(int i)        { id=i; }
    void setName(string n)   { itemName=n; }
    void setPrice(double p)  { price=p; }
    void setType(string t)   { type=t; }
    void setExtra(string e)  { extra=e; }
    int    getID()     { return id; }
    string getName()   { return itemName; }
    double getPrice()  { return price; }
    string getType()   { return type; }
    string getExtra()  { return extra; }

    virtual void display()
    {
        cout<<"\n"<<id<<". "<<itemName<<"\t\tRs."<<price;
    }
    virtual ~MenuItem() {} 
};

// ==================== FOODITEM (Inherits MenuItem) ====================
class FoodItem : public MenuItem
{
public:
    FoodItem()
    {
        type="Food";
    }
    FoodItem(string n, double p, string cat)
    {
        itemName=n;
        price=p;
        type="Food";
        extra=cat;
    }
    void display() override
    {
        cout<<"\n"<<id<<". "<<itemName<<"\t\tRs."<<price<<"\t["<<extra<<"]";
    }
};

// ==================== DRINKITEM (Inherits MenuItem) ====================
class DrinkItem : public MenuItem
{
public:
    DrinkItem()
    {
        type="Drink";
    }
    DrinkItem(string n, double p)
    {
        itemName=n;
        price=p;
        type="Drink";
        extra="Drink";
    }
    void display() override
    {
        cout<<"\n"<<id<<". "<<itemName<<"\t\tRs."<<price<<"\t[Drink]";
    }
};

// ==================== CART ITEM STRUCT ====================
struct CartItem
{
    string itemName;
    double itemPrice;
    int    quantity;
};

// ==================== CART ====================
class Cart
{
private:
    CartItem* items;
    int size;
    int capacity;
public:
    Cart()
    {
        capacity=20;
        size=0;
        items=new CartItem[capacity];
    }
    ~Cart()
    {
        delete[] items;
    }

    void addItem(string name, double price, int qty)
    {
        for(int i=0;i<size;i++)
        {
            if(items[i].itemName==name)
            {
                items[i].quantity+=qty;
                return;
            }
        }
        if(size==capacity)
        {
            capacity*=2;
            CartItem* temp=new CartItem[capacity];
            for(int i=0;i<size;i++) temp[i]=items[i];
            delete[] items;
            items=temp;
        }
        items[size].itemName=name;
        items[size].itemPrice=price;
        items[size].quantity=qty;
        size++;
    }

    void removeItem(int index)
    {
        if(index<0||index>=size)
        {
            cout<<"\nInvalid index!";
            return;
        }
        for(int i=index;i<size-1;i++)
            items[i]=items[i+1];
        size--;
    }

    void clear()
    {
        size=0;
    }

    double getSubtotal()
    {
        double total=0;
        for(int i=0;i<size;i++)
            total+=items[i].itemPrice*items[i].quantity;
        return total;
    }

    int getSize() { return size; }
    CartItem getItem(int i) { return items[i]; }
    bool isEmpty() { return size==0; }

    void display()
    {
        if(isEmpty())
        {
            cout<<"\nCart is empty.";
            return;
        }
        cout<<"\n============== CART ==============";
        for(int i=0;i<size;i++)
        {
            cout<<"\n"<<items[i].itemName
                <<"\t\tx"<<items[i].quantity
                <<"\tRs."<<items[i].itemPrice*items[i].quantity;
        }
        cout<<"\n\nSubtotal: Rs."<<getSubtotal();
    }
};

// ==================== ORDER ====================
class Order
{
private:
    int    orderID;
    string customerName;
    string customerPhone;
    double totalAmount;
    string paymentMethod;
    string status;
    string itemLines[50];
    int    itemCount;
public:
    Order()
    {
        orderID=0;
        customerName="";
        customerPhone="";
        totalAmount=0;
        paymentMethod="";
        status="Pending";
        itemCount=0;
    }

    void setOrderID(int i)         { orderID=i; }
    void setCustomerName(string n) { customerName=n; }
    void setCustomerPhone(string p){ customerPhone=p; }
    void setTotalAmount(double a)  { totalAmount=a; }
    void setPaymentMethod(string m){ paymentMethod=m; }
    void setStatus(string s)       { status=s; }
    void addItemLine(string line)
    {
        if(itemCount<50)
            itemLines[itemCount++]=line;
    }

	int    getOrderID()        { return orderID; }
	string getCustomerName()   { return customerName; }
	string getCustomerPhone()  { return customerPhone; }
	double getTotalAmount()    { return totalAmount; }
	string getPaymentMethod()  { return paymentMethod; }
	string getStatus()         { return status; }
	int    getItemCount()      { return itemCount; }
	string getItemLine(int i)  { return itemLines[i]; }

	void displayShort()
	{
		cout<<"\nOrder ID : "<<orderID;
		cout<<"\nCustomer : "<<customerName;
		cout<<"\nAmount   : Rs."<<totalAmount;
		cout<<"\nStatus   : "<<status;
	}

	void displayFull()
	{
		cout<<"\nOrder ID : "<<orderID;
		cout<<"\nCustomer : "<<customerName;
		cout<<"\nPhone    : "<<customerPhone;
		cout<<"\nItems    : ";
		for(int i=0;i<itemCount;i++)
			cout<<itemLines[i]<<" ";
		cout<<"\nTotal    : Rs."<<totalAmount;
		cout<<"\nPayment  : "<<paymentMethod;
		cout<<"\nStatus   : "<<status;
	}
};

// ==================== GLOBAL DATA ====================
MenuItem** menu     = NULL;
int menuSize        = 0;
int menuCapacity    = 0;

Customer** customers = NULL;
int custSize         = 0;
int custCapacity     = 0;

Order** orders      = NULL;
int orderSize       = 0;
int orderCapacity   = 0;

int nextOrderID     = 101;
int nextCustomerID  = 1;
int nextStaffID     = 1;
int nextMenuID      = 1;

Cart currentCart;

void initArrays()
{
	menuCapacity=50;
	menu=new MenuItem*[menuCapacity];

	custCapacity=50;
	customers=new Customer*[custCapacity];

	orderCapacity=100;
	orders=new Order*[orderCapacity];
}

// ==================== FILE: MENU ====================
void saveMenu()
{
	ofstream f("menu.txt");
	for(int i=0;i<menuSize;i++)
	{
		f<<menu[i]->getID()<<"|"
		 <<menu[i]->getType()<<"|"
		 <<menu[i]->getName()<<"|"
		 <<menu[i]->getPrice()<<"|"
		 <<menu[i]->getExtra()<<"\n";
	}
	f.close();
}

void loadMenu()
{
	ifstream f("menu.txt");
	if(!f) return;
	string line;
	while(getline(f,line))
	{
		if(line.empty()) continue;
		string p[5]; int pi=0; string tok="";
		for(int i=0; i<(int)line.size(); i++)
		{
			if(line[i]=='|'){ p[pi++]=tok; tok=""; }
			else tok+=line[i];
		}
		p[pi]=tok;

		int  id    = atoi(p[0].c_str());
		string type  = p[1];
		string name  = p[2];
		double price = atof(p[3].c_str());
		string extra = p[4];

		MenuItem* m;
		if(type=="Food")
		{
			FoodItem* fi=new FoodItem(name,price,extra);
			fi->setID(id);
			m=fi;
		}
		else
		{
			DrinkItem* di=new DrinkItem(name,price);
			di->setID(id);
			m=di;
		}

		if(menuSize==menuCapacity)
		{
			menuCapacity*=2;
			MenuItem** tmp=new MenuItem*[menuCapacity];
			for(int i=0;i<menuSize;i++) tmp[i]=menu[i];
			delete[] menu;
			menu=tmp;
		}
		menu[menuSize++]=m;
		if(id>=nextMenuID) nextMenuID=id+1;
	}
	f.close();
}

// ==================== FILE: CUSTOMERS ====================
void saveCustomers()
{
	ofstream f("customers.txt");
	for(int i=0;i<custSize;i++)
	{
		f<<customers[i]->getID()<<"|"
		 <<customers[i]->getName()<<"|"
		 <<customers[i]->getPhone()<<"|"
		 <<customers[i]->getPassword()<<"\n";
	}
	f.close();
}

void loadCustomers()
{
	ifstream f("customers.txt");
	if(!f) return;
	string line;
	while(getline(f,line))
	{
		if(line.empty()) continue;
		string p[4]; int pi=0; string tok="";
		for(int i=0; i<(int)line.size(); i++)
		{
			if(line[i]=='|'){ p[pi++]=tok; tok=""; }
			else tok+=line[i];
		}
		p[pi]=tok;

		Customer* c=new Customer();
		c->setID(atoi(p[0].c_str()));
		c->setName(p[1]);
		c->setPhone(p[2]);
		c->setPassword(p[3]);

		if(custSize==custCapacity)
		{
			custCapacity*=2;
			Customer** tmp=new Customer*[custCapacity];
			for(int i=0;i<custSize;i++) tmp[i]=customers[i];
			delete[] customers;
			customers=tmp;
		}
		customers[custSize++]=c;
		if(c->getID()>=nextCustomerID) nextCustomerID=c->getID()+1;
	}
	f.close();
}

// ==================== FILE: ORDERS ====================
void saveOrders()
{
	ofstream f("orders.txt");
	for(int i=0;i<orderSize;i++)
	{
		Order* o=orders[i];
		f<<o->getOrderID()<<"|"
		 <<o->getCustomerName()<<"|"
		 <<o->getCustomerPhone()<<"|"
		 <<o->getTotalAmount()<<"|"
		 <<o->getPaymentMethod()<<"|"
		 <<o->getStatus()<<"|"
		 <<o->getItemCount();
		for(int j=0;j<o->getItemCount();j++)
			f<<"~"<<o->getItemLine(j);
		f<<"\n";
	}
	f.close();
}

void loadOrders()
{
	ifstream f("orders.txt");
	if(!f) return;
	string line;
	while(getline(f,line))
	{
		if(line.empty()) continue;
		string p[8]; int pi=0; string tok="";
		for(int i=0; i<(int)line.size(); i++)
		{
			if(line[i]=='|'){ p[pi++]=tok; tok=""; }
			else tok+=line[i];
		}
		p[pi]=tok;

		Order* o=new Order();
		o->setOrderID(atoi(p[0].c_str()));
		o->setCustomerName(p[1]);
		o->setCustomerPhone(p[2]);
		o->setTotalAmount(atof(p[3].c_str()));
		o->setPaymentMethod(p[4]);
		o->setStatus(p[5]);
		int icount=atoi(p[6].c_str());

		string itemStr=p[7];
		string itok="";
		int loaded=0;
		for(int i=0; i<(int)itemStr.size(); i++)
		{
			if(itemStr[i]=='~')
			{
				if(!itok.empty()){ o->addItemLine(itok); itok=""; loaded++; }
			}
			else itok+=itemStr[i];
		}
		if(!itok.empty() && loaded<icount) o->addItemLine(itok);

		if(orderSize==orderCapacity)
		{
			orderCapacity*=2;
			Order** tmp=new Order*[orderCapacity];
			for(int i=0;i<orderSize;i++) tmp[i]=orders[i];
			delete[] orders;
			orders=tmp;
		}
		orders[orderSize++]=o;
		if(o->getOrderID()>=nextOrderID) nextOrderID=o->getOrderID()+1;
	}
	f.close();
}

// ==================== FILE: STAFF ====================
void saveAllStaffToFile()
{
    // Re-saves empty file or changes whenever elements are deleted manually
}

void saveStaff(Staff& s)
{
	ofstream f("staff.txt",ios::app);
	f<<s.getID()<<"|"<<s.getName()<<"|"<<s.getPhone()<<"|"<<s.getPassword()<<"\n";
	f.close();
}

// ==================== DISPLAY MENU ====================
void showMenu()
{
	if(menuSize==0){ cout<<"\nMenu is empty!"; return; }
	cout<<"\n============== MENU ==============";
	bool foodDone=false, drinkDone=false;
	for(int i=0;i<menuSize;i++)
	{
		if(menu[i]->getType()=="Food" && !foodDone)
		{
			cout<<"\nFood Items";
			foodDone=true;
		}
		if(menu[i]->getType()=="Drink" && !drinkDone)
		{
			cout<<"\n\nDrinks";
			drinkDone=true;
		}
		menu[i]->display();
	}
	cout<<"\n\n0. Back";
}

// ==================== CUSTOMER PORTAL REGISTER / LOGIN ====================
void registerCustomer()
{
	cout<<"\n==============================";
	cout<<"\nREGISTER (Type 0 to Cancel)";
	cout<<"\n==============================";
	cout<<"\nEnter Name: ";
	string name=getString();
	if(name == "0") {
	    cout << "\nRegistration Cancelled.";
	    return;
	}
	
	cout<<"Enter Phone: ";
	string phone=getString();

	for(int i=0;i<custSize;i++)
	{
		if(customers[i]->getPhone()==phone)
		{
			cout<<"\nPhone already registered!";
			return;
		}
	}

	cout<<"Enter Password: ";
	string pass=getString();

	Customer* c=new Customer();
	c->setID(nextCustomerID++);
	c->setName(name);
	c->setPhone(phone);
	c->setPassword(pass);

	if(custSize==custCapacity)
	{
		custCapacity*=2;
		Customer** tmp=new Customer*[custCapacity];
		for(int i=0;i<custSize;i++) tmp[i]=customers[i];
		delete[] customers;
		customers=tmp;
	}
	customers[custSize++]=c;
	saveCustomers();
	cout<<"\nAccount Created Successfully!";
}

int loginCustomer()
{
	cout<<"\n==============================";
	cout<<"\nLOGIN";
	cout<<"\n==============================";
	cout<<"\nEnter Phone: ";
	string phone=getString();
	cout<<"Enter Password: ";
	string pass=getString();

	for(int i=0;i<custSize;i++)
	{
		if(customers[i]->getPhone()==phone && customers[i]->getPassword()==pass)
		{
			cout<<"\nLogin Successful! Welcome "<<customers[i]->getName();
			return i;
		}
	}
	cout<<"\nInvalid Phone or Password!";
	return -1;
}

void addToCart()
{
	showMenu();
	if(menuSize==0) return;
	cout<<"\n\nEnter Item Number: ";
	int num=getInt();
	if(num<1||num>menuSize){ cout<<"\nInvalid item!"; return; }
	cout<<"Enter Quantity: ";
	int qty=getInt();
	if(qty<=0){ cout<<"\nQuantity must be positive!"; return; }
	currentCart.addItem(menu[num-1]->getName(), menu[num-1]->getPrice(), qty);
	cout<<"\n"<<menu[num-1]->getName()<<" Added To Cart!";
}

void viewCart()
{
	currentCart.display();
	if(currentCart.isEmpty()) return;
	cout<<"\n\n1. Remove Item\n2. Clear Cart\n3. Back";
	cout<<"\nEnter Choice: ";
	int o=getInt();
	if(o==1)
	{
		cout<<"Enter item number to remove (1-"<<currentCart.getSize()<<"): ";
		int idx=getInt();
		currentCart.removeItem(idx-1);
		cout<<"\nItem Removed!";
	}
	else if(o==2)
	{
		currentCart.clear();
		cout<<"\nCart Cleared!";
	}
}

void checkout(int custIdx)
{
	if(currentCart.isEmpty()){ cout<<"\nCart is empty!"; return; }

	cout<<"\n============== CHECKOUT ==============";
	double subtotal=currentCart.getSubtotal();
	cout<<"\nSubtotal: Rs."<<subtotal;

	cout<<"\n\nApply Discount? (Y/N): ";
	string dc=getString();
	double discount=0;
	if(dc=="Y"||dc=="y")
	{
		cout<<"Enter Discount %: ";
		discount=getDouble();
		if(discount<0||discount>100){ cout<<"\nInvalid discount!"; discount=0; }
	}

	double finalAmt=subtotal-(subtotal*discount/100);
	cout<<"\nDiscount   : "<<discount<<"%";
	cout<<"\nFinal Amt  : Rs."<<finalAmt;

	cout<<"\n\nSelect Payment Method";
	cout<<"\n1. Cash On Delivery\n2. Card";
	cout<<"\nChoice: ";
	int pm=getInt();
	string method="Cash On Delivery";
	if(pm==2) method="Card";

	Order* o=new Order();
	o->setOrderID(nextOrderID++);
	o->setCustomerName(customers[custIdx]->getName());
	o->setCustomerPhone(customers[custIdx]->getPhone());
	o->setTotalAmount(finalAmt);
	o->setPaymentMethod(method);
	o->setStatus("Pending");

	for(int i=0;i<currentCart.getSize();i++)
	{
		CartItem ci=currentCart.getItem(i);
		char buffer[50];
		sprintf(buffer, " x%d", ci.quantity);
		string line = ci.itemName + buffer;
		o->addItemLine(line);
	}

	if(orderSize==orderCapacity)
	{
		orderCapacity*=2;
		Order** tmp=new Order*[orderCapacity];
		for(int i=0;i<orderSize;i++) tmp[i]=orders[i];
		delete[] orders;
		orders=tmp;
	}
	orders[orderSize++]=o;
	currentCart.clear();
	saveOrders();

	cout<<"\n\nOrder Placed Successfully!";
	cout<<"\nOrder ID : "<<o->getOrderID();
	cout<<"\nStatus   : "<<o->getStatus();
	cout<<"\nOrder saved in file.";
}

void viewOrderHistory(int custIdx)
{
	cout<<"\n============== HISTORY ==============";
	bool found=false;
	for(int i=0;i<orderSize;i++)
	{
		if(orders[i]->getCustomerPhone()==customers[custIdx]->getPhone())
		{
			cout<<"\n";
			orders[i]->displayShort();
			cout<<"\n";
			found=true;
		}
	}
	if(!found) cout<<"\nNo orders found.";
	cout<<"\nLoaded from file.";
}

void trackOrder(int custIdx)
{
	bool found=false;
	for(int i=0;i<orderSize;i++)
	{
		if(orders[i]->getCustomerPhone()==customers[custIdx]->getPhone())
		{
			cout<<"\nOrder ID      : "<<orders[i]->getOrderID();
			cout<<"\nCurrent Status: "<<orders[i]->getStatus();
			found=true;
		}
	}
	if(!found) cout<<"\nNo active orders found.";
}

// ==================== DELETION UTILITIES ====================
void deleteCustomer()
{
    if(custSize == 0) { cout << "\nNo customers registered to delete."; return; }
    cout << "\n============== REGISTERED CUSTOMERS ==============";
    for(int i=0; i<custSize; i++) {
        cout << "\n" << (i+1) << ". ID: " << customers[i]->getID() << " | Name: " << customers[i]->getName() << " | Phone: " << customers[i]->getPhone();
    }
    cout << "\n\nEnter Customer Index to Delete (1-" << custSize << ") or 0 to Cancel: ";
    int choice = getInt();
    if(choice < 1 || choice > custSize) { cout << "\nOperation Cancelled/Invalid Index."; return; }
    
    int idx = choice - 1;
    cout << "\nAre you sure you want to delete Customer: " << customers[idx]->getName() << "? (Y/N): ";
    string confirm = getString();
    if(confirm == "Y" || confirm == "y") {
        delete customers[idx];
        for(int i = idx; i < custSize - 1; i++) {
            customers[i] = customers[i+1];
        }
        custSize--;
        saveCustomers();
        cout << "\nCustomer deleted successfully and sync'd to file.";
    } else {
        cout << "\nDeletion cancelled.";
    }
}

void deleteStaff()
{
    ifstream f("staff.txt");
    if(!f) { cout << "\nNo staff entries exist to delete."; return; }
    
    // Read and display options
    string lines[100];
    int linesCount = 0;
    string line;
    cout << "\n============== REGISTERED STAFF ==============";
    while(getline(f, line)) {
        if(line.empty()) continue;
        lines[linesCount++] = line;
        
        // Parse basic viewable details safely
        string p[4]; int pi=0; string tok="";
        for(int i=0; i<(int)line.size(); i++) {
            if(line[i]=='|'){ p[pi++]=tok; tok=""; }
            else tok+=line[i];
        }
        p[pi]=tok;
        cout << "\n" << linesCount << ". ID: " << p[0] << " | Name: " << p[1] << " | Phone: " << p[2];
    }
    f.close();

    if(linesCount == 0) { cout << "\nNo staff profiles found inside records."; return; }

    cout << "\n\nEnter Staff Record Index to Delete (1-" << linesCount << ") or 0 to Cancel: ";
    int choice = getInt();
    if(choice < 1 || choice > linesCount) { cout << "\nOperation Cancelled."; return; }

    cout << "\nConfirm permanent deletion? (Y/N): ";
    string confirm = getString();
    if(confirm == "Y" || confirm == "y") {
        ofstream out("staff.txt");
        for(int i=0; i<linesCount; i++) {
            if(i == (choice - 1)) continue; // skip the deleted line
            out << lines[i] << "\n";
        }
        out.close();
        cout << "\nStaff member profile updated and removed.";
    } else {
        cout << "\nDeletion cancelled.";
    }
}

// ==================== CUSTOMER DASHBOARD ====================
void customerDashboard(int custIdx)
{
	string choice;
	do
	{
		int o;
		cout<<"\n\n==============================";
		cout<<"\nCUSTOMER DASHBOARD";
		cout<<"\n==============================";
		cout<<"\n1. View Menu";
		cout<<"\n2. Add Item To Cart";
		cout<<"\n3. View Cart";
		cout<<"\n4. Checkout";
		cout<<"\n5. View Order History";
		cout<<"\n6. Track Current Order";
		cout<<"\n7. Logout";
		cout<<"\nEnter Choice: ";
		o=getInt();

		if(o==1)       showMenu();
		else if(o==2)  addToCart();
		else if(o==3)  viewCart();
		else if(o==4)  checkout(custIdx);
		else if(o==5)  viewOrderHistory(custIdx);
		else if(o==6)  trackOrder(custIdx);
		else if(o==7)
		{
			currentCart.clear();
			cout<<"\nLogged Out!";
			return;
		}
		else
		{
			cout<<"\nInvalid option! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) return;
		}
	}while(true);
}

// ==================== CUSTOMER PORTAL ====================
void CustomerPortal()
{
	string choice;
	do
	{
		int o;
		cout<<"\n==============================";
		cout<<"\nCUSTOMER PORTAL";
		cout<<"\n==============================";
		cout<<"\n1. Register\n2. Login\n3. Back";
		cout<<"\nEnter Choice: ";
		o=getInt();

		if(o==1)       registerCustomer();
		else if(o==2)
		{
			int idx=loginCustomer();
			if(idx>=0) customerDashboard(idx);
		}
		else if(o==3) return;
		else
		{
			cout<<"\nInvalid option! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) return;
		}
	}while(true);
}

// ==================== STAFF FUNCTIONS ====================
void registerStaff()
{
	cout<<"\n==============================";
	cout<<"\nSTAFF REGISTER (Type 0 to Cancel)";
	cout<<"\n==============================";
	cout<<"\nEnter Name: ";
	string name=getString();
	if(name == "0") {
	    cout << "\nRegistration Cancelled.";
	    return;
	}
	
	cout<<"Enter Phone: ";
	string phone=getString();

	ifstream sf("staff.txt");
	if(sf)
	{
		string line;
		while(getline(sf,line))
		{
			if(line.empty()) continue;
			string p[4]; int pi=0; string tok="";
			for(int i=0; i<(int)line.size(); i++)
			{
				if(line[i]=='|'){ p[pi++]=tok; tok=""; }
				else tok+=line[i];
			}
			p[pi]=tok;
			if(p[2]==phone)
			{
				cout<<"\nPhone already registered!";
				sf.close();
				return;
			}
		}
		sf.close();
	}

	cout<<"Enter Password: ";
	string pass=getString();

	Staff s;
	s.setID(nextStaffID++);
	s.setName(name);
	s.setPhone(phone);
	s.setPassword(pass);
	saveStaff(s);
	cout<<"\nStaff Account Created! ID: "<<s.getID();
}

bool loginStaff()
{
	cout<<"\n==============================";
	cout<<"\nSTAFF LOGIN";
	cout<<"\n==============================";
	cout<<"\nEnter Phone: ";
	string phone=getString();
	cout<<"Enter Password: ";
	string pass=getString();

	ifstream f("staff.txt");
	if(!f){ cout<<"\nNo staff registered yet!"; return false; }
	string line;
	while(getline(f,line))
	{
		if(line.empty()) continue;
		string p[4]; int pi=0; string tok="";
		for(int i=0; i<(int)line.size(); i++)
		{
			if(line[i]=='|'){ p[pi++]=tok; tok=""; }
			else tok+=line[i];
		}
		p[pi]=tok;
		if(p[2]==phone && p[3]==pass)
		{
			cout<<"\nLogin Successful! Welcome "<<p[1];
			f.close();
			return true;
		}
	}
	f.close();
	cout<<"\nInvalid Credentials!";
	return false;
}

void createMenuItem()
{
	cout<<"\n==============================";
	cout<<"\nCREATE MENU ITEM";
	cout<<"\n==============================";
	cout<<"\n1. Food Item\n2. Drink Item";
	cout<<"\nEnter Choice: ";
	int o=getInt();

	if(o==1)
	{
		cout<<"\nEnter Name: ";
		string name=getString();
		cout<<"Enter Price: ";
		double price=getDouble();
		if(price<=0){ cout<<"\nPrice must be positive!"; return; }
		cout<<"Enter Category: ";
		string cat=getString();

		FoodItem* fi=new FoodItem(name,price,cat);
		fi->setID(nextMenuID++);

		if(menuSize==menuCapacity)
		{
			menuCapacity*=2;
			MenuItem** tmp=new MenuItem*[menuCapacity];
			for(int i=0;i<menuSize;i++) tmp[i]=menu[i];
			delete[] menu;
			menu=tmp;
		}
		menu[menuSize++]=fi;
		saveMenu();
		cout<<"\nFood Item Added Successfully!";
		cout<<"\nSaved in menu file.";
	}
	else if(o==2)
	{
		cout<<"\nEnter Name: ";
		string name=getString();
		cout<<"Enter Price: ";
		double price=getDouble();
		if(price<=0){ cout<<"\nPrice must be positive!"; return; }

		DrinkItem* di=new DrinkItem(name,price);
		di->setID(nextMenuID++);

		if(menuSize==menuCapacity)
		{
			menuCapacity*=2;
			MenuItem** tmp=new MenuItem*[menuCapacity];
			for(int i=0;i<menuSize;i++) tmp[i]=menu[i];
			delete[] menu;
			menu=tmp;
		}
		menu[menuSize++]=di;
		saveMenu();
		cout<<"\nDrink Item Added Successfully!";
		cout<<"\nSaved in menu file.";
	}
	else cout<<"\nInvalid choice!";
}

void updateMenuItem()
{
	if(menuSize==0){ cout<<"\nMenu is empty!"; return; }
	showMenu();
	cout<<"\n\nEnter Item Number to Update: ";
	int idx=getInt();
	if(idx<1||idx>menuSize){ cout<<"\nInvalid!"; return; }
	idx--;
	cout<<"Enter New Name (current: "<<menu[idx]->getName()<<"): ";
	string name=getString();
	cout<<"Enter New Price (current: "<<menu[idx]->getPrice()<<"): ";
	double price=getDouble();
	menu[idx]->setName(name);
	menu[idx]->setPrice(price);
	saveMenu();
	cout<<"\nUpdated Successfully!";
}

void deleteMenuItem()
{
	if(menuSize==0){ cout<<"\nMenu is empty!"; return; }
	showMenu();
	cout<<"\n\nEnter Item Number to Delete: ";
	int idx=getInt();
	if(idx<1||idx>menuSize){ cout<<"\nInvalid!"; return; }
	idx--;
	cout<<"\nDeleted: "<<menu[idx]->getName();
	delete menu[idx];
	for(int i=idx;i<menuSize-1;i++) menu[i]=menu[i+1];
	menuSize--;
	saveMenu();
	cout<<"\nDeleted Successfully!";
}

void viewAllOrders()
{
	if(orderSize==0){ cout<<"\nNo Orders Found."; return; }
	cout<<"\n============== ORDERS ==============";
	for(int i=0;i<orderSize;i++)
	{
		cout<<"\n";
		orders[i]->displayShort();
		cout<<"\n";
	}
}

void updateOrderStatus()
{
	cout<<"\nEnter Order ID: ";
	int id=getInt();
	for(int i=0;i<orderSize;i++)
	{
		if(orders[i]->getOrderID()==id)
		{
			cout<<"\n1. Pending\n2. Preparing\n3. Ready\n4. Out For Delivery\n5. Delivered";
			cout<<"\nChoice: ";
			int c=getInt();
			string statusList[]={"Pending","Preparing","Ready","Out For Delivery","Delivered"};
			if(c<1||c>5){ cout<<"\nInvalid!"; return; }
			orders[i]->setStatus(statusList[c-1]);
			saveOrders();
			cout<<"\nOrder Status Updated!";
			return;
		}
	}
	cout<<"\nOrder Not Found!";
}

void searchOrder()
{
	cout<<"\nEnter Order ID: ";
	int id=getInt();
	for(int i=0;i<orderSize;i++)
	{
		if(orders[i]->getOrderID()==id)
		{
			orders[i]->displayFull();
			return;
		}
	}
	cout<<"\nOrder Not Found!";
}

void generateReports()
{
	string choice;
	do
	{
		int o;
		cout<<"\n============== REPORTS ==============";
		cout<<"\n1. Summary Report\n2. Transaction Report\n3. Search Report\n4. Back";
		cout<<"\nEnter Choice: ";
		o=getInt();

		if(o==1)
		{
			double revenue=0;
			int delivered=0;
			for(int i=0;i<orderSize;i++)
			{
				revenue+=orders[i]->getTotalAmount();
				if(orders[i]->getStatus()=="Delivered") delivered++;
			}
			cout<<"\nTotal Customers : "<<custSize;
			cout<<"\nTotal Orders    : "<<orderSize;
			cout<<"\nDelivered       : "<<delivered;
			cout<<"\nRevenue         : Rs."<<revenue;

			ofstream rf("summary_report.txt");
			rf<<"===== SUMMARY REPORT =====\n";
			rf<<"Total Customers : "<<custSize<<"\n";
			rf<<"Total Orders    : "<<orderSize<<"\n";
			rf<<"Delivered       : "<<delivered<<"\n";
			rf<<"Revenue         : Rs."<<revenue<<"\n";
			rf.close();
			cout<<"\nSaved to summary_report.txt";
		}
		else if(o==2)
		{
			cout<<"\nOrderID\t\tAmount\t\tStatus";
			cout<<"\n--------------------------------------";
			for(int i=0;i<orderSize;i++)
			{
				cout<<"\n"<<orders[i]->getOrderID()
					<<"\t\t"<<orders[i]->getTotalAmount()
					<<"\t\t"<<orders[i]->getStatus();
			}
			ofstream rf("transaction_report.txt");
			rf<<"===== TRANSACTION REPORT =====\n";
			rf<<"OrderID\tAmount\tStatus\n";
			for(int i=0;i<orderSize;i++)
				rf<<orders[i]->getOrderID()<<"\t"<<orders[i]->getTotalAmount()<<"\t"<<orders[i]->getStatus()<<"\n";
			rf.close();
			cout<<"\nSaved to transaction_report.txt";
		}
		else if(o==3)
		{
			cout<<"\nEnter Customer Name: ";
			string name=getString();
			bool found=false;
			for(int i=0;i<orderSize;i++)
			{
				if(orders[i]->getCustomerName()==name)
				{
					cout<<"\n";
					orders[i]->displayShort();
					found=true;
				}
			}
			if(!found) cout<<"\nNo orders found for "<<name;
		}
		else if(o==4) return;
		else
		{
			cout<<"\nInvalid! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) return;
		}
	}while(true);
}

// ==================== STAFF DASHBOARD ====================
void staffDashboard()
{
	string choice;
	do
	{
		int o;
		cout<<"\n\n==============================";
		cout<<"\nSTAFF DASHBOARD";
		cout<<"\n==============================";
		cout<<"\n1. Create Menu Item";
		cout<<"\n2. View Menu";
		cout<<"\n3. Update Menu Item";
		cout<<"\n4. Delete Menu Item";
		cout<<"\n5. View Orders";
		cout<<"\n6. Update Order Status";
		cout<<"\n7. Search Order";
		cout<<"\n8. Generate Reports";
		cout<<"\n9. Delete Customer Account";
		cout<<"\n10. Delete Staff Account";
		cout<<"\n11. Logout";
		cout<<"\nEnter Choice: ";
		o=getInt();

		if(o==1)      createMenuItem();
		else if(o==2) showMenu();
		else if(o==3) updateMenuItem();
		else if(o==4) deleteMenuItem();
		else if(o==5) viewAllOrders();
		else if(o==6) updateOrderStatus();
		else if(o==7) searchOrder();
		else if(o==8) generateReports();
		else if(o==9) deleteCustomer();
		else if(o==10) deleteStaff();
		else if(o==11)
		{
			cout<<"\nLogged Out!";
			return;
		}
		else
		{
			cout<<"\nInvalid! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) return;
		}
	}while(true);
}

// ==================== STAFF PORTAL ====================
void StaffPortal()
{
	string choice;
	do
	{
		int o;
		cout<<"\n==============================";
		cout<<"\nSTAFF PORTAL";
		cout<<"\n==============================";
		cout<<"\n1. Register\n2. Login\n3. Back";
		cout<<"\nEnter Choice: ";
		o=getInt();

		if(o==1)      registerStaff();
		else if(o==2)
		{
			if(loginStaff()) staffDashboard();
		}
		else if(o==3) return;
		else
		{
			cout<<"\nInvalid! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) return;
		}
	}while(true);
}

// ==================== CLEANUP ====================
void cleanup()
{
	for(int i=0;i<menuSize;i++)     delete menu[i];
	delete[] menu;
	for(int i=0;i<custSize;i++)     delete customers[i];
	delete[] customers;
	for(int i=0;i<orderSize;i++)    delete orders[i];
	delete[] orders;
}

// ==================== MAIN ====================
int main()
{
	initArrays();
	loadMenu();
	loadCustomers();
	loadOrders();

	string choice;
	int c;
	do
	{
		cout<<"\n================================";
		cout<<"\nONLINE FOOD ORDERING SYSTEM";
		cout<<"\n================================";
		cout<<"\n1. Customer Portal";
		cout<<"\n2. Restaurant Staff Portal";
		cout<<"\n3. Exit";
		cout<<"\nEnter Choice: ";
		c=getInt();

		if(c==1)      CustomerPortal();
		else if(c==2) StaffPortal();
		else if(c==3)
		{
			cout<<"\nExiting... Goodbye!";
			break;
		}
		else
		{
			cout<<"\nInvalid! Want to Retry? (Y/N): ";
			choice=getString();
			if(!(choice=="Y"||choice=="y")) break;
		}
	}while(true);

	cleanup();
	return 0;
}
