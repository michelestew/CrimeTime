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
#include"Crime.h"
#include"Tree.h"
#include<math.h>
#include<unordered_set>
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
void treeSort(vector<Crime> crimeData, string& text){ //sorting by age using tree sort through c++ ordered map || red black tree || O(nlogn)
	//map key is age value is crime obj
	avlTree tree; 
    for(int i = 0; i < crimeData.size(); i++){
        tree.insert(stoi(crimeData[i].Age));
    }
    auto start = chrono::system_clock::now();
    tree.printInorder();
    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "TREE SORT: finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    text += to_string(tree.sortAge[tree.sortAge.size() - 1]) + "\n";
    
	
}
void getStats(string& text, vector<Crime> crimeData, string area){
    map<string, vector<Crime>> region;
	map<string, vector<Crime>>::iterator itr;
    int male, female = 0;
	for(int i = 1; i < crimeData.size(); i++){
		region[crimeData[i].Area_Name].push_back(crimeData[i]);
	}
    text += ("Total number of crimes: " + to_string(region[area].size()) + "\n");
    text += "Oldest Criminal (Tree Sort): ";
    treeSort(region[area], text);
    text += "Month with most crime: ";
    map<int, vector<Crime>> month;
    map<int, vector<Crime>> time;
    map<int, vector<Crime>>::iterator it;
    map<int, vector<Crime>>::iterator itt;
    heap h(0);
    auto start = chrono::system_clock::now();
    for(int i = 1; i < region[area].size(); i++){
		month[stoi(region[area][i].Arrest_Date.substr(0, 2))].push_back(crimeData[i]);
        if(region[area][i].Sex_Code == "M")
            male++;
        if(region[area][i].Sex_Code == "F")
            female++;
        h.push(stoi(region[area][i].Age));
	}

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);
    cout << "HEAP SORT: finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    int m = 1;
    for(it = month.begin(); it != month.end(); it++){
        if(it->second.size() > month[m].size()){
            m = it->first;
        }
    }
    text += to_string(m) + "\n";
    text += "Oldest Criminal (Heap Sort): " + to_string(h.pop()) + "\n";
    text += "Total Female Charges: " + to_string(female) + "\n";
    text += "Total Male Charges: " + to_string(male) + "\n";



   
        
}


int main()
{
	vector<Crime> crimes; //data structure holding crime data 
    readData(crimes); //passed by refrence 

    map<string, vector<Crime>> regionData;
	map<string, vector<Crime>>::iterator itr;
	for(int i = 1; i < crimes.size(); i++){
		regionData[crimes[i].Area_Name].push_back(crimes[i]);
	}


    int w = 703;
    int h = 798;
    sf::RenderWindow window(sf::VideoMode(w + 150, h + 50), "Crime Time");

    sf::Sprite map(TextureManger::GetTexture("map"));
    sf::Sprite options(TextureManger::GetTexture("options"));
    sf::Sprite regionO(TextureManger::GetTexture("regionO"));
    sf::Sprite LAmap(TextureManger::GetTexture("LA_in_LA_County_map"));
    //shape.setFillColor(sf::Color::Green);
    sf::Font font;
    sf::Text title;
    sf::String playerInput;
    sf::Text playerText;
    if(!font.loadFromFile("Sanseriffic.otf")){
        cout << "problem" << endl;
    }
    title.setFont(font);
    title.setCharacterSize(25);
    playerText.setFont(font);
    playerText.setCharacterSize(38);
    LAmap.setColor(sf::Color::Transparent);
    playerInput = "Enter a region";
    playerText.setString(playerInput);


string s;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered){
                //cout << "Unicode: " << event.text.unicode <<endl;
                if(playerInput == "Enter a region"){
                    playerInput.clear();
                    playerText.setString(playerInput);
                }
                if(event.text.unicode == 13){
                    if((regionData.find(playerInput) != regionData.end())){
                        s = "------" + playerInput + "------\n";
                        getStats(s, crimes, playerInput);
                        map.setColor(sf::Color::Transparent);
                        LAmap.setColor(sf::Color::White);
                        title.setString(s);
                    }
                    if(playerInput == "return"){
                        LAmap.setColor(sf::Color::Transparent);
                        map.setColor(sf::Color::White);
                        title.setString("");
                        playerInput = "Enter a region";
                        playerText.setString(playerInput);
                    }
                    else{
                        playerInput.clear();
                        playerText.setString(playerInput);
                    }
                    
                    
                }
                else if(event.text.unicode == 8){
                    playerInput.erase(playerInput.getSize() - 1, 1);
                    playerText.setString(playerInput);
                }
                else{
                    playerInput +=event.text.unicode;
                    playerText.setString(playerInput);
                }
            }
        }


        window.clear();

        //Updating pos of each region button
        map.setPosition(0, 50);
        title.setPosition(0, 50);
        LAmap.setPosition(0, 374);
        options.setPosition(w, 50);
        regionO.setPosition(w, 0);


        //Drawing sprites 
        window.draw(map);
        window.draw(LAmap);
        window.draw(options);
        window.draw(title);
        window.draw(playerText);
        window.draw(regionO);


        window.display();

    }

return 0;

}
