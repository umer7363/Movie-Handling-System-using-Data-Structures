#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include<sstream>
#include <string>
#include <queue>
#include<conio.h>

using namespace std;
bool check2(string str, string sub)
{
	int y = 0, x;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == sub[0])
		{
			y = 1;
			x = i + 1;
			while (y < sub.length() && str[x] == sub[y])
			{
				y++;
				x++;
			}
			if (y == sub.length())
			{
				return true;
			}
		}
	}
	if (y == sub.length())
	{
		return true;
	}
	return false;
}
class movie
{
public:
	string name, genre;
	float rating;
	int year;

	movie()
	{
		name = "";
		genre = "";
		rating = 0;
		year = 0;
	}
	movie(string n, string g, float r, int y)
	{
		name = n;
		rating = r;
		year = y;
		genre = g;
	}
	void operator=(movie *rhs)
	{
		this->name = rhs->name;
		this->genre = rhs->genre;
		this->rating = rhs->rating;
		this->year = rhs->year;
	}
};
class Node
{
public:
	movie *data;
	Node *left, *right;
	Node()
	{
		data = 0;
		left = right = NULL;
	}
	Node(string n, string g, float r, int y)
	{
		data = new movie(n, g, r, y);
		left = NULL;
		right = NULL;
	}
};
class BST
{
public:
	Node *root;
	BST()
	{
		root = NULL;
	}
	void insert(string n, string g, float r, int y)
	{
		if (root == NULL)
		{
			root = new Node(n, g, r, y);
			return;
		}
		else
		{
			Node *temp = root;
			Node *prev = NULL;
			while (temp != NULL)
			{
				prev = temp;
				if (n < temp->data->name)
				{
					temp = temp->left;
				}
				else
				{
					temp = temp->right;
				}
			}
			if (prev != NULL)
			{

				if (n < prev->data->name)
				{
					prev->left = new Node(n, g, r, y);
				}
				else
				{
					prev->right = new Node(n, g, r, y);
				}
			}
		}
	}
	void inOrder(const Node *n)
	{
		if (n != NULL)
		{
			Node *temp = root, *n = NULL;
			queue<Node *> q;
			q.push(temp);
			while (!q.empty())
			{
				temp = q.front();
				if (temp->left != NULL)
				{
					q.push(temp->left);
				}
				if (temp->right != NULL)
				{
					q.push(temp->right);
				}
				q.pop();
				n = temp;
				cout << "Name:" << n->data->name << endl
					 << "Year:" << n->data->year << "\n"
					 << "Rating:" << n->data->rating << "\n"
					 << "Genre:" << n->data->genre << "\n\n";
			}
		}
	}
	movie *search(string n)
	{
		if (root != NULL)
		{
			Node *temp = root;
			while (temp != NULL)
			{
				if (check2(temp->data->name, n))
				{
					return (temp->data);
				}
				if (temp->data->name > n)
				{
					temp = temp->left;
				}
				else
				{
					temp = temp->right;
				}
			}
		}
		return NULL;
	}
};
bool check(string l, string r)
{
	size_t found = l.find(r);
	if (found != string ::npos)
		return true;
	else
		return false;
}
class Data
{
public:
	BST *tree;
	Data()
	{
		tree = new BST();
	}
	void insert(string n, string g, float r, int y)
	{
		tree->insert(n, g, r, y);
	}
	void display()
	{
		if (tree != NULL)
		{
			tree->inOrder(tree->root);
		}
	}
	movie *search_name(string n)
	{
		return tree->search(n);
	}
};
class Rating
{
public:
	Data *data;
	Rating()
	{
		data = new Data[5]();
	}
	void insert(string n, string g, float r, int y)
	{
		if (r < 5)
		{
			int a;
			a = r;
			data[a].insert(n, g, r, y);
		}
	}
	void search_year()
	{
		if (data != NULL)
		{
			for (int i = 0; i < 5; i++)
			{
				data[i].display();
			}
		}
	}
	void search_rating(int r)
	{
		if (data != NULL)
		{
			if (r < 5)
			{
				data[r].display();
			}
		}
	}
	void search_genre()
	{
		if (data != NULL)
		{
			for (int i = 0; i < 5; i++)
			{
				data[i].display();
			}
		}
	}
	void search_name(string n)
	{
		if (data)
		{
			movie *temp = NULL;
			for (int i = 0; i < 5; i++)
			{
				temp = data[i].search_name(n);
				if (temp != NULL)
				{
					cout << "Name:" << temp->name << endl
						 << "Year:" << temp->year << "\n"
						 << "Rating:" << temp->rating << "\n"
						 << "Genre:" << temp->genre << "\n";
					cout << endl;
				}
			}
		}
	}
};
class Genre
{
public:
	Rating *rate;
	string *genre;
	int size;

	Genre()
	{
		size = 16;
		rate = new Rating[size]();
		genre = new string[16];
		genre[0] = "action";
		genre[1] = "animation";
		genre[2] = "comedy";
		genre[3] = "crime";
		genre[4] = "drama";
		genre[5] = "adventure";
		genre[6] = "thriller";
		genre[7] = "war";
		genre[8] = "sci-fi";
		genre[9] = "romance";
		genre[10] = "musical";
		genre[11] = "westren";
		genre[12] = "fantasy";
		genre[13] = "mystery";
		genre[14] = "horror";
		genre[15] = "childern";
	}
	void insert(string n, string g, float r, int y)
	{
		for (int i = 0; i < size; i++)
		{
			if (check2(g, genre[i]))
			{
				rate[i].insert(n, g, r, y);
			}
		}
	}
	void search_year()
	{
		if (rate != NULL && genre != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				rate[i].search_year();
				return;
			}
		}
	}
	void search_rating(int r)
	{
		if (rate && genre)
		{
			for (int i = 0; i < size; i++)
			{
				rate[i].search_rating(r);
				return;
			}
		}
	}
	void search_genre(string g)
	{
		if (rate && genre)
		{
			for (int i = 0; i < size; i++)
			{
				if (g == genre[i])
				{
					rate[i].search_genre();
					return;
				}
			}
		}
	}
	void search_name(string n)
	{
		if (rate && genre)
		{
			for (int i = 0; i < size; i++)
			{
				rate[i].search_name(n);
				return;
			}
		}
	}
};
class Year
{
public:
	Genre *gen;
	int size;

	Year()
	{
		size = 0;
		gen = NULL;
	}
	Year(int s)
	{
		size = s;
		gen = new Genre[s]();
	}
	void insert(string n, string g, float r, int y)
	{
		if (y > 2000)
		{
			gen[2].insert(n, g, r, y);
			return;
		}
		else if (y > 1990)
		{
			gen[1].insert(n, g, r, y);
			return;
		}
		else
		{
			gen[0].insert(n, g, r, y);
			return;
		}
	}
	void search_year(int y)
	{
		if (gen != NULL)
		{
			if (y > 2000)
			{
				return gen[2].search_year();
			}
			else if (y > 1990)
			{
				return gen[1].search_year();
			}
			else
			{
				return gen[0].search_year();
			}
		}
	}
	void search_rating(int r)
	{
		if (gen != NULL)
		{
			for (int i = 0; i < 3; i++)
			{
				gen[i].search_rating(r);
				return;
			}
		}
	}
	void search_genre(string g)
	{
		if (gen != NULL)
		{
			for (int i = 0; i < 3; i++)
			{
				gen[i].search_genre(g);
				return;
			}
		}
	}
	void search_name(string n)
	{
		if (gen != NULL)
		{
			for (int i = 0; i < 3; i++)
			{
				gen[i].search_name(n);
				return;
			}
		}
	}
};

void filling(Year &y)
{
	string line;
	ifstream obj("movies.txt");
	string stri, name, genre, rating, extra, year, str;
	double rat;
	long int year1;
	if (!obj)
	{
		cout << "\nerror";
	}
	for (int j = 0; j < 1000; j++)
	{
		int count = 0;
		// cout<<j<<" ";
		getline(obj, line, '\n');

		int i = line.length();

		for (i--; i >= 0; i--)
		{
			if (line[i] == '~')
				break;

			else
				genre += line[i];
		}

		reverse(genre.begin(), genre.end());

		for (i--; i >= 0; i--)
		{
			if (line[i] == '~')
				break;

			else
				extra += line[i];
		}

		for (i--; i >= 0; i--)
		{
			if (line[i] == '~')
				break;

			else
				rating += line[i];
		}
		reverse(rating.begin(), rating.end());
		stringstream obj3(rating);
		obj3>>rat;
		for (i = i - 2; i >= 0; i--)
		{
			if (line[i] == '(')
			{
				count = 1;
				break;
			}

			else
				year += line[i];
		}
		if (count == 0)
		{
			name = year;
			year = "2000";
			stringstream obj2(year);
			obj2 >> year1;
//			year1 = stoi(year);
			y.insert(name, genre, rat, year1);
			name = rating = year = genre = "";
			str = stri = "";
			continue;
		}
		reverse(year.begin(), year.end());
		stringstream obj(year);
		obj>>year1;
//		year1 = stoi(year)
		for (i = i - 2; i >= 0; i--)
		{
			name += line[i];
		}
		reverse(name.begin(), name.end());

		// cout<<rat<<endl;
		y.insert(name, genre, rat, year1);
		name = rating = year = genre = "";
		str = stri = "";
	}
}
int main()
{
	string *interest;
	int num;
	system("cls");
	cout << "LOADING.....";
	system("cls");
	Year y(3);
	filling(y);
	cout << "\n\n1.Action, 2.Animation, 3.Comedy, 4.Crime, 5.Drama, 6.Adventure, 7.Thriller, 8.War, 9.Sci-Fi,\n10.Romance, 11.Musical, 12.Western, 13.Fantasy, 14.Mystery, 15.Horror ";
	cout << "\n\nEnter Total Number Of intrested genres: ";
	cin >> num;
	num=num+1;
	cout << "\n\nEnter genres: ";
	interest = new string[num];
	for (int i = 0; i < num; i++)
	{
		getline(cin, interest[i]);
	}
	system("cls");

	int choice = 0, opt = 0;
	
	for(;;)
	{	
		system("cls");
		cout << "\n\n1.View movies of a time period.\n"
			 << "2.Search Genre.\n"
			 << "3.View Rating of a Movie.\n"
			 << "4.Recommendations.\n"
			 << "5.Search Movie With Name\n"
			 << "6.Enter 0 to EXIT.\n\n"
			 << "OPTION: ";
		cin >> choice;
		
		if (choice == 1)
		{
			int i;
			cout << "1.Movies Before 1990.\n"
				 << "2.Movies Between 1990-2000\n"
				 << "3.Movies Between 2000-2010\n"
				 << "CHOICE: ";
				 
			cin >> opt;
			if (opt == 1)
			{
				y.search_year(1990);
			}
			else if (opt == 2)
			{
				y.search_year(2000);
			}
			else if (opt == 3)
			{
				y.search_year(2010);
			}
			else
			{
				cout << "\nInvalid choice!!\n";
			}
			cout<<"\n\nPress any key to continue.";
			getch();
		}

		else if (choice == 2)
		{
			cout << "1.Action, 2.Animation, 3.Comedy, 4.Crime, 5.Drama, 6.Adventure, 7.Thriller, 8.War, 9.Sci-Fi,\n10.Romance, 11.Musical, 12.Western, 13.Fantasy, 14.Mystery, 15.Horror ";
			cout<< "\nEnter movie genre: ";
			int genres;
			cin.ignore();
			cin >> genres;
			string g;
			if(genres>15);
			cout<<"\n\nInvalid entry.\n";
			if (genres == 1)
			{
				g = "action";
			}
			if (genres == 2)
			{
				g = "animation";
			}
			if (genres == 3)
			{
				g = "comedy";
			}
			if (genres == 4)
			{
				g = "crime";
			}
			if (genres == 5)
			{
				g = "drama";
			}
			if (genres == 6)
			{
				g = "adventure";
			}
			if (genres == 7)
			{
				g = "thriller";
			}
			if (genres == 8)
			{
				g = "war";
			}
			if (genres == 9)
			{
				g = "sci-fi";
			}
			if (genres == 10)
			{
				g = "romance";
			}
			if (genres == 11)
			{
				g = "musical";
			}
			if (genres == 12)
			{
				g = "western";
			}
			if (genres == 13)
			{
				g = "fantasy";
			}
			if (genres == 14)
			{
				g = "mystery";
			}
			if (genres == 15)
			{
				g = "horror";
			}
			y.search_genre(g);
			cout<<"\n\nPress any key to continue.";
			getch();
		}
		else if (choice == 3)
		{
			cout << "Enter desired rating: ";
			int r;
			cin.ignore();
			cin >> r;
			y.search_rating(r);
			cout<<"\n\nPress any key to continue.";
			getch();
		}
		else if(choice == 4)
		{
			for(int i=0;i<num;i++)
			{
				y.search_genre(interest[i]);
			}
			cout<<"\n\nPress any key to continue.";
			getch();
		}
		else if (choice == 5)
		{
			cout<<"Enter movie name: ";
			string namm;
			cin.ignore();
			getline(cin,namm);
			y.search_name(namm);
			cout<<"\n\nPress any key to continue.";
			getch();
		}
		else if(choice ==0)
			break;
	}
}

