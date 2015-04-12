#include <iostream>
#include <vector>
#include <algorithm> //to erase(remove) a single object form a vector
using namespace std;
#define QUEUE_SIZE  8

typedef struct { int a, b, c; } sValues;

/***********************************************************
*			OBSERVER
************************************************************/
class Observer
{
public:
	virtual void update() = 0;
	virtual void update_values() = 0;
};

/***********************************************************
*			Subject
************************************************************/
class Subject
{
	int value_;
	int end = -1;
	sValues s_values = {};
	Observer* obs_[QUEUE_SIZE] = {};
	vector <  Observer * > vector_obs_;
public:
	void attach(Observer *obs){
		for (int i = 0; i <= QUEUE_SIZE - 1; i++){
			if (obs_[i] == 0){
				obs_[i] = obs;
				break;
			}
		}
		vector_obs_.push_back(obs);
	}
	void detach(Observer *obs){
		//for Array
		for (int i = 0; i <= QUEUE_SIZE - 1; i++){
			if (obs == obs_[i]){
				for (int j = i; j <= QUEUE_SIZE - 1; j++){
					obs_[j] = obs_[j + 1];
					if (obs_[j + 1] == 0){
						break;
					}
					else if (j == QUEUE_SIZE - 1){
						obs_[j] = 0;
					}
				}
			}
		}
		//for Vector
		vector_obs_.erase(remove(vector_obs_.begin(), vector_obs_.end(), obs), vector_obs_.end());
	}
	void set_val(int value){
		value_ = value;
		notify();
	}
	void set_values(int a, int b, int c){
		s_values.a = a;
		s_values.b = b;
		s_values.c = c;
		notify();
	}
	sValues get_values(void){
		return s_values;
	}
	int get_val(void){
		return value_;
	}
	void notify(){
		for (int i = 0; i <= QUEUE_SIZE - 1; ++i){
			if (obs_[i] != 0){
				//obs_[i]->update();
				obs_[i]->update_values();
			}
		}
		for (int i = 0; i < vector_obs_.size(); ++i){
			vector_obs_[i]->update();
			//vector_obs_[i]->update_values();
		}
	}
};

/***********************************************************
*			plusOBSERVER
************************************************************/
class PlusObserver : public Observer
{
	int i = 0, v = 0;
	sValues values;
	Subject *model_;
public:
	PlusObserver(int div){
		i = div;
	}
	void attatch(Subject *model){
		model->attach(this);
		model_ = model;
	}
	void detatch(Subject *model){
		model->detach(this);
		//model_ = model;
	}
	/* virtual */void update(){
		v = model_->get_val();
		cout << v << " plus  " << i << " is " << v + i << '\n';
	}
	/* virtual */void update_values(){
		values = model_->get_values();
		cout << values.a << " and  " << values.b << " and " << values.c << '\n';
	}
};

/***********************************************************
*			minusOBSERVER
************************************************************/
class MinusObserver : public Observer
{
	int i = 0, v = 0;
	sValues values;
	Subject *model_;
public:
	MinusObserver(int mod){
		i = mod;
	}
	void attatch(Subject *model){
		model->attach(this);
		model_ = model;
	}
	void detatch(Subject *model){
		model->detach(this);
		//model_ = model;
	}
	/* virtual */void update(){
		v = model_->get_val();
		cout << v << " minus " << i << " is " << v - i << '\n';
	}
	/* virtual */void update_values(){
		values = model_->get_values();
		cout << values.a << " and  " << values.b << " and " << values.c << '\n';
	}
};

/***********************************************************
*			MAIN
************************************************************/
int main()
{
	Subject subj;
	PlusObserver plus1(4);
	PlusObserver plus2(3);
	MinusObserver minus3(3);
	//plus1.attatch(&subj);
	//plus2.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);
	minus3.attatch(&subj);

	subj.set_val(10);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	minus3.detatch(&subj);
	subj.set_val(20);
	//subj.set_values(1, 2, 3);
	//minus3.detatch(&subj);
	//subj.set_values(4, 5, 6);
	//minus3.attatch(&subj);
	//subj.set_values(7, 8, 9);
}

