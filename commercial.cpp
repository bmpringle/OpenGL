#include<stdio.h> 
#include<iostream>
#include<cstdlib>

void print(std::string print) {
    std::cout << print << std::endl;
}

std::string input() {
    std::string input;
    std::cin >> input;
    return input;
}

std::string askPlayer() {
    print("Hey, nerd! You're here now. What do you want to do? \n 1. Eat \n 2. Sleep \n 3. Go do something productive \n 4. buy toilet paper (costs 20 coins per roll) \n 5. check bal \n 6. help");
    std::string in = input();

    if(in != "1" && in != "2" && in != "3" && in != "4" && in != "5" && in != "6") {
        print("Please enter 1, 2, 3, 4, 5, or 6.");
        return askPlayer();
    }
    return in;
}

int coins = 120;

int tpJoke() {
    std::string in = input();

    if(in != "1" && in != "2" && in != "3" && in != "4" && in != "5" && in != "6") {
        print("Please enter 1, 2, 3, 4, 5, or 6. You can't buy any more than 6, cuz you're broke and toilet paper is EXPENSIVE.");
        return tpJoke();
    }
    if(std::stoi(in)*20 > coins) {
        print("You're too broke to buy that much! How about a bit less, greedy?");
        return tpJoke();
    }
    return std::stoi(in);
}

void mainInputHandle(std::string action) {
    int amnt = 0;
    switch(std::stoi(action)) {
        case 1:
            print("You eat a whole buffet. You pig.");
        break;
        case 2:
            print("You just woke up. Lazy.");
        break;
        case 3:
            print("Productive? I didn't know you even knew what that meant. But fine, what do you want to do?");
            
            print("You want to do " + input() + "? But that would require you to have some sort of talent!");
        break;
        case 4:
            if(coins == 0) {
                print("You are literaly broke. You have no money. Do you think they hand out toilet paper for free?");
                break;
            }
            print("How much?");
            amnt = tpJoke();
            print("You buy " + std::to_string(amnt) + " roll(s) of toilet paper. It ran you " + std::to_string(amnt*20) + " coins. Are you done wasting your money like a fool now?");
            coins = coins - amnt*20;
        break;
        case 5: 
            print("You have " + std::to_string(coins) + " coins. What are you spending your paycheck on?");
        break;
        case 6: 
            print("no.");
        break;
    }
}

int main() {
    bool playing = true;

    while(playing) {
        std::string playerAction = askPlayer();
        mainInputHandle(playerAction);
    }
    return 0;
}