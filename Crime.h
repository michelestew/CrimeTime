#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

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

	Crime(string a, string b, string c, string d, string e, string f, string g, string h, string i, string j, string k, string l, string m, string n, string o, string p, string q, string r, string s, string t, string u, string v, string w, string x) : Report_ID(a), Report_Type(b), Arrest_Date(c), Time(d), Area_ID(e), Area_Name(f), Reporting_District(g), Age(h), Sex_Code(i), Descent_Code(j), Charge_Group_Code(j), Charge_Group_Description(k), Arrest_Type_Code(l), Charge(m), Charge_Description(n), Disposition_Description(o), Address(p), Cross_Street(q), LAT(r), LON(s), Location(t), Booking_Date(u), Booking_Time(v), Booking_Location(w), Booking_Location_Code(x) {}

};