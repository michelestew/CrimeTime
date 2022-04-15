#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

//Object to store different data about a crime -- sorry for the crazy long constructor
struct Crime {
	string Report_ID;
	string Report_Type;
	string Arrest_Date;
	string Time;
	string Area_ID;
	string Area_Name;
	string Reporting_District;
	string Age;
	string Sex_Code;
	string Descent_Code;
	string Charge_Group_Code;
	string Charge_Group_Description;
	string Arrest_Type_Code;
	string Charge;
	string Charge_Description;
	string Disposition_Description;
	string Address;
	string Cross_Street;
	string LAT;
	string LON;
	string Location;
	string Booking_Date;
	string Booking_Time;
	string Booking_Location;
	string Booking_Location_Code;

	Crime(string a, string b, string c,string d,string e,string f,string g,string h,string i,string j,string k, string l,string m,string n,string o,string p,string q,string r,string s,string t,string u,string v,string w,string x) : Report_ID(a), Report_Type(b), Arrest_Date(c),Time(d),Area_ID(e),Area_Name(f),Reporting_District(g),Age(h), Sex_Code(i),Descent_Code(j), Charge_Group_Code(j), Charge_Group_Description(k), Arrest_Type_Code(l), Charge(m), Charge_Description(n),Disposition_Description(o),Address(p),Cross_Street(q),LAT(r),LON(s),Location(t),Booking_Date(u), Booking_Time(v), Booking_Location(w), Booking_Location_Code(x) {}

};


void readData(vector<Crime>& crimeData){//loads all 1322095 crimes into a vector of crime objects 
	vector<string> row;
	string line, word;
 
	fstream file ("Arrest_Data_from_2010_to_2019.csv", ios::in);
	if(file.is_open())
	{
		int z = 0;
		while(z < 1000) // [z < 100000] load z num crimes - needs getline(file, line); on line 53 || getline(file, line); loads all crimes
		{
			getline(file, line);
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			Crime crime(row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13],row[14],row[15],row[16],row[17],row[18],row[19],row[20],row[21],row[22],row[23]);
			crimeData.push_back(crime);
			z++;
		}
	}
	else
		cout<<"Could not open the file\n";
 

}
map<int, vector<Crime>> treeSort(vector<Crime> crimeData){ //sorting by age using tree sort through c++ ordered map || red black tree || O(nlogn)
	//map key is age value is crime obj
	map<int, vector<Crime>> ageSort;
	map<int, vector<Crime>>::iterator itr;
	for(int i = 1; i < crimeData.size(); i++){
		int n = stoi(crimeData[i].Age);
		ageSort[n].push_back(crimeData[i]);
	}
	float percent18andAbove = 0.0;
	for(itr = ageSort.begin(); itr != ageSort.end(); itr++){
		if(itr->first >= 18){
			percent18andAbove += itr->second.size();
		}
		cout << itr->first << endl;
	}

	cout << "Percent: " << ((percent18andAbove / crimeData.size()) * 100) << endl; //random stat for fun
	
	return ageSort;

}



int main()
{
	vector<Crime> crimes; //data structure holding crime data 
    readData(crimes); //passed by refrence 

	map<int, vector<Crime>> treeSortResult = treeSort(crimes); //result of treeSort 

return 0;

}
