#include <iostream>
#include <vector>
#include <algorithm> //to erase(remove) a single object form a vector
using namespace std;
#define QUEUE_SIZE  8

typedef struct { int a, b, c; } sValues;	
class Subject;

/***********************************************************
*			OBSERVER
************************************************************/
class Observer
{
public:
	virtual void update() {};
	virtual void update_values() {};
	
};
/***********************************************************
*			SUBJECT
************************************************************/
class Subject
{
private:
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
*			ValueSubject
************************************************************/
class ValueSubject : public Subject
{
	int value_;
public:
	void set_val(int value){
		value_ = value;
		notify();
	}
	int get_val(void){
		return value_;
	}
};
/***********************************************************
*			MultipleValueSubject
************************************************************/
class MultipleValueSubject : public Subject
{
	sValues s_values = {};
public:
	void set_values(int a, int b, int c){
		s_values.a = a;
		s_values.b = b;
		s_values.c = c;
		notify();
	}
	sValues get_values(void){
		return s_values;
	}
};

/***********************************************************
*			ValueOBSERVER
************************************************************/
class ValueObserver : public Observer
{
	int i = 0, v = 0;
	sValues values;
	ValueSubject *model_;
public:
	ValueObserver(int div){
		i = div;
	}
	void attatch(ValueSubject *model){
		model->attach(this);
		model_ = model;
	}
	void detatch(ValueSubject *model){
		model->detach(this);
		//model_ = model;
	}
	/* virtual */void update(){
		v = model_->get_val();
		cout << v << " plus  " << i << " is " << v + i << '\n';
	}
	
};

/***********************************************************
*			MultipleValueOBSERVER
************************************************************/
class MultipleValueObserver : public Observer
{
	int i = 0, v = 0;
	sValues values;
	MultipleValueSubject *model_;
public:
	MultipleValueObserver(int mod){
		i = mod;
	}
	void attatch(MultipleValueSubject *model){
		model->attach(this);
		model_ = model;
	}
	void detatch(MultipleValueSubject *model){
		model->detach(this);
		//model_ = model;
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
	//SUBJECTS DEFINED
	ValueSubject vSubject;
	MultipleValueSubject mSubject;

	//OBSERVERS DEFINED
	ValueObserver vObserver(3);
	MultipleValueObserver mObserver(3);

	vObserver.attatch(&vSubject);
	mObserver.attatch(&mSubject);
	
	vSubject.set_val(10);
	mSubject.set_values(1, 2, 3);

	vObserver.detatch(&vSubject);
	
	vSubject.set_val(20);
	//subj.set_values(1, 2, 3);
	//minus3.detatch(&subj);
	//subj.set_values(4, 5, 6);
	//minus3.attatch(&subj);
	//subj.set_values(7, 8, 9);
}

