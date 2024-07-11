#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class MyString
{
private:
	vector<char> data;//кдасс вектор є більш безпечним ніж масив, а також має за замовчувань стандартні алгоритми котрі знадобляться нам пізніше 
public:
	MyString(const char str[] = "\0")//конструктор за замовчуваням, у разі якщо текст не буде набраний, то вектор збереже один пустий символ
	{
		for(int i = 0, num = strlen(str); i < num; i++) 
			data.push_back(str[i]);
	};

	MyString(const MyString& temp)//конструктор копіюванняЮ котрий використовує перенавантажений оператор =
	{
		data = temp.data;
	};

	friend ostream& operator<<(ostream& output, MyString& str)//перевантажаний оператор консольного вивіду <<, що дає змогу виводити в консоль данні класу, як стандартні змінні
	{
		for (auto i : str.data)//особливості вектора
			output << i;
		return output;
	};

	friend fstream& operator<<(fstream& whrite, MyString& str)//перевантажаний оператор файлового вивіду <<, що дає змогу виводити у файл данні класу, як стандартні змінні
	{
		if (whrite.is_open())//перевірка на існування файлу
			for (auto i : str.data) whrite << i;
		else
			cout << "No file\n";//повідомлення у консоль якщо файл не існує
		return whrite;
	};

	friend fstream& operator>>(fstream& read, MyString& str)//перевантажаний оператор файлового вводу >>, що дає змогу данні у класс з файлуі, як стандартні змінні
	{
		if (read.is_open())//перевірка на існування файлу
		{
			str.data.clear();//очишення вектора від минулих данних

			for (char temp ;read.get(temp);)str.data.push_back(temp);
		}
		else
			cout << "No file\n";//повідомлення у консоль якщо файл не існує
		return read;
	};

	MyString operator=(const MyString str)//перевантаженний оператор =
	{
		this->data = str.data;
		return *this;
	};

	MyString operator+(const MyString str)//перевантаженний оператор +
	{
		MyString temp;

		temp.data = data;
		for (auto i : str.data) temp.data.push_back(i);
		return temp;
	};

	MyString operator+=(const MyString str)//перевантаженний оператор += котрий використовує "готові" оператори + та =
	{
		*this = *this + str;
		return *this;
	};

	friend bool operator==(const MyString str1, const MyString str2)//перевантажний булевий оператор ==
	{
		for (int i = 0, num = str1.data.size(); i < num; i++)
			if (str1.data[i] != str2.data[i])
				return false;
		return true;
	};

	friend bool operator!=(const MyString str1, const MyString str2)//перевантажений булевий оператор !=
	{
		for (int i = 0, num = str1.data.size(); i < num; i++)
			if (str1.data[i] != str2.data[i])
				return true;
		return false;
	};

	friend bool operator<(const MyString str1, const MyString str2){return (str1.data.size() < str2.data.size());}//перевантажений булевий оператор <

	friend bool operator>(const MyString str1, const MyString str2){return (str1.data.size() > str2.data.size());}//перевантажений булевий оператор <

	friend bool operator<=(const MyString str1, const MyString str2){return (str1.data.size() <= str2.data.size());}//перевантажений булевий оператор <=

	friend bool operator>=(const MyString str1, const MyString str2){return (str1.data.size() >= str2.data.size());}//перевантажений булевий оператор >=


	int size() { return data.size(); };//повернення довжини вектора

	int search(const char line[] = "\0")//пошук підрядка повертає позиці. першого символа
	{
		int i = 0, key = 0, num = strlen(line), size = data.size() - num;

		for (i = 0; i <= size; i++) 
		{
			for (int j = 0; j < num; j++)
			{	if (data[j + i] != line[j])
					break;
				else
					key++;
				if (key == num)
					return i;
			}
			key = 0;
		}
		return -1;
	};

	void change(const char line[], const char to[])//заміна підрядка іншим підрядком
	{
		int pos = search(line);
		if (pos != -1)//чи взагалі існує підрядок у тексті
		{
			data.erase(data.begin() + pos, data.begin() + pos + strlen(line));//видалення попередньго підрядка
			for (int i = 0, num = strlen(to); i < num; i++) data.insert(data.begin() + pos + i, to[i]);//посимвольне вставлення нового підрядка у текст
		}
	};

	void to_upper()	{for (auto i = data.begin(); i != data.end(); i++) *i = toupper(*i);};//посимвольне піднесення кожної літери до верхнього регістру 

	void to_lower() {for (auto i = data.begin(); i != data.end(); i++) *i = tolower(*i);};//посимвольне педнесення кожної літери до нижнього регістру
};


int main()
{
	fstream output;
	output.open("text.txt");

	MyString test0, test1("Helo"), test2("World!");

	cout << "Test 0: " << test0 << endl;
	cout << "Test 1: " << test1 << endl;
	cout << "Test 2: " << test2 << endl << endl;

	test0 = test1 + test2;

	cout << "Test 0: " << test0 << endl;
	cout << "Test 1: " << test1 << endl;
	cout << "Test 2: " << test2 << endl << endl;

	test0.change("Helo","Hello, ");

	cout << "Test 0: " << test0 << endl;
	cout << "Test 1: " << test1 << endl;
	cout << "Test 2: " << test2 << endl << endl;

	output << test0 << endl;
	
	test0.to_upper();
	output << test0 << endl;
	
	test0.to_lower();
	output << test0 << endl;

	output.close();

	return 0;
}