/*
This is a implementation for observer pattern in C++
Author: Nhannguyen

The Observer Pattern defines a one to many dependency between objects
so that one object changes state, all of its dependents are notified and updated automatically.

-----------
-Observer--(Notify()) =>>>>>>>>>>>>>>>>>>> Subject 
-----------
-+------+
-+------+++++++++++++++++
-+----------------------+
---------------------------------
- Concrete  -       -- Concrete -
- ObserverA -       -- ObserverB-
---------------------------------
--Notify() ----------- Notify()--
---------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

enum MATCHSTATE {
	START_MATCH = 0,
	FIRST_HALF = 1,
	HALF_TIME, 
	SECOND_HALF,
	EXTRA_1,
	EXTRA_2,
	PENALTY,
	END_MATCH
};

class Team {
private:
	int _numPlayer;
	int _goal;
	std::string _name;
public:
	Team() :_numPlayer(11), _goal(0), _name("Manchester United") {}
	Team(int p, int g, std::string name) : _numPlayer(p), _goal(g), _name(name) {}
	int getNumPlayer() { return _numPlayer; }
	void setNumPlayer(int n){ _numPlayer = n; }
	void score() { _goal++; }
	int getGoal() { return _goal; }
	void redCard() { _numPlayer--; }
	std::string getName() { return _name; }
	void setName(std::string name) { _name = name; }
};

// Observer interface
class Observer {
public:
	virtual void Update(MATCHSTATE, Team, Team) = 0;
};

// subject observer interface
class SubjectObserver {
public: 
	virtual void RegisterObserver(Observer) = 0;
	virtual void UnregisterObserver(Observer) = 0;
	virtual void NotifyObservers() = 0;
};

class Match : public SubjectObserver {
private:
	Team T1, T2;
	std::vector<Observer> observerList;
	MATCHSTATE state;
public:
	Match() :state(START_MATCH){}
	Match(Team _T1, Team _T2):
		state(START_MATCH),
		T1(_T1),
		T2(_T2) {}

	// change state of match
	void changeState() {
		if (state == SECOND_HALF && T1.getGoal() != T2.getGoal()) {
			endMatch();
			return;
		}
		state = (MATCHSTATE) (state + 1);
	}
	void endMatch() {
		state = MATCHSTATE::END_MATCH;
	}

	// override from interface
	void RegisterObserver(Observer ob) {
		observerList.push_back(ob);
	}

	void UnregisterObserver(Observer ob) {
		/*std::vector<Observer>::iterator it = std::find(observerList.begin(), observerList.end(), ob);
		if (it != observerList.end()) {
			std::swap(*it, observerList.back());
			observerList.pop_back();
		}*/
	}

	void NotifyObservers() {
		for (auto it = observerList.begin(); it != observerList.end(); ++it) {
			(*it).Update(state, T1, T2);
		}
	}

	void DataChanged() {
		NotifyObservers();
	}
};

class ScoreDisplayBoard : public Observer {
private:
	MATCHSTATE _state;
	Team _T1, _T2;
public: 
	void Update(MATCHSTATE state, Team T1, Team T2) {
		_state = state;
		_T1 = T1; 
		_T2 = T2;
		HandleChanges();
	}

	void PrintScore() {
		std::cout << _T1.getName() << " "
			      << _T1.getGoal() << ":"
				  << _T2.getGoal() << " "
				  << _T2.getName() << "\n";
	}

	void HandleChanges() {
		switch (_state) {
		case START_MATCH:
			std::cout << "Match has started...\n";
			break;
		case FIRST_HALF:
			std::cout << "First half time...\n";
			break;
		case HALF_TIME:
			std::cout << "There are 15 mins of half_time...\n";
			break;
		case SECOND_HALF:
			std::cout << "It's second half...\n";
			break;
		case EXTRA_1:
			std::cout << "It's 1st extra time...\n";
			break;
		case EXTRA_2: break;
			std::cout << "It's 2st extra time...\n";
		case END_MATCH:
			std::cout << "Match ends...\n";
			std::cout << "Final result:\n";
			PrintScore();
			break;
		default:
			return;
		}
	}
};

class PlayerInfoBoard : public Observer {
private:
	MATCHSTATE _state;
	Team _T1, _T2;
public:
	void Update(MATCHSTATE state, Team T1, Team T2) {
		_state = state;
		_T1 = T1;
		_T2 = T2;
		HandleChanges();
	}

	void PrintNumberOfPlayer() {
		std::cout << "Number of players(" << _T1.getName() << "):" << _T1.getNumPlayer() << "\n";
		std::cout << "Number of players(" << _T2.getName() << "):" << _T2.getNumPlayer() << "\n";
	}

	void HandleChanges(){
		switch (_state) {
		case START_MATCH:
			std::cout << "Match has started...\n";
			break;
		case FIRST_HALF:
			std::cout << "First half time...\n";
			break;
		case HALF_TIME:
			std::cout << "There are 15 mins of half_time...\n";
			break;
		case SECOND_HALF:
			std::cout << "It's second half...\n";
			break;
		case EXTRA_1:
			std::cout << "It's 1st extra time...\n";
			break;
		case EXTRA_2: break;
			std::cout << "It's 2st extra time...\n";
		case END_MATCH:
			std::cout << "Match ends...\n";
			break;
		default:
			return;
		PrintNumberOfPlayer();
		}
	}
};

int main() {
	Team T1(11, 0, "Manchester United");
	Team T2(11, 0, "Liverpool");

	// create observers
	Observer *playerinfo = new PlayerInfoBoard();
	Observer *scoreboard = new ScoreDisplayBoard();

	Match match(T1, T2);
	match.RegisterObserver(playerinfo);
	match.RegisterObserver(displayboard);

	match.DataChanged();

	return 0;
}