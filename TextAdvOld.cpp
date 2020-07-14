#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

void EncounterAttacker(int &h, int &mh, int &a, int &wa, int &c, int &e);
void BeginBattle(int &h, int &mh, int &a, int &wa, int &c, int &e, int aa, int ah, string attacker);
void EncounterTrader(int &h, int &mh, int&th, int &a, int &wa, int &c, string &weapon, string &helmS, int &helm, string &chestS, int &chest, string &pantsS, int &pants, string &shoesS, int &shoes);
void EncounterWeaponSmith(int &wa, string &weapon, int &c);
void Weapon(int choice, int &wa, string &weapon, int &c);
int RunChance(char s);
int EnterTown(char symbol, int dangerLevel);
string TownDangerLevel(int dangerLevel);
bool equalString(string str, string str2);
int EnterScenario(int &h, int &mh, int &a, int &wa, int &c, int x);
int FindItem(int item);
void EquipItem(int &h, int &mh, int &th, int &a, int &wa, int &c, string &weapon, string &helmS, int &helm, string &chestS, int &chest, string &pantsS, int &pants, string &shoesS, int &shoes, int item);
void Chat(int h, int dangerlvl, string weapon, int wa);
bool YesNo();
int CheckID(int item, int function);
int DetermineTraderPrice(int itemAttribute);
void AddItemToInventory(int invSpace, string name, int value, int id);

int main() {

	//settings
	int numberOfTowns = 50;
	int numberOfCamps = 70;
	int numberOfCaves = 30;
	int numberOfLandmarks = 0;

	cout << "=====DIRECTIONS=====" << endl << "You are in an open world filled with lots of chances. Anything can happen." << endl
		<< endl << "Question marks (?) are places you can visit." << endl << "  -Once you entered them, they will turn into their symbol." << endl << "  -You can entered " <<
		"any location infinite times." << endl << endl << "Towns are marked as (T):" << endl << "  -Towns are places where people gather. You can" <<
		" encountered anything in at these towns. " << endl <<"  -Towns also have danger levels. These levels indicate the likely-hood you will be attacked" <<
		" upon entering the town." << endl << endl << "Upgrades to your character and weapons to help in battle can be found all around the wasteland. " << endl <<  
		"You can upgrade your base max health, as well as find armor to improve your health points. Only one of each type " << endl << "of armor can be equipped " << 
		"at a time." << endl <<"IMPORTANT: Equipping a weapon or armor will lose your current respective weapon or armor. " << endl;

	cout << endl << "To begin playing," << endl;
	system("pause");
	cout << endl;

	struct player {
		int xcord = 49;
		int ycord = 49;
		int health = 10; //current health
		int maxHealth = 10; //maximum health w/o armor
		int totalHealth = 10; //maximum health + armor points
		int attack = 1;
		int wAttack = 0;
		string weapon = "None";
		//armor
		string helmS = "None";
		int helm = 0;
		string chestS = "None";
		int chest = 0;
		string pantsS = "None";
		int pants = 0;
		string shoesS = "None";
		int shoes = 0;
		//--
		int exp = 0;
		int level = 0;
		int money = 1000;
		char symbol = 'A';
		string name = "Aaron";
		int numOfInvItems = 0;
		struct inventory {
			string itemName;
			int itemId;
			int itemValue;
		}inventory[20];
	}aaron;

	srand(time(NULL));
	
	//map struct
	struct themap {
		char symbol = '+';
		string name = "Default";
		string description = "Default";
		bool chance = false;
		bool discovered = true;
		int dangerLevel = 0;
	}map[100][100];

	//other places
	struct theroad {
		char symbol = '@';
		string name = "Road";
		string description = "Safe to walk along";
		bool chance = false;
		bool discovered = true;
	}road;

	struct thetown {
		char symbol = 'T';
		string name = "Town";
		string description = "a place where people tend to gather";
		bool chance = true;
		bool discovered = false;
		int dangerLevel = 0;
	}town;

	bool gameOver = false;
	string input = "";
	

	//establish roads
	for (int i = 0; i < 100; i++) {
		map[49][i].symbol = road.symbol;
		map[49][i].name = road.name;
		map[49][i].description = road.description;
		map[49][i].chance = road.chance;
	}

	for (int i = 0; i < 100; i++) {
		map[i][49].symbol = road.symbol;
		map[i][49].name = road.name;
		map[i][49].description = road.description;
		map[i][49].chance = road.chance;
	}


	//randomize areas

	map[51][51].symbol = town.symbol;
	map[51][51].name = town.name;
	map[51][51].description = town.description;
	map[51][51].chance = town.chance;
	map[51][51].discovered = town.discovered;

	//generate towns
	for (int i = 0; i < numberOfTowns; i++) {
		int x, y;
		x = (int) rand() % 100;
		y = (int) rand() % 100;

		//dont generate on it if it is a road!
		if (map[x][y].symbol == '@') {
			i--;
			continue;
		}

		//cout << x << ", " << y << endl;
		map[x][y].symbol = town.symbol;
		map[x][y].name = town.name;
		map[x][y].description = town.description;
		map[x][y].chance = town.chance;
		map[x][y].discovered = town.discovered;
		map[x][y].dangerLevel = rand() % 6;
	}

	//generate camps
	for (int i = 0; i < numberOfCamps; i++) {

	}

	//generate caves
	for (int i = 0; i < numberOfCaves; i++) {

	}


	//begin game
	while (!gameOver) {

		bool goodInput = false;
		aaron.totalHealth = aaron.maxHealth + aaron.helm + aaron.chest + aaron.pants + aaron.shoes;



			//tell current player info
		cout << endl << endl << "  CURRENT  |  Health: " << aaron.health << "/" << aaron.totalHealth << "     Level: " << aaron.level << "     Exp: " << aaron.exp << "    Coins: " << aaron.money <<  endl <<
								"           |  Weapon Equipped: " << aaron.weapon << "    Helmet: " << aaron.helmS << "    Chest: " << aaron.chestS << "    Pants: " << aaron.pantsS << "    Shoes: " << aaron.shoesS << endl;

			//check for player on place
			if (map[aaron.xcord][aaron.ycord].symbol != '+') {
				if (map[aaron.xcord][aaron.ycord].symbol == '@') {
					cout << "  STATUS   |  You are on a road! Road's are safe to walk along." << endl;
				}
				else {
					cout << "  STATUS   |  (!) You are by a " << map[aaron.xcord][aaron.ycord].name << ", " << map[aaron.xcord][aaron.ycord].description << ". Type \"enter\" to enter!" << endl;
				}
			}
			else {
				cout << "  STATUS   |  You are in the wild. Be careful." << endl;
			}

			//print the map
			cout << endl << "WORLD CORDS: Map shows " << "(" << aaron.xcord - 4 << "," << aaron.ycord - 4 << ")" << " to " << "(" << aaron.xcord + 4 << "," << aaron.ycord + 4 << "); " << "Currently at " << "(" << aaron.xcord << "," << aaron.ycord << ")" << endl;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (j == 4 && i == 4) {
						cout << aaron.symbol << " ";
					}
					else {
						if (!map[aaron.xcord + j - 4][aaron.ycord - i + 4].discovered)
							cout << "? ";
						else
							cout << map[aaron.xcord + j - 4][aaron.ycord - i + 4].symbol << " ";
					}
				}
				cout << endl;
			}

			
			//take in the map movement input
			cout << "Use WASD to move your character.";
			if (map[aaron.xcord][aaron.ycord].symbol != '+')
				cout << " Use 'e' to enter locations!";
			cout << endl;
			
			while (!goodInput) {

				cout << ">> ";
				cin >> input;

				//player movement input
				if (equalString("w", input)) {
					aaron.ycord++;
					goodInput = true;
				}
				else if (equalString("s", input)) {
					aaron.ycord--;
					goodInput = true;
				}
				else if (equalString("a", input)) {
					aaron.xcord--;
					goodInput = true;
				}
				else if (equalString("d", input)) {
					aaron.xcord++;
					goodInput = true;
				}
				//if entering a town....
				else if (map[aaron.xcord][aaron.ycord].symbol == 'T' && (equalString(input, "enter") || equalString(input, "e"))) {
					map[aaron.xcord][aaron.ycord].discovered = true;
					cout << "(@) You have entered town. This town is " << TownDangerLevel(map[aaron.xcord][aaron.ycord].dangerLevel) << endl;

					//chance to get attacked upon entering the town
					int attackChance;
					if (map[aaron.xcord][aaron.ycord].dangerLevel != 0)
						attackChance = rand() % map[aaron.xcord][aaron.ycord].dangerLevel;

					if (attackChance == 0)
						EncounterAttacker(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.exp);

					bool inTown = true;
					while (inTown) {
						cout << endl;
						int choice = EnterTown(map[aaron.xcord][aaron.ycord].symbol, map[aaron.xcord][aaron.ycord].dangerLevel);

						//begin town options
						if (choice == 1) {
							EncounterTrader(aaron.health, aaron.maxHealth, aaron.totalHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.weapon, aaron.helmS, aaron.helm, aaron.chestS, aaron.chest, aaron.pantsS, aaron.pants, aaron.shoesS, aaron.shoes);
						}
						else if (choice == 2) {
							EncounterWeaponSmith(aaron.wAttack, aaron.weapon, aaron.money);
						}
						else if (choice == 3) {
							//search
							int randChan = rand() % 6;
							//if they find something...
							if (randChan == 0 || randChan == 1) {
								int item = rand() % 120;
								item = FindItem(item);

								cout << "Would you like to keep this item? (Y/N)?" << endl << ">> ";

								bool goodInput = false;
								while (!goodInput) {
									cin >> input;

									if (equalString("yes", input) || equalString("y", input)) {
										goodInput = true;
										EquipItem(aaron.health, aaron.maxHealth, aaron.totalHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.weapon, aaron.helmS, aaron.helm, aaron.chestS, aaron.chest, aaron.pantsS, aaron.pants, aaron.shoesS, aaron.shoes, item);
									}
									else if (equalString("no", input) || equalString("n", input)) {
										goodInput = true;
									}
									else
										cout << "(ERROR) That's not an option." << endl;
								}
							}
							//encounter an attacker while searching
							else if (randChan == 2 || (map[aaron.xcord][aaron.ycord].dangerLevel < 3 && randChan > 3) || map[aaron.xcord][aaron.ycord].dangerLevel == 0)  {
								int numberOfAttackers = 5;
								string attacker[5] = { "Aggressive Mouse", "Alley Cat", "Armed Mugger", "Sly Bandit", "Wretched Ghoul" };
								int attackerLvl = rand() % numberOfAttackers;
								int aa = rand() % (attackerLvl + 1) + 1;
								int ah = rand() % (attackerLvl + 1) + 1;

								if (map[aaron.xcord][aaron.ycord].dangerLevel == 0) {
									aa++;
									ah++;
								}

								cout << endl << "(!) While searching, you ran into a " << attacker[attackerLvl] << "!" << endl;
								BeginBattle(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.exp, aa, ah, attacker[attackerLvl]);

							}
							else {
								cout << "Nothing to be found here...." << endl;
							}
						}
						else if (choice == 4) {
							Chat(aaron.health, map[aaron.xcord][aaron.ycord].dangerLevel, aaron.weapon, aaron.wAttack);
						}
						else if (choice == 5) {
							//attack a town
							cout << "(!) Attacking the town!" << endl;
							int townProtectorAttack = rand() % 6 + 10;
							int townProtectorHealth = rand() % 5 + 11;
							BeginBattle(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.exp, townProtectorAttack, townProtectorHealth, "Town Protector");
						}
						else {
							cout << "(@) You have left town." << endl;
							inTown = false;
						}
					}

					//give a chance to run into something
					//int item = EnterScenario(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, 1);
					//EquipItem(aaron.health, aaron.maxHealth, aaron.totalHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.weapon, aaron.helmS, aaron.helm, aaron.chestS, aaron.chest, aaron.pantsS, aaron.pants, aaron.shoesS, aaron.shoes, item);
					goodInput = true;
				}
				else {
					cout << "(ERROR) That's not an option." << endl;
				}
				//end choices when entering town
		}
			//end of goodInput loop

			//run a chance of them running into something,
			if (RunChance(map[aaron.xcord][aaron.ycord].symbol) == 0) {
				EncounterAttacker(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.exp);
			}
			else if (RunChance(map[aaron.xcord][aaron.ycord].symbol) == 1) {
				//enter scenario returns with an item id if you find one in scenario, if not, with -1
				int itemF = EnterScenario(aaron.health, aaron.maxHealth, aaron.attack, aaron.wAttack, aaron.money, 1);
				EquipItem(aaron.health, aaron.maxHealth, aaron.totalHealth, aaron.attack, aaron.wAttack, aaron.money, aaron.weapon, aaron.helmS, aaron.helm, aaron.chestS, aaron.chest, aaron.pantsS, aaron.pants, aaron.shoesS, aaron.shoes, itemF);
			}

	}
	//end of game loop

}

void EncounterAttacker(int &h, int &mh, int &a, int &wa, int &coins, int &e) {
	int c = rand() % 25;
	string attacker = "";
	int aa;
	int ah;
	string input;

	if (c == 0) {
		attacker = "Rabies squirrel";
		aa = rand() % 2 + 1; // 1-2
		ah = rand() % 2 + 1; // 1-2
	}
	else if (c == 1) {
		attacker = "Wild dog";
		aa = rand() % 2 + 2; // 2-3
		ah = rand() % 2 + 2; // 2-3
	}
	else if (c == 2) {
		attacker = "Mugger";
		aa = rand() % 2 + 3; // 3-4
		ah = rand() % 3 + 3; // 3-5
	}
	else if (c == 3) {
		attacker = "Bandit";
		aa = rand() % 3 + 3; // 3-5
		ah = rand() % 3 + 3; // 3-5
	}
	else if (c == 4) {
		attacker = "Uncanny Bear";
		aa = rand() % 3 + 3; //3-5
		ah = rand() % 3 + 5; //5-7
	}
	else if (c == 5) {
		attacker = "Deformed mutant";
		aa = rand() % 3 + 4; // 4-6
		ah = rand() % 4 + 1; // 1-4
	}
	else if (c == 6) {
		attacker = "Rapid cat";
		int rc = rand() % 3;
		if (rc == 0)
			attacker = "Baloo the Rapid Cat";
		aa = rand() % 2 + 2; // 2-3
		ah = rand() % 2 + 2; // 2-3
	}
	else if (c == 7) {
		attacker = "Fleshing eating ghoul";
		aa = rand() % 5 + 3; // 3-4
		ah = rand() % 3 + 2; // 2-4
	}
	else if (c == 8) {
		attacker = "Lizard man";
		aa = rand() % 2 + 3; // 3-4
		ah = rand() % 5 + 2; // 2-6
	}
	else if (c == 9) {
		attacker = "Unicorn";
		aa = rand() % 1 + 7; // 7
		ah = rand() % 1 + 7; // 7
	}
	else if (c == 10) {
		attacker = "Morbid Goblin";
		aa = rand() % 2 + 2; // 2-3
		ah = rand() % 2 + 4; // 4-5
	}
	else if (c == 11) {
		attacker = "Supernatural Wraith";
		aa = rand() % 2 + 8; // 8-9
		ah = rand() % 2 + 2; // 2-3
	}
	else if (c == 12) {
		attacker = "Nightmare Monkey";
		aa = rand() % 5 + 5; // 5-9
		ah = rand() % 3 + 6; // 6-8
	}
	else if (c == 13) {
		attacker = "Spooky Raccon";
		aa = rand() % 3 + 1; // 1-3	
		ah = rand() % 2 + 1; // 1-2
	}
	else if (c == 14) {
		attacker = "Bloodthristy Mouse";
		aa = rand() % 2 + 2; // 2-3
		ah = rand() % 2 + 1; // 1-2
	}
	else if (c == 15) {
		attacker = "Menacing Owl";
		aa = rand() % 2 + 3; // 3-4 
		ah = rand() % 2 + 2; // 2-3
	}
	else if (c == 16) {
		attacker = "Mysterious Wisp";
		aa = rand() % 2 + 3; // 3-4 
		ah = rand() % 3 + 1; // 1-3
	}
	else if (c == 17) {
		attacker = "Cannibalistic Clown";
		aa = rand() % 4 + 3; // 3-6
		ah = rand() % 1 + 5; // 5
	}
	else if (c == 18) {
		int rc = rand() % 3;
		if (rc == 0) {
			attacker = "Crazed Chainsaw wielding Lumberjack";
			aa = rand() % 5 + 5; // 5-9 
			ah = rand() % 3 + 3; // 3-5
		}
		else if (rc == 1) {
			attacker = "Crazed Axe wielding Lumberjack";
			aa = rand() % 2 + 4; // 4-5 
			ah = rand() % 3 + 2; // 2-4
		}
		else {
			attacker = "Lumberjack";
			aa = rand() % 3 + 2; // 2-4 
			ah = rand() % 3 + 2; //	2-4
		}
	}
	else if (c == 19) {
		attacker = "Infected Bobcat";
		aa = rand() % 2 + 5; // 5-6
		ah = rand() % 2 + 3; // 3-4
	}
	else if (c == 19) {
		attacker = "Infected Bobcat";
		aa = rand() % 2 + 5; // 5-6
		ah = rand() % 2 + 3; // 3-4
	}
	else if (c == 20) {
		attacker = "Beefy Brawler";
		aa = rand() % 1 + 6; // 6
		ah = rand() % 1 + 6; // 6
	}
	else if (c == 21) {
		int rc = rand() % 3;
		if (rc == 0) {
			attacker = "Vicious Child";
			aa = rand() % 3 + 3; // 3-5
			ah = rand() % 2 + 3; // 3-4
		}
		else if (rc == 1) {
			attacker = "Blood Curdling Boy";
			aa = rand() % 3 + 4; // 4-6 
			ah = rand() % 3 + 2; // 2-4
		}
		else {
			attacker = "Bloodthristy Girl";
			aa = rand() % 3 + 3; // 3-5 
			ah = rand() % 4 + 2; //	2-5
		}
	}
	else if (c == 22) {
		attacker = "Giga Worm";
		aa = rand() % 3 + 4; // 4-6
		ah = rand() % 6 + 1; // 1-6
	}
	else if (c == 23) {
		attacker = "Psychopathic Archer";
		aa = rand() % 3 + 5; // 4-7
		ah = rand() % 2 + 3; // 3-4
	}
	else {
		attacker = "Giant Spectral beast";
		aa = rand() % 3 + 4; // 4-7
		ah = rand() % 6 + 5; // 5-11
	}

	cout << endl << "(!) You have encountered a " << attacker << " with " << aa << " attack, and " << ah << " health" << endl;

	BeginBattle(h, mh, a, wa, coins, e, aa, ah, attacker);

}

void BeginBattle(int &h, int &mh, int &a, int&wa, int &c, int &e, int aa, int ah, string attacker) {
	string input;
	int pointsEarned = aa + ah;

	system("pause");

	//begin battle loop
	while (h > 0 && ah > 0) {
		int oppAtt = rand() % 2;
		bool dodge = false;
		bool run = false;
		bool oppAlive = true;
		bool posioned = false;
		int posionDamage = 0;

		cout << endl << "Your Health: " << h << "   Your Attack: " << a + wa << "  // VS. //  " << attacker << " Health: " << ah << "   " << attacker << " Attack: " << aa << endl;
		cout << "You must now Attack, Dodge, or Flee. " << endl;

		bool goodInput = false;
		while (!goodInput) {
			cout << ">> ";
			cin >> input;

			//check to see if opponent dodged
			if (equalString("attack", input) || equalString("a", input)) {
				goodInput = true;
				if (oppAtt == 1) {
					cout << "The " << attacker << " dodged your attack!" << endl;
				}
				else {
					//give chance for critcal hit, then extra critcal hit
					int critChance = rand() % 10;

					if (critChance == 0) {
						int doubleCritChance = rand() % 10;

						if (doubleCritChance == 0) {
							cout << "You attacked the " << attacker << " for " << ((a+wa) * 4) << "extremely critical damage!" << endl;
							ah -= (a+wa)*4;
						}
						else {
							cout << "You attacked the " << attacker << " for " << (a+wa) * 2 << " critical damage!" << endl;
							ah -= (a+wa) * 2;
						}
					}
					else {
						//else normal attack damage
						cout << "You attacked the " << attacker << " for " << a+wa << " damage!" << endl;
						ah -= a + wa;
					}

					if (ah <= 0) {
						oppAlive = false;
						cout << endl << "(*) You have killed the " << attacker << endl;
					}
				}
			}
			else if (equalString("dodge", input) || equalString("d", input)) {
				dodge = true;
				goodInput = true;
			}
			else if (equalString("flee", input) || equalString("f", input)) {
				goodInput = true;
				cout << "You had a 2/" << ah <<" chance to escape." << endl;
				int cte = rand() % ah;

				if (cte < 2) {
					cout << "You successfully ran away." << endl;
					run = true;
					break;
				}
				cout << "You failed to run away... " << endl;
			}
			else {
				cout << "That's not an option." << endl;
			}
		}
		//end of input loop

		if (oppAlive && (oppAtt == 0 && !run)) {
			if (dodge) {
				cout << "You dodged the " << attacker << "s attack!" << endl;
			}
			else {
				cout << "The " << attacker << " attacked you for " << aa << " damage" << endl;
				h -= aa;
			}
		}

		if (run)
			break;
	}
	//end of battle loop

	if (h <= 0) {
		cout << "You have died. Better luck next time." << endl;
		system("pause");
		exit(0);
	}
	else {
		cout << "(*) You managed to survive the attack with " << h << " health!" << endl;
		if (ah <= 0) {
			int expGained = rand() % pointsEarned + 2;
			cout << "(*) You gained " << expGained << " exp points!" << endl;
			e += expGained;
			int coinchance = rand() % 5;
			if (coinchance == 1) {
				int coinsFound = rand() % pointsEarned + 2;
				cout << "($) The " << attacker << " dropped " << coinsFound << " coins." << endl;
				c += coinsFound;
			}
		}
	}
}

void EncounterTrader(int &h, int &mh, int&th, int &a, int &wa, int &c, string &weapon, string &helmS, int &helm, string &chestS, int &chest, string &pantsS, int &pants, string &shoesS, int &shoes) {
	//
	string itemList[80] = {"Basic First Aid", "Old Bandage", "Canteen Of Water", "Canned Beans", "Roll of Guaze", "Army Grade Medkit", "Morphine", "Can of Tuna", "Wattle Bottle", "Gallon Of Water", "Healing Cream", "Cooked Pork", "Expensive First Aid Kit", "Enchanted Brew", "Granola Bar", "35", "36", "37", "38", "39", "Chainmail Vest", "Kevlar Vest", "Construction Helmet", "Knee Pads", "Football Helmet", "Tennis Shoes", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "Kung-Fu How-To Manual", "Ancient Fighting Tip", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "Fork", "Butcher Knife", "Sharpened Stick", "Rake", "Spiked Bat", "Poision Tipped Dagger", "Woodcutters Axe", "Pocket Knife", "Wooden Plank", "Hammer", "Katana", "Machete", "Blow Torch", "Homemade Shiv", "Large Staff", "Copper Pipe", "96", "97", "98", "99"};
	int itemAttributes[120] = {2, 1, 2, 2, 3, 8, 4, 3, 1, 3, 2, 5, 4, 5, 1, 0, 0, 0, 0, 0, 4, 5, 2, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 2, 4, 7, 4, 1, 2, 2, 6, 5, 6, 3, 4, 4, 0, 0, 0, 0};
	//Item IDs                20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99
	//includes all items from 20-99, health stuff(20-39), armor(40-59), base attack upgrades(60-79), and weapons(80-99)
	//inclues each items one number value, whether it be the armors strength or the weapons attack, will know based off ID value
	

	
	string traderName;
	int chanceName = 0; // rand() % 6;
	int numOfItems;
	int price;
	int itemIds[10];
	int itemPrice[10];
	string input;
	int intput;

	cout << "($) You encountered a ";

	//choose trader random trader list
	if (chanceName == 0) {
		traderName = "Trader Wagon";
		cout << traderName << "." << endl;
		cout << traderName << "'s Items: " << endl;

		numOfItems = rand() % 3 + 4;

	}
	else if (chanceName == 1) {
		traderName = "Traveling Merchant";
	}
	else if (chanceName == 2) {
		traderName = "Peddling Shopkeeper";
	}
	else if (chanceName == 3) {
		traderName = "Small Shopkeeper";
	}
	else if (chanceName == 4) {
		traderName = "Sketchy Witchcraft Healer";
	}
	else if (chanceName == 5) {
		traderName = "Greedy Trader";
	}
	else if (chanceName == 6) {
		traderName = "Unqualified Doctor";
	}
	//list out items for sale
	for (int i = 0; i < numOfItems; i++) {
		itemIds[i] = CheckID(900, 6);
		itemPrice[i] = DetermineTraderPrice(itemAttributes[itemIds[i]]);
		cout << i + 1 << "] " << itemList[itemIds[i]] << "(" << itemAttributes[itemIds[i]] << ")" << " for $" << itemPrice[i] << endl;  //ADD attack, health, notes in () when selling items, instead of just a number
	}
	cout << numOfItems + 1 << "] Leave" << endl << "Type a # to choose that option: " << endl;

	bool goodInput = false;
	while (!goodInput) {
		cout << ">> ";
		cin >> intput;

		if (intput > 0 && intput <= numOfItems) {
			//buy item
			if (c >= itemPrice[intput - 1]) {
				EquipItem(h, mh, th, a, wa, c, weapon, helmS, helm, chestS, chest, pantsS, pants, shoesS, shoes, itemIds[intput - 1] + 20);
			}
			else
				cout << "(*) You don't have enough coins to buy the " << itemList[itemIds[intput-1]]<< endl;
			goodInput = true;
		}
		else if (intput == numOfItems + 1) {
			//leave trading menu

			goodInput = true;
		}
		else {
			cout << "(ERROR) That number is not an option! Please try again." << endl;
		}
	}



}

int DetermineTraderPrice(int item) {
	int price = item + (rand() % (item+1) + (rand() % 5));
	return price;
}

int EnterScenario(int &h, int &mh, int &a, int &wa, int &c, int x = 1) {
	int scenario = rand() % 8;
	int itemFound = -1;
	bool search = false;
	bool house = false;
	bool monster = false;
	bool cannibal = false;
	string input;

	if (x == 1)
		x = rand() % 3;

	if (x == 0) {
		if (scenario == 0) {
			cout << endl << "(?) You have stumbled across the remains of an unlucky traveler...." << endl << "Search their remains?";
		}
		else if (scenario == 1) {
			cout << endl << "(?) There is a greatly weathered wagon broken down into the sand." << endl << "Search through it's contents?";
		}
		else if (scenario == 2) {
			cout << endl << "(?) An abandoned campsite lies in front of you. Old barrels, crates, and tents lay scattered about." << endl << "Search the campsite?";
		}
		else if (scenario == 3) {
			cout << endl << "(?) A handmade wooden cross sits tilted to mark a forgotton grave." << endl << "Unearth the grave to search its corpse?";
		}
		else if (scenario == 4) {
			cout << endl << "(?) A gruel scene of blood, guts, and body parts are scattered about. It looks to be very recent.... " << endl << "Use the opportunity to search for items?";
			monster = true;
		}
		else if (scenario == 5) {
			cout << endl << "(?) You encountered an old shack with smoke billowing from the top. Outside is littered with heads of goats on stakes. Looking carefully, you notice a few even look human." << endl << "Enter the shack?";
			cannibal = true;
		}
		else if (scenario == 6) {
			cout << endl << "(?) An old house, mostly eroded away from the harsh elements, silently lies in front of you." << endl;
			house = true;
		}
		else if (scenario == 7) {
			cout << endl << "(?) " << endl << "";
		}
		cout << " (Y/N)?" << endl << ">> ";

		bool goodInput = false;
		while (!goodInput) {
			cin >> input;

			if (equalString("yes", input) || equalString("y", input)) {
				search = true;
				goodInput = true;
			}
			else if (equalString("no", input) || equalString("n", input)) {
				search = false;
				goodInput = true;
			}
			else {
				cout << "That's not an option." << endl;
			}
		}
	}

	if (search) {
		if (house || cannibal || monster) {
			if (house) {
				cout << "You walk up to the front door of the house and softly push open the front door. It swings open easily." << endl;
			}
			if (cannibal) {
				cout << "You cautiously enter the hut and take a look around. Various tools for butchering animals lie about a wooden desk, and a cloth bed lies in the corner, but no one seems to be home." << endl;
			}
			if (monster) {
				cout << "" << endl;
			}
		}

		itemFound = rand() % 120;
		itemFound = FindItem(itemFound);
		

		//ask if they want the item
		cout << "Would you like to keep this item? (Y/N)?" << endl << ">> ";

		bool goodInput = false;
		while (!goodInput) {
			cin >> input;

			if (equalString("yes", input) || equalString("y", input)) {
				goodInput = true;
			}
			else if (equalString("no", input) || equalString("n", input)) {
				itemFound = -1;
				goodInput = true;
			}
			else
				cout << "That's not an option." << endl;
		}

	}
	else if (!search && x == 0) {
		if (house) {
			cout << "As inviting as the house seems, you decide against it and continue on." << endl;
		}
		else if (cannibal) {
			cout << "You take the staked heads as a fair warning and decide to pass by (at a good distance) the gruesome hut." << endl;
		}
		else if (monster) {
			cout << "You decide you don't want to stay around to find out what happened, and continue walking past." << endl;
		}
		else {
			cout << "You decide to keep heading on your way." << endl;
		}
		itemFound = -1;
	}

	return itemFound;
}

int CheckID(int item, int func) {
	int numOfCurrencyItems = 8;
	int numOfHealingItems = 15;
	int numOfMaxHealthItems = 6;
	int numOfBaseAttackItems = 2;
	int numOfWeaponItems = 16;
	int numOfCompanions = 0;

	bool inRange = false;

	while (!inRange) {
		//makes sure we have an item currently registered as that ID number, if not, recalcutes random ID and tries again
		if ((item < 20 && item < numOfCurrencyItems) || ((item < 40 && item > 19) && item - 20 < numOfHealingItems) || ((item < 60 && item > 39) && item - 40 < numOfMaxHealthItems) || ((item < 80 && item > 59) && item - 60 < numOfBaseAttackItems) || ((item < 100 && item > 79) && item - 80 < numOfWeaponItems) || ((item < 120 && item > 99) && item - 100 < numOfCompanions)) {
			if (func == 0)
				inRange = true;
			if (func == 6) {
				if (item > 19 && item < 100)
					item -= 20;
					inRange = true;
			}
		}
		else {
			item = rand() % 120;
		}
	}

	return item;
}

int FindItem(int item) {

	if (item == -1)
		return -1;

	item = CheckID(item, 0);

	//now we find the item
	switch (item) {
		//currency items 0-19
		case 0: cout << "You have found a bag of 3 coins." << endl;
			break;
		case 1: cout << "You have found a bag of 2 coins." << endl;
			break;
		case 2: cout << "You have found 1 coin." << endl;
			break;
		case 3: cout << "You have found a gold bar worth 17 coins!" << endl;
			break;
		case 4: cout << "You have found a Jewel worth 14 coins!" << endl;
			break;
		case 5: cout << "You have found a bag of 5 coins!" << endl;
			break;
		case 6: cout << "You have found a bag of 4 coins!" << endl;
			break;
		case 7: cout << "You have found some metal ore worth 8 coins!" << endl;
			break;
		//healing items 20-39
		case 20: cout << "You have found a basic first aid kit that heals for 2 health." << endl;
			break;
		case 21: cout << "You have found an old bandage that heals for 1 health." << endl;
			break;
		case 22: cout << "You have found a canteen of water that heals for 2 health." << endl;
			break;
		case 23: cout << "You have found canned beans that heals for 2 health." << endl;
			break;
		case 24: cout << "You have found a roll of guaze heals for 3 health." << endl;
			break;
		case 25: cout << "You have found an army grade medkit that heals for 8 health!" << endl;
			break;
		case 26: cout << "You have found morphine that heals for 4 health." << endl;
			break;
		case 27: cout << "You have found a can of tuna that heals for 3 health." << endl;
			break;
		case 28: cout << "You have found a water bottle that heals for 1 health." << endl;
			break;
		case 29: cout << "You have found a gallon of water that heals for 2 health." << endl;
			break;
		case 30: cout << "You have found some healing cream that heals for 2 health." << endl;
			break;
		case 31: cout << "You have found cooked pork that heals for 5 health!" << endl;
			break;
		case 32: cout << "You have found an expensive First Aid Kit that heals for 4 health." << endl;
			break;
		case 33: cout << "You have found an enchanted brew that heals for 5 health." << endl;
			break;
		case 34: cout << "You have found a granola bar that heals for 1 health." << endl;
			break;
		//max health upgrade items 40-59
		case 40: cout << "You have found a chainmail vest! (4 Chest Armor)" << endl;
			break;
		case 41: cout << "You have found a kevlar vest! (5 Chest Armor)" << endl;
			break;
		case 42: cout << "You have found a construction helmet. (2 Helmet Armor)" << endl;
			break;
		case 43: cout << "You have found a pair of knee pads. (1 Pants Armor)" << endl;
			break;
		case 44: cout << "You have found a football helmet. (3 Helmet Armor)." << endl;
			break;
		case 45: cout << "You have found a pair of old tennis shoes. (1 Shoe Armor)" << endl;
			break;
		//base attack upgrade items 60-79
		case 60: cout << "You have found a Kung-Fu How-To Manual. (+1 Base Attack)" << endl;
			break;
		case 61: cout << "You have found an ancient fighting tip. (+2 Base Attack)" << endl;
			break;
		//weapon items 80-99
		case 80: cout << "You have found a fork. (+1 Damage)" << endl;
			break;
		case 81: cout << "You have found a butcher knife. (+3 Damage)" << endl;
			break;
		case 82: cout << "You have found a sharpened stick. (+2 Damage)" << endl;
			break;
		case 83: cout << "You have found a rake. (+2 Damage)" << endl;
			break;
		case 84: cout << "You have found a spiked bat. (+4 Damage)" << endl;
			break;
		case 85: cout << "You have found a poison tipped dagger! (+7 Damage)" << endl;
			break;
		case 86: cout << "You have found a wood cutter's axe. (+4 Damage)" << endl;
			break;
		case 87: cout << "You have found a pocket knife. (+1 Damage)" << endl;
			break;
		case 88: cout << "You have found a wooden plank. (+2 Damage)" << endl;
			break;
		case 89: cout << "You have found a hammer. (+2 Damage)" << endl;
			break;
		case 90: cout << "You have found a katana! (+6 Damage)" << endl;
			break;
		case 91: cout << "You have found a machete. (+5 Damage)" << endl;
			break;
		case 92: cout << "You have found a blow torch! (+6 Damage)" << endl;
			break;
		case 93: cout << "You have found a homemade shiv. (+3 Damage)" << endl;
			break;
		case 94: cout << "You have found a large staff. (+4 Damage)" << endl;
			break;
		case 95: cout << "You have found a copper pipe. (+4 Damage)" << endl;
			break;
	}

	return item;
}

void AddItemToInventory(int invSpace, string name, int value, int id) {

}

void EquipItem(int &h, int &mh, int &th, int &a, int &wa, int &c, string &weapon, string &helmS, int &helm, string &chestS, int &chest, string &pantsS, int &pants, string &shoesS, int &shoes, int item) {
	if (item == -1)
		return;

	//now we find the item
	switch (item) {
		//currency items 0-19
	case 0: cout << "You have taken the bag of 3 coins." << endl;
		c += 3;
		break;
	case 1: cout << "You have taken the bag of 2 coins." << endl;
		c += 2;
		break;
	case 2: cout << "You took the coin." << endl;
		c += 1;
		break;
	case 3: cout << "You took the gold bar worth 17 coins!" << endl;
		c += 17;
		break;
	case 4: cout << "You grabbed the Jewel worth 14 coins!" << endl;
		c += 14;
		break;
	case 5: cout << "You have taken the bag of 5 coins!" << endl;
		c += 5;
		break;
	case 6: cout << "You took the bag of 4 coins!" << endl;
		c += 4;
		break;
	case 7: cout << "You took the metal ore worth 8 coins!" << endl;
		c += 8;
		break;
		//healing items 20-39
	case 20: cout << "You used the basic first aid kit and healed for 2 health." << endl;
		h = h + 2;
		if (h > th)
			h = th;
		break;
	case 21: cout << "You used the old bandage and healed for 1 health." << endl;
		h = h + 1;
		if (h > th)
			h = th;
		break;
	case 22: cout << "You drank the canteen of water and restored 2 health." << endl;
		h = h + 2;
		if (h > th)
			h = th;
		break;
	case 23: cout << "You ate the canned beans and restored 2 health." << endl;
		h = h + 2;
		if (h > th)
			h = th;
		break;
	case 24: cout << "You used the roll of guaze and restored 3 health." << endl;
		h = h + 3;
		if (h > th)
			h = th;
		break;
	case 25: cout << "You used the army grade medkit and restored 8 health!" << endl;
		h = h + 8;
		if (h > th)
			h = th;
		break;
	case 26: cout << "You used morphine to restore 4 health." << endl;
		h = h + 4;
		if (h > th)
			h = th;
		break;
	case 27: cout << "You ate the can of tuna and restored 3 health." << endl;
		h = h + 3;
		if (h > th)
			h = th;
		break;
	case 28: cout << "You drank the water bottle to restore 1 health." << endl;
		h = h + 1;
		if (h > th)
			h = th;
		break;
	case 29: cout << "You drank the gallon of water and restored 2 health." << endl;
		h = h + 2;
		if (h > th)
			h = th;
		break;
	case 30: cout << "You used the healing cream and healed 2 health." << endl;
		h = h + 2;
		if (h > th)
			h = th;
		break;
	case 31: cout << "You consumed the cooked pork and regained 5 health!" << endl;
		h = h + 5;
		if (h > th)
			h = th;
		break;
	case 32: cout << "You used the expensive First Aid Kit and healed up 4 health." << endl;
		h = h + 4;
		if (h > th)
			h = th;
		break;
	case 33: cout << "You drank the enchanted brew and regained 5 health." << endl;
		h = h + 5;
		if (h > th)
			h = th;
		break;
	case 34: cout << "You munched down the granola bar and regained 1 health." << endl;
		h = h + 1;
		if (h > th)
			h = th;
		break;
		//max health upgrade items 40-59
	case 40: cout << "You equipped the chainmail vest! (4 Chest Armor)" << endl;
		chest = 4;
		h += 4;
		chestS = "Chainmail Vest";
		break;
	case 41: cout << "You equipped the kevlar vest! (5 Chest Armor)" << endl;
		chest = 5;
		h += 5;
		chestS = "Kevlar Vest";
		break;
	case 42: cout << "You put on construction helmet. (2 Helmet Armor)" << endl;
		helm = 2;
		h += 2;
		helmS = "Construction Helmet";
		break;
	case 43: cout << "You put on the pair of knee pads. (1 Pants Armor)" << endl;
		pants = 1;
		h += 1;
		pantsS = "Knee Pads";
		break;
	case 44: cout << "You put on the football helmet. (3 Helmet Armor)." << endl;
		helm = 3;
		h += 3;
		helmS = "Football Helmet";
		break;
	case 45: cout << "You have found a pair of old tennis shoes. (1 Shoe Armor)" << endl;
		shoes = 1;
		h += 1;
		shoesS = "Tennis Shoes";
		break;
		//base attack upgrade items 60-79
	case 60: cout << "Your base attack has increased by one from reading the Kung-Fu How-To Manual." << endl;
		a++;
		break;
	case 61: cout << "Your base attacked has increased by two from learning an ancient fighting technique!" << endl;
		a += 2;
		break;
		//weapon items 80-99
	case 80: cout << "You equipped the fork." << endl;
		wa = 1;
		weapon = "Fork";
		break;
	case 81: cout << "You equipped the butcher knife." << endl;
		wa = 3;
		weapon = "Butcher Knife";
		break;
	case 82: cout << "You equipped the sharpened stick. (+2 Damage)" << endl;
		wa = 2;
		weapon = "Sharpened Stick";
		break;
	case 83: cout << "You equipped the rake. (+2 Damage)" << endl;
		wa = 2;
		weapon = "Rake";
		break;
	case 84: cout << "You equipped the spiked bat. (+4 Damage)" << endl;
		wa = 4;
		weapon = "Spiked Bat";
		break;
	case 85: cout << "You equipped the poision tipped dagger! (+7 Damage)" << endl;
		wa = 7;
		weapon = "Poison Dagger";
		break;
	case 86: cout << "You equipped the woodcutter's axe. (+4 Damage)" << endl;
		wa = 4;
		weapon = "Woodcutter's Axe";
		break;
	case 87: cout << "You equipped the pocket knife. (+1 Damage)" << endl;
		wa = 1;
		weapon = "Pocket Knife";
		break;
	case 88: cout << "You equipped the wooden plank. (+2 Damage)" << endl;
		wa = 2;
		weapon = "Wooden Plank";
		break;
	case 89: cout << "You equipped the hammer. (+2 Damage)" << endl;
		wa = 2;
		weapon = "Hammer";
		break;
	case 90: cout << "You equipped the katana! (+6 Damage)" << endl;
		wa = 6;
		weapon = "Katana";
		break;
	case 91: cout << "You equipped the machete. (+5 Damage)" << endl;
		wa = 5;
		weapon = "Machete";
		break;
	case 92: cout << "You equipped the blow torch! (+6 Damage)" << endl;
		wa = 6;
		weapon = "Blow Torch";
		break;
	case 93: cout << "You equipped the homemade shiv. (+3 Damage)" << endl;
		wa = 3;
		weapon = "Homemade Shiv";
		break;
	case 94: cout << "You equipped the large staff. (+4 Damage)" << endl;
		wa = 4;
		weapon = "Large Staff";
		break;
	case 95: cout << "You equipped the copper pipe. (+4 Damage)" << endl;
		wa = 4;
		weapon = "Copper Pipe";
		break;
	}
}

void EncounterWeaponSmith(int &wa, string &weapon, int &c) {
	int textChance = rand() % 6;
	string input;

	//check if they have a weapon
	if (weapon.compare("None") == 0) {
		cout << "You need a weapon to visit the weapon smith." << endl;
	}
	else {

		if (textChance == 0)
			cout << "Weapon Smith: What can I do ya for today?" << endl;
		else if (textChance == 1)
			cout << "Weapon Smith: What do you want?" << endl;
		else if (textChance == 2)
			cout << "Weapon Smith: If you're looking for some killing gear, you found the right guy!" << endl;
		else if (textChance == 3)
			cout << "Weapon Smith: How could I help you today mister?" << endl;
		else if (textChance == 4)
			cout << "Weapon Smith: I'm the best in town!" << endl;
		else if (textChance == 5)
			cout << "Weapon Smith: I've been praticing my trade since I was 4." << endl;

		//options
		cout << " Upgrade-Weapon    Rename-Weapon    Sell-Weapon" << endl << ">> ";
		cin >> input;

		bool goodInput = false;
		while (!goodInput) {
			if (equalString("upgrade-weapon", input)) {
				goodInput = true;
				Weapon(1, wa, weapon, c);
			}
			else if (equalString("rename-weapon", input)) {
				goodInput = true;
				Weapon(2, wa, weapon, c);
			}
			else if (equalString("sell-weapon", input)) {
				goodInput = true;
				Weapon(3, wa, weapon, c);
			}
			else {
				cout << "That's not an option." << endl;
			}
		}
	}
}

void Weapon(int choice, int &wa, string &weapon, int &c) {
	int price;
	int addedAttack = rand() % 2 + 1;
	string input;
	bool correct = false;

	switch (choice) {

		//upgrade
	case 1:
		price = rand() % wa + wa + 1;
		cout << "You have been offered an upgrade of " << addedAttack << " for the price of " << price << " coins." << endl;
		cout << "Do you accept this offer? (Y/N)" << endl;
		if (YesNo()) {
			//chceck to make sure they have the money to pay for it
			if (c >= price) {
				c -= price;
				wa += addedAttack;
				cout << "You upgraded your " << weapon << " for " << addedAttack << " damage." << endl;
			}
			else {
				cout << "You don't have enough coins!" << endl;
			}
		}
		break;

		//rename
	case 2:
		price = rand() % 10 + 15;
		cout << "Enter your weapons new name: ";
		while (!correct) {
			cin >> input;
			cout << "Is this correct? (Y/N) " << endl;
			if (YesNo()) {
				correct = true;
				weapon = input;
				cout << "Your weapon is now called " << weapon << "!" << endl;
			}
			else
				cout << "Please try again," << endl;
		}
		break;

		//sell
	case 3:
		price = rand() % (wa + 1) + 2;
		cout << "The weapon smith offered " << price << " coins for your " << weapon << "." << endl;
		cout << "Do you accept this offer? (Y/N)" << endl;
		if (YesNo()) {
			c += price;
			cout << "You sold your " << weapon << " for " << price << " coins." << endl;
		}
		break;
	}
}

int ItemLibrary(int item) {
	
	struct itemStruct {
		string name = "Name Of Item";
		int attribute = 0;
	}itemList;

	//itemStruct coins[20] = { {"Bag of Coins", 3}, {"Bag of Coins", 2}, {"Coin", 1}, {"Gold Bar", 17}, {"Jewel", 14}, {"Bag of Coins", 5}, {"Bag of Coins", 4}, {"Metal Ore", 8} };
	//itemStruct health[20] = { {"Basic First Aid Kit", 2}, {"Old Bandage", 1}, {"Canteen of Water", 2},{"Canned Beans", 2}, {"Roll of Guaze", 3}, {"Army Grade Medkit", 8}, {"Morphine", 4}, {"Can of Tuna" , 3}, {"Wattle Bottle", 1}, {"Gallon of Water", 3}, {"Healing Cream", 2}, {"Cooked Pork", 5}, {"Expensive First Aid Kit", 4}, {"Enchanted Brew", 5}, {"Granola Bar", 1}};
	//itemStruct maxHealth[20] = { {"Chainmail Vest", 4}, {"Kevlar Vest", 5}, {"Construction Helmet", 2}, {"Knee Pads", 1}, {"Football Helmet", 3}, {"Tennis Shoes", 1} };
	//itemStruct baseAttack[20] = { {"Kung-Fu How-To Manual", 1,}, {"Ancient Fighting Tip", 2} };
	//itemStruct weapons[20] = { {"Fork", 1}, {"Butcher Knife", 3}, {"Sharpened Stick", 2}, {"Rake", 2}, {"Spiked Bat", 4}, {"Poision Tipped Dagger", 7}, {"Woodcutters Axe", 4}, {"Pocket Knife", 1}, {"Wooden Plank", 2}, {"Hammer", 2}, {"Katana", 6}, {"Machete", 5}, {"Blow Torch", 6}, {"Homemade Shiv", 3}, {"Large Staff", 4}, {"Copper Pipe", 4} };
	//itemStruct companions[20];

	return item;
}

bool equalString(string str, string str2) {
	bool areEqual = true;

	if (tolower(str2[0]) == str[0])
		return true;

	if (str.length() == str2.length()) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != tolower(str2[i])) {
				areEqual = false;
			}
		}
	}
	else {
		areEqual = false;
	}

	return areEqual;
}

string TownDangerLevel(int dangerLevel) {
	if (dangerLevel == 0)
		return "very dangerous!";
	else if (dangerLevel == 1)
		return "dangerous.";
	else if (dangerLevel == 2)
		return "kinda dangerous.";
	else if (dangerLevel == 3)
		return "slightly safe.";
	else if (dangerLevel == 4)
		return "lawful(ish).";
	else if (dangerLevel == 5)
		return "fairly Safe.";
	else
		return "a decent place.";
}

int EnterTown(char s, int d) {

	int choice = 0;
	string level = "";
	string input = "";
	
	cout << "Town Status: " << TownDangerLevel(d) << endl;
	cout << "Choose one of the following options. Typing only the first letter of the option is valid input" << endl;
	cout << "  Trade    Weapon-Smith    Search    Chat    Attack    Leave" << endl;

	bool goodInput = false;
	while (!goodInput) {
		
		cout << ">> ";
		cin >> input;

		if (equalString("trade", input)) {
			return 1;
			goodInput = true;
		}
		else if (equalString("weapon-smith", input)) {
			return 2;
			goodInput = true;
		}
		else if (equalString("search", input)) {
			return 3;
			goodInput = true;
		}
		else if (equalString("chat", input)) {
			return 4;
			goodInput = true;
		}
		else if (equalString("attack", input)) {
			return 5;
			goodInput = true;
		}
		else if (equalString("leave", input)) {
			return 6;
			goodInput = true;
		}
		else {
			cout << "That's not an option." << endl;
		}
	}


	return choice;
	
}

//run a chance to run into something end of every loop
int RunChance(char s) {

	srand(time(NULL));

	int chanceToReturnB = rand() % 5;
	int b = rand() % 3;

	//is player on a road?
	if (s != '@') {
		if (chanceToReturnB == 3) {
			return b;
		}
	}
}

void Chat(int h, int dl, string weapon, int wa) {

	if (h < 5) {
		int chance = rand() % 3;

		if (chance == 0)
			cout << "Old Man: You don't look so well... " << endl;
		else if (chance == 1)
			cout << "Little Kid: What happened to you Mister?" << endl;
		else
			cout << "Random Lady: You need Medical Attention!" << endl;
	}
	else { 
		int chance1 = rand() % 2;
		int chance2 = rand() % 4;

		if (chance1 == 0) {
			//if you are low health..
			if (wa > 5) {
				cout << "People seem to be keeping an eye on your " << weapon << endl;
			}
			else {
				cout << "Little Girl: What are YOU looking at?" << endl;
			}
		}
		else if (dl < 5) {
			//if its a more dangerous town....
			if (chance2 == 0)
				cout << "Young Man: Get outta my face... " << endl;
			if (chance2 == 1)
				cout << "Homeless Boy: Got any bread o' coins ta spare?" << endl;
			if (chance2 == 2)
				cout << "Badly Scarred Man: Don't you come a step closer scum." << endl;
			else
				cout << "Dog: Bark! Bark bark!" << endl;
		}
		else {
			//if its a safer town...
			if (chance2 == 0)
				cout << "Young Women: Looks like you need a nice rest. " << endl;
			if (chance2 == 1)
				cout << "Homeless Man: Got a job to do? I need a good job." << endl;
			if (chance2 == 2)
				cout << "Old Grumpy Dude: Travelers always comin' in our towns n' killin' our people....  hurmph... " << endl;
			else
				cout << "Religious Leader: Repent! For the end is nigh!" << endl;
		}
	}

	system("pause");

}

bool YesNo() {
	string input;
	bool YesNo = true;

	cout << ">> ";
	cin >> input;

	if (equalString("yes", input) || equalString("y", input)) {
		YesNo = true;
		return YesNo;
	}
	else if (equalString("no", input) || equalString("n", input)) {
		YesNo = false;
		return YesNo;
	}
	else {
		cout << "That's not an option." << endl;
	}
	return YesNo;
}

