#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class MyString
{
private:
	vector<char> data;//����� ������ � ���� ��������� �� �����, � ����� �� �� ����������� ��������� ��������� ���� ������������ ��� ����� 
public:
	MyString(const char str[] = "\0")//����������� �� ������������, � ��� ���� ����� �� ���� ��������, �� ������ ������� ���� ������ ������
	{
		for(int i = 0, num = strlen(str); i < num; i++) 
			data.push_back(str[i]);
	};

	MyString(const MyString& temp)//����������� ���������� ������ ����������� ���������������� �������� =
	{
		data = temp.data;
	};

	friend ostream& operator<<(ostream& output, MyString& str)//�������������� �������� ����������� ����� <<, �� �� ����� �������� � ������� ���� �����, �� ��������� ����
	{
		for (auto i : str.data)//���������� �������
			output << i;
		return output;
	};

	friend fstream& operator<<(fstream& whrite, MyString& str)//�������������� �������� ��������� ����� <<, �� �� ����� �������� � ���� ���� �����, �� ��������� ����
	{
		if (whrite.is_open())//�������� �� ��������� �����
			for (auto i : str.data) whrite << i;
		else
			cout << "No file\n";//����������� � ������� ���� ���� �� ����
		return whrite;
	};

	friend fstream& operator>>(fstream& read, MyString& str)//�������������� �������� ��������� ����� >>, �� �� ����� ���� � ����� � �����, �� ��������� ����
	{
		if (read.is_open())//�������� �� ��������� �����
		{
			str.data.clear();//�������� ������� �� ������� ������

			for (char temp ;read.get(temp);)str.data.push_back(temp);
		}
		else
			cout << "No file\n";//����������� � ������� ���� ���� �� ����
		return read;
	};

	MyString operator=(const MyString str)//��������������� �������� =
	{
		this->data = str.data;
		return *this;
	};

	MyString operator+(const MyString str)//��������������� �������� +
	{
		MyString temp;

		temp.data = data;
		for (auto i : str.data) temp.data.push_back(i);
		return temp;
	};

	MyString operator+=(const MyString str)//��������������� �������� += ������ ����������� "�����" ��������� + �� =
	{
		*this = *this + str;
		return *this;
	};

	friend bool operator==(const MyString str1, const MyString str2)//������������� ������� �������� ==
	{
		for (int i = 0, num = str1.data.size(); i < num; i++)
			if (str1.data[i] != str2.data[i])
				return false;
		return true;
	};

	friend bool operator!=(const MyString str1, const MyString str2)//�������������� ������� �������� !=
	{
		for (int i = 0, num = str1.data.size(); i < num; i++)
			if (str1.data[i] != str2.data[i])
				return true;
		return false;
	};

	friend bool operator<(const MyString str1, const MyString str2){return (str1.data.size() < str2.data.size());}//�������������� ������� �������� <

	friend bool operator>(const MyString str1, const MyString str2){return (str1.data.size() > str2.data.size());}//�������������� ������� �������� <

	friend bool operator<=(const MyString str1, const MyString str2){return (str1.data.size() <= str2.data.size());}//�������������� ������� �������� <=

	friend bool operator>=(const MyString str1, const MyString str2){return (str1.data.size() >= str2.data.size());}//�������������� ������� �������� >=


	int size() { return data.size(); };//���������� ������� �������

	int search(const char line[] = "\0")//����� ������� ������� ������. ������� �������
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

	void change(const char line[], const char to[])//����� ������� ����� ��������
	{
		int pos = search(line);
		if (pos != -1)//�� ������ ���� ������� � �����
		{
			data.erase(data.begin() + pos, data.begin() + pos + strlen(line));//��������� ����������� �������
			for (int i = 0, num = strlen(to); i < num; i++) data.insert(data.begin() + pos + i, to[i]);//����������� ���������� ������ ������� � �����
		}
	};

	void to_upper()	{for (auto i = data.begin(); i != data.end(); i++) *i = toupper(*i);};//����������� ��������� ����� ����� �� ��������� ������� 

	void to_lower() {for (auto i = data.begin(); i != data.end(); i++) *i = tolower(*i);};//����������� ���������� ����� ����� �� �������� �������
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