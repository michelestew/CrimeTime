#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
#include<queue>
#include<SFML/Graphics.hpp>
#include"TextureManger.h"
#include"TextureManger.cpp"
#include"Heap.h"
#include "Crime.h"
using namespace std;


void readData(vector<Crime>& crimeData){//loads all 1322095 crimes into a vector of crime objects 
	vector<string> row;
	string line, word;
 
	fstream file ("Arrest_Data_from_2010_to_2019.csv", ios::in);
	if(file.is_open())
	{
		int z = 0;
		while(z < 100000) // [z < 100000] load z num crimes - needs getline(file, line); on line 53 || getline(file, line); loads all crimes
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
map<int, vector<Crime>> treeSort(vector<Crime> crimeData, string& text){ //sorting by age using tree sort through c++ ordered map || red black tree || O(nlogn)
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
    if(ageSort.begin()->first){
        text += (to_string(ageSort.begin()->first) + "-" + to_string(ageSort.rbegin()->first));
    }
    text += "\n";
    

	cout << "Percent: " << ((percent18andAbove / crimeData.size()) * 100) << endl; //random stat for fun
	
	return ageSort;

}

void getStats(string& text, vector<Crime> crimeData, string area){
    map<string, vector<Crime>> region;
	map<string, vector<Crime>>::iterator itr;
	for(int i = 1; i < crimeData.size(); i++){
		region[crimeData[i].Area_Name].push_back(crimeData[i]);
	}
    text += ("Total number of crimes: " + to_string(region[area].size()) + "\n");
    text += "Age range of criminals: ";
    treeSort(region[area], text);
    text += "Month with most crime: ";
    map<int, vector<Crime>> month;
    map<int, vector<Crime>>::iterator it;
    for(int i = 1; i < region[area].size(); i++){
		month[stoi(region[area][i].Arrest_Date.substr(0, 2))].push_back(crimeData[i]);
	}
    int m = 1;
    for(it = month.begin(); it != month.end(); it++){
        if(it->second.size() > month[m].size()){
            m = it->first;
        }
    }
    text += to_string(m) + "\n";


}

int main()
{
	vector<Crime> crimes; //data structure holding crime data 
    readData(crimes); //passed by refrence 

	//map<int, vector<Crime>> treeSortResult = treeSort(crimes); //result of treeSort 
    heap result(crimes); //result of heapSort
	for (int i = 0; i < result.h.size(); i++)
	{
		pair<string, int> top = result.pop();
		cout << result.h[i].first << ": " << result.h[i].second << endl;
	}

    int w = 658;
    int h = 798;
    sf::RenderWindow window(sf::VideoMode(w + 150, h), "Crime Time");

    sf::Sprite map(TextureManger::GetTexture("map"));
    sf::Sprite thsreet(TextureManger::GetTexture("77thstreet"));
    sf::Sprite central(TextureManger::GetTexture("central"));
    sf::Sprite devonshire(TextureManger::GetTexture("devonshire"));
    sf::Sprite foothill(TextureManger::GetTexture("foothill"));
    sf::Sprite harbor(TextureManger::GetTexture("harbor"));
    sf::Sprite hollenbeck(TextureManger::GetTexture("hollenbeck"));
    sf::Sprite hollywood(TextureManger::GetTexture("hollywood"));
    sf::Sprite mission(TextureManger::GetTexture("mission"));
    sf::Sprite newton(TextureManger::GetTexture("newton"));
    sf::Sprite northeast(TextureManger::GetTexture("northeast"));
    sf::Sprite northhollywood(TextureManger::GetTexture("northhollywood"));
    sf::Sprite olympic(TextureManger::GetTexture("olympic"));
    sf::Sprite pacific(TextureManger::GetTexture("pacific"));
    sf::Sprite rampart(TextureManger::GetTexture("rampart"));
    sf::Sprite southeast(TextureManger::GetTexture("southeast"));
    sf::Sprite southwest(TextureManger::GetTexture("southwest"));
    sf::Sprite topanga(TextureManger::GetTexture("topanga"));
    sf::Sprite vannuys(TextureManger::GetTexture("vannuys"));
    sf::Sprite westLA(TextureManger::GetTexture("westLA"));
    sf::Sprite westvalley(TextureManger::GetTexture("westvalley"));
    sf::Sprite wilshire(TextureManger::GetTexture("wilshire"));
    //shape.setFillColor(sf::Color::Green);
    sf::Font font;
    sf::Text title;
    sf::Text content;
    if(!font.loadFromFile("The Butter.otf")){
        cout << "problem" << endl;
    }
    title.setFont(font);
    title.setCharacterSize(20);
    content.setFont(font);
    content.setCharacterSize(20);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) { // checking for which region was clicked
                if (event.mouseButton.button == sf::Mouse::Left) {
                    string s;
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    auto bounds = thsreet.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------77th Street------ \n ";
                        getStats(s, crimes, "77th Street");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "77th Street" << endl;
                    }
                    bounds = central.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Central------ \n ";
                        getStats(s, crimes, "Central");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "Central" << endl;
                    }
                    bounds = devonshire.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Devonshire------ \n ";
                        getStats(s, crimes, "Devonshire");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "DevonShire" << endl;
                    }
                    bounds = foothill.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Foothill------ \n ";
                        getStats(s, crimes, "Foothill");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "FootHill" << endl;
                    }
                    bounds = harbor.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Harbor------ \n ";
                        getStats(s, crimes, "Harbor");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "Harbor" << endl;
                    }
                    bounds = hollenbeck.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Hollenbeck------ \n ";
                        getStats(s, crimes, "Hollenbeck");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "hollenbeck" << endl;
                    }
                    bounds = hollywood.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Hollywood------ \n ";
                        getStats(s, crimes, "Hollywood");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "hollywood" << endl;
                    }
                    
                    bounds = mission.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Mission------ \n ";
                        getStats(s, crimes, "Mission");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "mission" << endl;
                    }
                    bounds = newton.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Newton------ \n ";
                        getStats(s, crimes, "Newton");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "newton" << endl;
                    }
                    bounds = northeast.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Northeast------ \n ";
                        getStats(s, crimes, "Northeast");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "northeast" << endl;
                    }
                    bounds = northhollywood.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------North Hollwood------ \n ";
                        getStats(s, crimes, "N Hollywood");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "north hollywood" << endl;
                    }
                    bounds = olympic.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Olympic------ \n ";
                        getStats(s, crimes, "Olympic");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "olympic" << endl;
                    }
                    bounds = pacific.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Pacific------ \n ";
                        getStats(s, crimes, "Pacific");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "pacific" << endl;
                    }
                    bounds = rampart.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Rampart------ \n ";
                        getStats(s, crimes, "Rampart");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "rampart" << endl;
                    }
                    bounds = southeast.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Southeast------ \n ";
                        getStats(s, crimes, "Southeast");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "southeast" << endl;
                    }
                    bounds = southwest.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Southwest------ \n ";
                        getStats(s, crimes, "Southwest");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "southwest" << endl;
                    }
                    bounds = topanga.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Topanga------ \n ";
                        getStats(s, crimes, "Topanga");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "topanga" << endl;
                    }
                    bounds = vannuys.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Van Nuys------ \n ";
                        getStats(s, crimes, "Van Nuys");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "vannuys" << endl;
                    }
                    bounds = westLA.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------West LA------ \n ";
                        getStats(s, crimes, "West LA");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "westLA" << endl;
                    }
                    bounds = westvalley.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------West Valley------ \n ";
                        getStats(s, crimes, "West Valley");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "westvalley" << endl;
                    }
                    bounds = wilshire.getGlobalBounds();
                    if(bounds.contains(localPosition.x, localPosition.y)){
                        s = "------Wilshire------ \n ";
                        getStats(s, crimes, "Wilshire");
                        map.setColor(sf::Color::Transparent);
                        title.setString(s);
                        cout << "wilshire" << endl;
                    }

                }
            }
        }


        window.clear();

        //Updating pos of each region button

        thsreet.setPosition(w, 38 * 0);
        central.setPosition(w, 38 * 1);
        devonshire.setPosition(w, 38 * 2);
        foothill.setPosition(w, 38 * 3);
        harbor.setPosition(w, 38 * 4);
        hollenbeck.setPosition(w, 38 * 5);
        hollywood.setPosition(w, 38 * 6);
        mission.setPosition(w, 38 * 7);
        newton.setPosition(w, 38 * 8);
        northeast.setPosition(w, 38 * 9);
        northhollywood.setPosition(w, 38 * 10);
        olympic.setPosition(w, 38 * 11);
        pacific.setPosition(w, 38 * 12);
        rampart.setPosition(w, 38 * 13);
        southeast.setPosition(w, 38 * 14);
        southwest.setPosition(w, 38 * 15);
        topanga.setPosition(w, 38 * 16);
        vannuys.setPosition(w, 38 * 17);
        westLA.setPosition(w, 38 * 18);
        westvalley.setPosition(w, 38 * 19);
        wilshire.setPosition(w, 38 * 20);

        //Drawing sprites 
        window.draw(map);
        window.draw(thsreet);
        window.draw(central);
        window.draw(devonshire);
        window.draw(foothill);
        window.draw(harbor);
        window.draw(hollenbeck);
        window.draw(hollywood);
        window.draw(mission);
        window.draw(newton);
        window.draw(northeast);
        window.draw(northhollywood);
        window.draw(olympic);
        window.draw(pacific);
        window.draw(rampart);
        window.draw(southeast);
        window.draw(southwest);
        window.draw(topanga);
        window.draw(vannuys);
        window.draw(westLA);
        window.draw(westvalley);
        window.draw(wilshire);
        window.draw(title);
        window.draw(content);
       


        window.display();
    }

return 0;

}
