#ifndef LIVING_H
#define LIVING_H

#include <iostream>
#include <string>

class Empty;
class Grass;
class Rabbit;
class Fox;

class Living {
    public:
        void die(int i, int j, bool isEnding);
        void updateCreature();
        int getMaxAmountRabbits() const;
        int getMaxAmountFoxes() const;
    private: 
        int maxAmountRabbits;
        int maxAmountFoxes;
};

class Grass : public Living {
    public:
    Grass();
    void updateCreature();
        void grow();
        int getAge() const {return age;}
        void setAge(int newAge) {age = newAge;}             
        int getLevel() const {return level;}
        void setLevel(int input) {level = input;}    
        int getMaxLevel() const;


    private:
        int age;
        int level;
        int maxLevel;
};

class Rabbit : public Living {
    public:
    Rabbit();
    Rabbit(bool initialGender);
    void updateCreature(int i, int j);   
        int getMaxAge() const;
        int getMaxHunger() const;
        int getMinAgeMateRabbit() const;
          
        bool getGender() const {return gender;}
        void setGender(bool newGender) {gender = newGender;}
        int getHunger() const {return hunger;}
        void setHunger(int newHunger) {hunger = newHunger;}      
        int getAge() const {return age;}
        void setAge(int newAge) {age = newAge;}        
        bool getTookTurn() const {return tookTurn;}
        void setTookTurn(bool newTookTurn) {tookTurn = newTookTurn;}
        bool getHorny() const {return horny;}
        void setHorny(bool newHorny) {horny = newHorny;}
    private:
        bool tookTurn;
        bool horny;
        bool gender;
        int hunger;        
        int age;
        int maxHunger;
        int maxAge;
        int minAgeMateRabbit;
};

class Fox : public Living {
    public:
    Fox();
    Fox(bool initialGender);
    void updateCreature(int i, int j);
        int getMaxAge() const;
        int getMaxHunger() const;
        int getminAgeMateFox() const;

        bool getGender() const {return gender;}
        void setGender(bool newGender) {gender = newGender;}
        int getHunger() const {return hunger;}
        void setHunger(int newHunger) {hunger = newHunger;}      
        int getAge() const {return age;}
        void setAge(int newAge) {age = newAge;}
        bool getTookTurn() const {return tookTurn;}
        void setTookTurn(bool newTookTurn) {tookTurn = newTookTurn;}
        bool getHorny() const {return horny;}
        void setHorny(bool newHorny) {horny = newHorny;}
    private:
        bool tookTurn;
        bool horny;
        bool gender;
        int hunger;
        int age;
        int maxHunger;
        int maxAge;
        int minAgeMateFox;
};

extern Living living;
#endif
