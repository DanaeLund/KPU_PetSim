/* =================================================
Course: INFO 1112 S10
Last Name: Lund
First Name: Megan
Student ID: 100473249

File: project01Fall24_LundM.cpp
Summary:
A program that use the culmative teachings of my class so far.
Functions, Loops, Logical Statements, Switch Statements, Arrays, etc.
Using these components coupled with user input I have recreated a virtual pet in the styling of the tamagotchi game from the 90s.
================================================= */

//Beginning of Codebase

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

//Checks what operating system is in use for my Sleep commands
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

//Game Set Up Functions
void gameGreeting();
void printImage();
void printImageToFile(char, char, std::string, std::string);
void petNumber();
std::string petCreation();

//Global Pet Stats
bool petHealthly = true;
int age = 0;
int health = 5;
int hunger = 5;
int happiness = 5;
int cleanliness = 5;
int energy = 3;

//Pet Activities
//Function w/ Array in it (Note for KJ)
int feedPet(int, std::string);

//Function w/ Array in it (Note for KJ)
int playWithPet(int, std::string);

int cleanPet(int, std::string);
void adventure(std::string);
void sleepPet(std::string);

//Back-End Functions
void resetGame();
void clearScreen();
void customSleep(int);

//Various Game Variables
char eggSymbol = '@';
char petEyeSymbol = '@';
std::string petName = "DEFAULT NAME";
int gameColorInt;
std::string gameColourString = "White";
int numberOfPets;

std::string activeGameColor ="\033[0m";
char lineBreak = '=';
char spaceChar = ' ';
int screenwidth = 28;

std::string goodMorning = "Good morning! ";
std::string newDay = "A new day has begun. ";
std::string day = "Day ";
std::string ageString = std::to_string(age);
std::string stats = "Stats";
std::string keepPlayingResponse = "";

//Main Function
int main()
{
    bool playing = true;
    std::string gameStartAnswer = "";
    while (playing == true) {

        //Input Validation
        bool gameStartAnswerValidation = false;
        do {
            std::cout << "Welcome to the main menu!\n\n";
            std::cout << "Type \'start\' to start the game or end to cancel the game.\n";
            std::cin >> gameStartAnswer;

            if (gameStartAnswer == "Start" || gameStartAnswer == "start")
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                gameStartAnswerValidation = true;
            }
            else if (gameStartAnswer == "Cancel" || gameStartAnswer == "cancel")
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                exit(0);
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "That was not one of the options please try again.\n\n";
                gameStartAnswerValidation = false;
            }
            clearScreen();
        } while (gameStartAnswerValidation == false);
        
        //User Greeting function
        gameGreeting();

        //Print Image function
        std::cout << "This is what a pet looks like:\n\n";
        printImage();

        //Pet Hatching
        customSleep(2000);
        std::cout << "\nBut you will get to customize yours-" << std::endl;;
        customSleep(2000);
        std::cout << "\nWait.. do you hear that?" << std::endl;
        customSleep(2000);
        std::cout << "\n\t\t*crack*" << std::endl;
        customSleep(2000);
        std::cout << "\t\t\t*crack*" << std::endl;
        customSleep(2000);
        std::cout << "\t\t\t\t*crack*" << std::endl;
        customSleep(2000);
        std::cout << "\nYour egg is hatching!" << std::endl;

        //Reading Buffer
        customSleep(1000);

        //User input Number Of Pets
        petNumber();

        //Clear screen
        clearScreen();

        //MAIN GAME LOOP
        for (int i = 0; i < numberOfPets; i++)
        {
            //Pet Creation function
            std::string fileName = petCreation();

            //Set Game Color
            std::cout << activeGameColor;

            //GAME DAY LOOP
            do {
                //Set Game Color
                std::cout << activeGameColor;

                //Stats decrease by 1
                hunger -= 1;
                happiness -= 1;
                cleanliness -= 1;

                //Pet ages by 1
                age += 1;

                //Day Greeting
                clearScreen();

                std::cout << std::string((screenwidth - (day.length() + 2) / 2), lineBreak);
                std::cout << "\033[0m" << day << age << activeGameColor;
                std::cout << std::string((screenwidth - (day.length() + 2) / 2), lineBreak);
                std::cout << '\n';
                std::cout << '\n';


                std::ofstream file(fileName + ".txt", std::ios::app);
                file << '\n';
                file << std::string((screenwidth - (day.length() + 2) / 2), lineBreak);
                file << day << age;
                file << std::string((screenwidth - (day.length() + 2) / 2), lineBreak);
                file << '\n';

                file << std::string(screenwidth - ((petName.length() + 4 + 2 + 10) / 2), spaceChar);
                file << petName << " is " << age << " days old!" << std::endl;
                file << std::string(screenwidth - ((petName.length() + 4 + 2 + 10) / 2), spaceChar);
                file << '\n';
                file.close();

                std::cout << "\033[0m";
                std::cout << std::string(screenwidth - (goodMorning.length() / 2), spaceChar);
                std::cout << goodMorning;
                std::cout << std::string(screenwidth - (goodMorning.length() / 2), spaceChar);
                std::cout << '\n';

                std::cout << std::string(screenwidth - (newDay.length() / 2), spaceChar);
                std::cout << newDay;
                std::cout << std::string(screenwidth - (newDay.length() / 2), spaceChar);
                std::cout << '\n';
                std::cout << '\n';
                std::cout << activeGameColor;

                printImage();
                printImageToFile(eggSymbol, petEyeSymbol, petName, fileName);
                file.open(fileName + ".txt", std::ios::app);
                file << '\n';
                file.close();
                customSleep(2000);

                //PET ENERGY LOOP
                for (int i = 0; i < energy; i++)
                {
                    //User is presented with activity options
                    std::cout << activeGameColor;
                    std::cout << "\nWhat would you and " << petName << " like to do today? \n";
                    std::cout << "\033[0m";
                    std::cout << "\t" << "Feed " << activeGameColor << petName << "\033[0m" << " (Reply: 1)" << "\n";
                    std::cout << "\t" << "Play with " << activeGameColor << petName << "\033[0m" << " (Reply: 2)" << "\n";
                    std::cout << "\t" << "Bathe " << activeGameColor << petName << "\033[0m" << " (Reply: 3)" << "\n";
                    std::cout << "\t" << "Go on an adventure with " << activeGameColor << petName << "\033[0m" << " (Reply: 4)" << "\n";
                    std::cout << "\t" << "Put " << activeGameColor << petName << "\033[0m" << " to bed (Reply: 5)" << "\n" << activeGameColor;

                    //User makes activity choice
                    bool activityChoiceValidation = false;
                    int activityChoice;
                    do {
                        std::cout << "\nActivity choice: ";
                        std::cout << "\033[0m";
                        std::cin >> activityChoice;
                        std::cout << activeGameColor;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cout << "\nInvalid answer, please input a number between 1 and 5.\n";
                            activityChoiceValidation = false;
                        }
                        else if (activityChoice < 1 || activityChoice > 5) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cout << "\nInvalid answer, please input a number between 1 and 5.\n";
                            activityChoiceValidation = false;
                        }
                        else {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            activityChoiceValidation = true;
                        }
                    } while (activityChoiceValidation == false);

                    switch (activityChoice)
                    {
                    case 1:
                        hunger = feedPet(hunger, fileName);
                        break;
                    case 2:
                        happiness = playWithPet(happiness, fileName);
                        break;
                    case 3:
                        cleanliness = cleanPet(cleanliness, fileName);
                        break;
                    case 4:
                        adventure(fileName);
                        break;
                    case 5:
                        sleepPet(fileName);
                        i = 3;
                        break;
                    default:
                        break;
                    }
                    customSleep(2000);
                }

                std::cout << "\nYour pet is out of energy and is tired.\nYou can play more tomorrow.\n";
                customSleep(2000);

                //Change health depending on end-of-day stats
                if (hunger <= 0)
                {
                    health -= 1;
                }

                if (happiness <= 0)
                {
                    health -= 1;
                }

                if (cleanliness <= 0)
                {
                    health -= 1;
                }

                //Ensuring Stats are within range
                if (hunger < 0) {
                    hunger = 0;
                }
                else if (hunger > 5) {
                    hunger = 5;
                }

                if (happiness < 0) {
                    happiness = 0;
                }
                else if (happiness > 5) {
                    happiness = 5;
                }

                if (cleanliness < 0) {
                    cleanliness = 0;
                }
                else if (cleanliness > 5) {
                    cleanliness = 5;
                }

                if (health <= 0)
                {
                    health = 0;
                    petHealthly = false;

                    //Death Message
                    std::cout << "\033[0m";
                    std::cout << '\n' << petName << " has died in their sleep.\n";
                    std::cout << "You let your pet die, this is why I gave you a game and not a pet." << '\n';
                    std::cout << "Make sure to check your file folder for your diary entry." << '\n';

                    file.open(fileName + ".txt", std::ios::app);
                    file << '\n' << petName << " has died in their sleep.\n";
                    file << "You let your pet die, this is why I gave you a game and not a pet." << '\n';
                    file << "Make sure to check your file folder for your diary entry." << '\n';
                    file.close();
                }
                else if (health > 5) {
                    health = 5;
                }
                
                //Output to console
                std::cout << '\n';
                std::cout << activeGameColor;
                std::cout << std::string((screenwidth - (stats.length() / 2)), lineBreak);
                std::cout << "\033[0m" << stats << activeGameColor;
                std::cout << std::string((screenwidth - (stats.length() / 2)), lineBreak);
                std::cout << '\n';

                std::cout << "\nHealth: " << "\033[0m" << health << " out of 5" << activeGameColor << '\n';
                std::cout << "Hunger: " << "\033[0m" << hunger << " out of 5" << activeGameColor << '\n';
                std::cout << "Happiness: " << "\033[0m" << happiness << " out of 5" << activeGameColor << '\n';
                std::cout << "Cleanliness: " << "\033[0m" << cleanliness << " out of 5" << activeGameColor << '\n';

                //Output to file
                file.open(fileName + ".txt", std::ios::app);
                file << '\n';
                file << std::string((screenwidth - (stats.length() / 2)), lineBreak);
                file << stats;
                file << std::string((screenwidth - (stats.length() / 2)), lineBreak);
                file << '\n';

                file << "\nHealth: " << health << " out of 5" << '\n';
                file << "Hunger: " << hunger << " out of 5" << '\n';
                file << "Happiness: " << happiness << " out of 5" << '\n';
                file << "Cleanliness: " << cleanliness << " out of 5" << '\n';
                file.close();

                customSleep(2000);
                

                if (petHealthly == true)
                {
                    std::cout << "\033[0m" << "\nWould you like to return to the main menu (Reply: \"return\")? Otherwise press any key to continue: " << activeGameColor << std::endl;
                    std::cout << "\033[0m";
                    std::cin >> keepPlayingResponse;

                    if (keepPlayingResponse == "Return" || keepPlayingResponse == "return")
                    {
                        file.open(fileName + ".txt", std::ios::app);
                        file << "\nGame was ended early by the player." << std::endl;
                        file.close();
                        resetGame();
                        clearScreen();
                        break;
                    }
                    else
                    {
                        continue;
                        clearScreen();
                    }
                }

            } while (petHealthly);

            std::cout << "\nWould you like to return to the main menu (Reply: \"return\")? Otherwise press any key to continue on to your next pet: " <<  std::endl;
            std::cin >> keepPlayingResponse;

            if (keepPlayingResponse == "Return" || keepPlayingResponse == "return")
            {
                resetGame();
                clearScreen();
                break;
            }
            else
            {
                resetGame();
                clearScreen();
                continue;
            }

        }

    }
    return(0);
}

//FUNCTIONS
void gameGreeting() {
    //User greeting
    std::cout << "Hello, welcome to KPU Pet Simulator!\n";
    customSleep(2000);
    std::cout << "\nWe know you are too busy to take care of a real pet.\nSo we made a game for you to try!\n";
    customSleep(2000);

    //Game Instructions (function)
    std::cout << "\nHow to play the game: \n";
    std::cout << "\t1. Choose how many pets to take care of (1 - 3, max of 3.)\n";
    std::cout << "\t2. Name your first pet.\n";
    std::cout << "\t3. Choose the symbol for your pet\'s eyes\n";
    std::cout << "\t4. Choose the symbol to make up your egg.\n";
    std::cout << "\t5. Choose the color you want the game to be.\n";
    std::cout << "\t6. Each day you can perform 3 actions to take care of your pet.\n";

    customSleep(2000);

    //Game Tip
    std::cout << "\nNOTE: If your pet's health falls to 0 your pet will die and you will move on to your next pet.\n";
    std::cout << "If you want a token to remember your pet by, there will be a text file you can keep at the end with your pet\'s name + _diary as the file name.\nIt is a diary of all the activites you and your pet completed together.\n";

    customSleep(5000);

    std::cout << '\n';
    system("pause");
    clearScreen();
}

void printImage() {
    //Show Unchanged Image (function)
    int lineNumber = 1;
    int lineMax = 28;
    int eggString = 16;
    int petImageWidth = 10;

    std::cout << activeGameColor;

    std::string spaceString = "";

    for (int i = lineNumber; i < 30; i++)
    {
        //Top of Egg
        if (lineNumber <= 4) {
            eggString += 4;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            std::cout << spaceString;
            std::cout << std::string(eggString, eggSymbol);
            std::cout << spaceString;
            std::cout << std::endl;
        }
        //Top of Egg 2
        else if (lineNumber > 4 && lineNumber <= 9) {
            eggString += 2;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            std::cout << spaceString;
            std::cout << std::string(eggString, eggSymbol);
            std::cout << spaceString;
            std::cout << std::endl;
        }
        //Top of Screen
        else if (lineNumber > 9 && lineNumber <= 12) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            if (lineNumber == 11)
            {
                if (petName.length() % 2 == 1)
                {
                    std::cout << spaceString;
                    std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    std::cout << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    std::cout << petName;
                    std::cout << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    std::cout << " ";
                    std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    std::cout << spaceString;
                    std::cout << std::endl;
                }
                else {
                    std::cout << spaceString;
                    std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    std::cout << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    std::cout << petName;
                    std::cout << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    std::cout << spaceString;
                    std::cout << std::endl;
                }
            }

            std::cout << spaceString;
            std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
            std::cout << std::string(screenwidth, spaceChar);
            std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
            std::cout << spaceString << std::endl;
        }

        //Pet Image
        else if (lineNumber > 12 && lineNumber <= 18) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            //Use a switch statement to print the right pet line
            switch (lineNumber)
            {
            case 13:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << " -------- ";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            case 14:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << "/        \\";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            case 15:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << "| " << petEyeSymbol << "    " << petEyeSymbol << " |";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            case 16:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << "|        |";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            case 17:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << "\\   \\/   /";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            case 18:
                std::cout << spaceString;
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << " -------- ";
                std::cout << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
                std::cout << spaceString;
                std::cout << std::endl;
                break;
            default:
                break;
            }
        }
        //Bottom of Screen
        else if (lineNumber > 18 && lineNumber <= 21) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            std::cout << spaceString;
            std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
            std::cout << std::string(screenwidth, spaceChar);
            std::cout << std::string(((eggString - screenwidth) / 2), eggSymbol);
            std::cout << spaceString;
            std::cout << std::endl;
        }
        //Bottom of Egg
        else if (lineNumber > 21 && lineNumber <= 25) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            std::cout << spaceString;
            std::cout << std::string(eggString, eggSymbol);
            std::cout << spaceString;
            std::cout << std::endl;
        }
        //Bottom of Egg 2
        else if (lineNumber > 25 && lineNumber <= 30) {
            eggString -= 4;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            std::cout << spaceString;
            std::cout << std::string(eggString, eggSymbol);
            std::cout << spaceString;
            std::cout << std::endl;
        }
        else {
            //Error handling
            std::cout << "Error! Something is wrong! \n" << lineNumber << '\n';
        }

        lineNumber++;
    }
}

void printImageToFile(char eggSymbol, char petEyeSymbol, std::string petName, std::string fileName) {
    //Show Unchanged Image (function)
    int lineNumber = 1;
    int lineMax = 28;
    int eggString = 16;
    int petImageWidth = 10;

    std::string spaceString = "";
    std::ofstream file(fileName + ".txt", std::ios::app);

    for (int i = lineNumber; i < 30; i++)
    {
        //Top of Egg
        if (i > 0 && i <= 4) {
            eggString += 4;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(eggString, eggSymbol);
            file << spaceString;
            file << std::endl;
            file.close();
        }
        //Top of Egg 2
        else if (i > 4 && i <= 9) {
            eggString += 2;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(eggString, eggSymbol);
            file << spaceString;
            file << std::endl;
            file.close();
        }
        //Top of Screen
        else if (i > 9 && i <= 12) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            if (i == 11)
            {
                if (petName.length() % 2 == 1)
                {
                    file.open(fileName + ".txt", std::ios::app);
                    file << spaceString;
                    file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    file << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    file << petName;
                    file << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    file << " ";
                    file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    file << spaceString;
                    file << std::endl;
                    file.close();
                }
                else {
                    file.open(fileName + ".txt", std::ios::app);
                    file << spaceString;
                    file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    file << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    file << petName;
                    file << std::string((screenwidth - petName.length()) / 2, spaceChar);
                    file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                    file << spaceString;
                    file << std::endl;
                    file.close();
                }
            }

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(((eggString - screenwidth) / 2), eggSymbol);
            file << std::string(screenwidth, spaceChar);
            file << std::string(((eggString - screenwidth) / 2), eggSymbol);
            file << spaceString << std::endl;
            file.close();
        }

        //Pet Image
        else if (i > 12 && i <= 18) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            //Use a switch statement to print the right pet line
            switch (i)
            {
            case 13:
            {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << " -------- ";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
            }
            case 14:
            {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << "/        \\";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
            }
            case 15:
            {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << "| " << petEyeSymbol << "    " << petEyeSymbol << " |";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
            }
            case 16:
            {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << "|        |";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
            }
            case 17:
            {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << "\\   \\/   /";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
             }
            case 18: {
                file.open(fileName + ".txt", std::ios::app);
                file << spaceString;
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << " -------- ";
                file << std::string((screenwidth - petImageWidth) / 2, spaceChar);
                file << std::string(((eggString - screenwidth) / 2), eggSymbol);
                file << spaceString;
                file << std::endl;
                file.close();
                break;
            }
            default:
                break;
            }
        }
        //Bottom of Screen
        else if (i > 18 && i <= 21) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(((eggString - screenwidth) / 2), eggSymbol);
            file << std::string(screenwidth, spaceChar);
            file << std::string(((eggString - screenwidth) / 2), eggSymbol);
            file << spaceString;
            file << std::endl;
            file.close();
        }
        //Bottom of Egg
        else if (i > 21 && i <= 25) {
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(eggString, eggSymbol);
            file << spaceString;
            file << std::endl;
            file.close();
        }
        //Bottom of Egg 2
        else if (i > 25 && i <= 30) {
            eggString -= 4;
            spaceString = std::string((lineMax - eggString / 2), spaceChar);

            file.open(fileName + ".txt", std::ios::app);
            file << spaceString;
            file << std::string(eggString, eggSymbol);
            file << spaceString;
            file << std::endl;
            file.close();
        }
        else {
            //Error handling
            std::cout << "Error! Something is wrong on line \n" << i << '\n';
        }
    }
}

void petNumber() {
    std::cout << "\nHow many pets would you like? (maximum of 3): ";
    std::cin >> numberOfPets;

    while (numberOfPets != 1 && numberOfPets != 2 && numberOfPets != 3) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "\nInvalid answer, please input a number between 1 and 3.\n";
            std::cout << "\nHow many pets would you like? (maximum of 3): ";
        }
        else if (numberOfPets < 1 || numberOfPets > 3) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "\nInvalid answer, please input a number between 1 and 3.\n";
            std::cout << "\nHow many pets would you like? (maximum of 3): ";
        }

        std::cin >> numberOfPets;
    }
}

std::string petCreation() {
    int petCustomizerChoice;
    
    //Pet is "hatched"
    std::cout << "Pet has hatched!" << std::endl;
    std::cout << "\n";
    printImage();

    //User Pet customizer menu
    bool petCustomizerFinished = false;
    do
    {
        //Pet Customizer Choice Validation
        bool petCustomizerChoiceValidation = false;
        do {
            std::cout << activeGameColor;

            std::cout << "\nWhat would you like to customize on your pet?:\n";
            std::cout << "\tName (" << petName << ") (Reply: 1)\n";
            std::cout << "\tPet\'s Eye Symbol (" << petEyeSymbol << ") (Reply: 2)\n";
            std::cout << "\tPet\'s Egg\'s Symbol (" << eggSymbol << ") (Reply: 3)\n";
            std::cout << "\tGame Colour (" << gameColourString << ") (Reply: 4)\n";
            std::cout << "\tNothing (Reply: 5)\n";
            std::cin >> petCustomizerChoice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\nInvalid answer, please input a number between 1 and 5.\n";
                petCustomizerChoiceValidation = false;
            }
            else if (petCustomizerChoice < 1 || petCustomizerChoice > 5) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "\nInvalid answer, please input a number between 1 and 5.\n";
                petCustomizerChoiceValidation = false;
            }
            else {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                petCustomizerChoiceValidation = true;
            }
        } while (petCustomizerChoiceValidation == false);


        switch (petCustomizerChoice)
        {
        case 1:
        {
            //User names their pet
            std::cout << "\nWhat would you like to name your pet?: ";
            std::cin >> petName;
            std::cout << "Pet has been named: " << petName << std::endl;
            customSleep(2000);
            clearScreen();
            break;
        }
        case 2:
        {
            //User customizes pet's eyes 
            bool petEyeValidation = false;
            do {
                std::cout << "Please choose a symbol to use as your pet\'s eyes: ";
                std::cin >> petEyeSymbol;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "\nInvalid answer, please input a single character.\n";
                    petEyeValidation = false;
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "\nChosen eye symbol is: " << petEyeSymbol << "\n";
                    petEyeValidation = true;
                    customSleep(2000);
                    clearScreen();
                }
            } while (petEyeValidation == false);
            break;
        }
        case 3:
        {
            //User customizes pet's egg
            bool eggSymbolValidation = false;
            do {
                std::cout << "Please choose a symbol to use as your pet\'s egg: ";
                std::cin >> eggSymbol;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    eggSymbolValidation = false;
                    std::cout << "\nInvalid answer, please input a single character.\n";
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    eggSymbolValidation = true;
                    std::cout << "\nChosen egg symbol is: " << eggSymbol << "\n";
                    customSleep(2000);
                    clearScreen();
                }
            } while (eggSymbolValidation == false);
            break;
        }
        case 4:
        {
            //User customizes game color

            std::cout << "Game Colors:" << '\n';
            std::cout << "\t\033[31;1mRed\033[0m" << " (Reply: 1)" << '\n';
            std::cout << "\t\033[32;1mGreen\033[0m" << " (Reply: 2)" << '\n';
            std::cout << "\t\033[33;1mYellow\033[0m" << " (Reply: 3)" << '\n';
            std::cout << "\t\033[35;1mPurple\033[0m" << " (Reply: 4)" << '\n';

            bool gameColorValidation = false;
            do {
                std::cout << activeGameColor;
                std::cout << "\nPlease choose the color you would like your game text: ";
                std::cout << "\033[0m";
                std::cin >> gameColorInt;
                std::cout << activeGameColor;

                if (std::cin.fail()) {
                    std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    gameColorValidation = false;
                }
                else if (gameColorInt < 1 || gameColorInt >4) {
                    std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    gameColorValidation = false;
                }
                else {
                    gameColorValidation = true;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                }
            } while (gameColorValidation == false);

            switch (gameColorInt)
            {
            case 1:
                activeGameColor = "\033[31;1m";
                gameColourString = "Red";
                std::cout << "\nChosen game colour is: " << gameColourString << "\n";
                break;
            case 2:
                activeGameColor = "\033[32;1m";
                gameColourString = "Green";
                std::cout << "\nChosen game colour is: " << gameColourString << "\n";
                break;
            case 3:
                activeGameColor = "\033[33;1m";
                gameColourString = "Yellow";
                std::cout << "\nChosen game colour is: " << gameColourString << "\n";
                break;
            case 4:
                activeGameColor = "\033[35;1m";
                gameColourString = "Purple";
                std::cout << "\nChosen game colour is: " << gameColourString << "\n";
                break;
            default:
                break;
            }

            customSleep(2000);
            clearScreen();
            break;
        }
        case 5:
            std::cout << "\nNo more changes will be made.\n";
            petCustomizerFinished = true;
            clearScreen();
            break;
        default:
            break;
        }
        std::cout << "\n";
        printImage();
    } while (petCustomizerFinished == false);


    //Create and open the text file
    std::string fileName = petName + "_diary";

    //Output to file
    std::ofstream file(fileName + ".txt");
    file << "Welcome to KPU Pet Simulator!" << std::endl;
    file.close();

    printImageToFile('@', '@', "DEFAULT NAME", fileName);

    file.open(fileName + ".txt", std::ios::app);
    file << "Pet has hatched!" << std::endl;
    file << "Pet has been named: " << petName << std::endl;

    file << petName << " has " << petEyeSymbol << " eyes." << std::endl;

    file << petName << " has a " << eggSymbol << " shell." << std::endl;
    file.close();

    switch (gameColorInt)
    {
    case 1:
        //OUTPUT TO FILE
        file << "The game color is: Red" << std::endl;
        break;
    case 2:
        //OUTPUT TO FILE
        file << "The game color is: Green" << std::endl;
        break;
    case 3:
        //OUTPUT TO FILE
        file << "The game color is: Yellow" << std::endl;
        break;
    case 4:
        //OUTPUT TO FILE
        file << "The game color is: Purple" << std::endl;
        break;
    default:
        break;
    }

    printImageToFile(eggSymbol, petEyeSymbol, petName, fileName);
    file << std::endl;
    file.close();
    
    //End of function
    return(fileName);
}

//Function w/ Array in it (Note for KJ)
int feedPet(int hunger, std::string fileName) {
    std::string foods[] = {"Apple", "Burger", "Cookie", "Juice", "a ", "an "};
    int foodChoice;
    std::string foodChoiceString;
    std::ofstream file(fileName + ".txt", std::ios::app);

    std::cout << "\nOn the menu today is:\n";
    std::cout << "\033[0m";
    std::cout << "\t" << foods[0] << " (Reply: 1)\n";
    std::cout << "\t" << foods[1] << " (Reply: 2)\n";
    std::cout << "\t" << foods[2] << " (Reply: 3)\n";
    std::cout << "\t" << foods[3] << " (Reply: 4)\n";

    bool foodChoiceValidation = false;
    do {
        std::cout << activeGameColor;
        std::cout << "\nWhat would you like to feed " << petName << "?: ";
        std::cout << "\033[0m";
        std::cin >> foodChoice;
        std::cout << activeGameColor;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            foodChoiceValidation = false;
            std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
        }
        else if (foodChoice < 1 || foodChoice > 4) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            foodChoiceValidation = false;
            std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
        }
        else {
            foodChoiceValidation = true;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    } while (foodChoiceValidation == false);

    switch (foodChoice)
    {
    case 1:
        foodChoiceString = foods[5] + foods[0];
        break;
    case 2:
        foodChoiceString = foods[4] + foods[1];
        break;
    case 3:
        foodChoiceString = foods[4] + foods[2];
        break;
    case 4:
        foodChoiceString = foods[4] + foods[3];
        break;
    default:
        break;
    }

    //Output to Console
    std::cout << "\033[0m";
    std::cout << "\nYou fed " << petName << " " << foodChoiceString << ".\n";
    std::cout << activeGameColor;

    //OUTPUT TO FILE
    file << petName << " has eaten " << foodChoiceString << " and gained back 1 point of hunger." << std::endl;

    hunger++;
    file.close();
    return(hunger);
}

//Function w/ Array in it (Note for KJ)
int playWithPet(int happiness, std::string fileName) {
    std::string games[] = { "Ball for Fetch", "Rope for Tug-of-War", "Frisbe for Catch", "Laser Pointer for Chase" };
    int gameChoice;
    std::string gameChoiceString;
    std::ofstream file(fileName + ".txt", std::ios::app);

    std::cout << "\nToys of the day are:\n";
    std::cout << "\033[0m";
    std::cout << "\t" << games[0] << " (Reply: 1)\n";
    std::cout << "\t" << games[1] << " (Reply: 2)\n";
    std::cout << "\t" << games[2] << " (Reply: 3)\n";
    std::cout << "\t" << games[3] << " (Reply: 4)\n";

    bool gameChoiceValidation = false;
    do {
        std::cout << activeGameColor;
        std::cout << "\nWhat would you like to play with, with " << petName << "?: ";
        std::cout << "\033[0m";
        std::cin >> gameChoice;
        std::cout << activeGameColor;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            gameChoiceValidation = false;
            std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
        }
        else if (gameChoice < 1 || gameChoice > 4) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            gameChoiceValidation = false;
            std::cout << "\nInvalid answer, please input a number between 1 and 4.\n";
        }
        else {
            gameChoiceValidation = true;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    } while (gameChoiceValidation == false);

    switch (gameChoice)
    {
    case 1:
        gameChoiceString = games[0];
        break;
    case 2:
        gameChoiceString = games[1];
        break;
    case 3:
        gameChoiceString = games[2];
        break;
    case 4:
        gameChoiceString = games[3];
        break;
    default:
        break;
    }

    //Output to Console
    std::cout << "\033[0m";
    std::cout << "\nYou played with a " << gameChoiceString << " with " << petName << "\n";
    std::cout << activeGameColor;

    //OUTPUT TO FILE
    file << petName << " has played " << gameChoiceString << " and gained back 1 point of happiness." << std::endl;

    happiness++;
    file.close();
    return(happiness);
}

int cleanPet(int cleanliness, std::string fileName) {
    //Output to Console
    std::cout << "\033[0m";
    std::cout << "\nYou catch " << petName << " and wrestle them into the tub.\n" << petName << " is now clean.\n";
    std::cout << activeGameColor;
    std::ofstream file(fileName + ".txt", std::ios::app);

    //OUTPUT TO FILE
    file << petName << " has been bathed and gained back 1 point of cleanliness." << std::endl;

    ++cleanliness;
    file.close();
    return(cleanliness);
}

void adventure(std::string fileName) {
    srand((int)time(0));
    int r = (rand() % 20);
    std::ofstream file(fileName + ".txt", std::ios::app);

    customSleep(2000);

    std::cout << "\033[0m" << "\n";
    switch (r)
    {
    case 0:
        std::cout << "A kind passerby gives " << petName << " a belly rub, increasing Happiness by 1." << "\n";
        file << "A kind passerby gives " << petName << " a belly rub, increasing Happiness by 1." << std::endl;
        ++happiness;
        break;
    case 1:
        std::cout << petName << " finds a delicious treat on the ground and eats it, increasing Hunger by 1." << "\n";
        file << petName << " finds a delicious treat on the ground and eats it, increasing Hunger by 1." << std::endl;
        ++hunger;
        break;
    case 2:
        std::cout << "A sudden rainstorm leaves " << petName << " soaked, decreasing Cleanliness by 1." << "\n";
        file << "A sudden rainstorm leaves " << petName << " soaked, decreasing Cleanliness by 1." << std::endl;
        --cleanliness;
        break;
    case 3:
        std::cout << "While walking, " << petName << " meets a friendly dog, and they play together, increasing Happiness by 1." << "\n";
        file << "While walking, " << petName << " meets a friendly dog, and they play together, increasing Happiness by 1." << std::endl;
        ++happiness;
        break;
    case 4:
        std::cout << petName << " runs through a patch of mud, decreasing Cleanliness by 1." << "\n";
        file << petName << " runs through a patch of mud, decreasing Cleanliness by 1." << std::endl;
        --cleanliness;
        break;
    case 5:
        std::cout << "You find a sunny spot in the park and relax with your pet, increasing Happiness by 1." << "\n";
        file << "You find a sunny spot in the park and relax with your pet, increasing Happiness by 1." << std::endl;
        ++happiness;
        break;
    case 6:
        std::cout << petName << " accidentally steps on a thorn and yelps, decreasing Health by 1." << "\n";
        file << petName << " accidentally steps on a thorn and yelps, decreasing Health by 1." << std::endl;
        --health;
        break;
    case 7:
        std::cout << petName << " chases after a squirrel and trips, decreasing Health by 1." << "\n";
        file << petName << " chases after a squirrel and trips, decreasing Health by 1." << std::endl;
        --health;
        break;
    case 8:
        std::cout << "You and " << petName << " come across a vendor giving away free sample of hotdogs, increasing Hunger by 1." << "\n";
        file << "You and " << petName << " come across a vendor giving away free sample of hotdogs, increasing Hunger by 1." << std::endl;
        ++hunger;
        break;
    case 9:
        std::cout << "After a long walk, " << petName << " lies down to rest, increasing Happiness by 1." << "\n";
        file << "After a long walk, " << petName << " lies down to rest, increasing Happiness by 1." << std::endl;
        ++happiness;
        break;
    case 10:
        std::cout << petName << " spots a mud puddle and jumps in it, decreasing Cleanliness by 1." << "\n";
        file << petName << " spots a mud puddle and jumps in it, decreasing Cleanliness by 1." << std::endl;
        --cleanliness;
        break;
    case 11:
        std::cout << "You visit the park, and " << petName << " makes new friends, increasing Happiness by 1." << "\n";
        file << "You visit the park, and " << petName << " makes new friends, increasing Happiness by 1." << std::endl;
        ++happiness;
        break;
    case 12:
        std::cout << "A passing cyclist scares " << petName << ", decreasing Happiness by 1." << "\n";
        file << "A passing cyclist scares " << petName << ", decreasing Happiness by 1." << std::endl;
        --happiness;
        break;
    case 13:
        std::cout << petName << " rolls in some rotten garbage, decreasing Cleanliness by 1." << "\n";
        file << petName << " rolls in some rotten garbage, decreasing Cleanliness by 1." << std::endl;
        --cleanliness;
        break;
    case 14:
        std::cout << "You stop for a picnic, and " << petName << " sneaks some food, decreasing Hunger by 1." << "\n";
        file << "You stop for a picnic, and " << petName << " sneaks some food, decreasing Hunger by 1." << std::endl;
        ++hunger;
        break;
    case 15:
        std::cout << petName << " gets scared by some kids palying with fireworks, decreasing Happiness by 1." << "\n";
        file << petName << " gets scared by some kids palying with fireworks, decreasing Happiness by 1." << std::endl;
        --happiness;
        break;
    case 16:
        std::cout << petName << " drinks from a questionable puddle, decreasing Health by 1." << "\n";
        file << petName << " drinks from a questionable puddle, decreasing Health by 1." << std::endl;
        --health;
        break;
    case 17:
        std::cout << "You spend time training " << petName << " during the walk, increasing Happiness by 1." << "\n";
        file << "You spend time training " << petName << " during the walk, increasing Happiness by 1." << std::endl;
        --happiness;
        break;
    case 18:
        std::cout << petName << " finds a clean stream to splash in, increasing Cleanliness by 1." << "\n";
        file << petName << " finds a clean stream to splash in, increasing Cleanliness by 1." << std::endl;
        --cleanliness;
        break;
    case 19:
        std::cout << "While playing fetch, " << petName << " sprains a paw, decreasing Health by 1." << "\n";
        file << "While playing fetch, " << petName << " sprains a paw, decreasing Health by 1." << std::endl;
        --health;
        break;
    default:
        std::cout << "You shouldn't see me... Please contact the developer." << "\n";
        break;
    }
    file.close();
    customSleep(2000);
    std::cout << activeGameColor;
}

void sleepPet(std::string fileName) {
    //Output to Console
    std::cout << "\033[0m";
    std::cout << "\nYou put " << petName << " to bed and end your day early.\n";
    std::cout << activeGameColor;
    std::ofstream file(fileName + ".txt", std::ios::app);

    //OUTPUT TO FILE
    file << petName << " has been put to bed early." << std::endl;

    file.close();
}

void resetGame() {
    petHealthly = true; 
    petName = "DEFAULT NAME";
    age = 0;
    health = 5;
    hunger = 5;
    happiness = 5;
    cleanliness = 5;
    energy = 3;

    eggSymbol = '@';
    petEyeSymbol = '@';
    gameColorInt = 0;
    gameColourString = "White";
    activeGameColor = "\033[0m";
}

void clearScreen() {
    //Clears terminal to keep things clean
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

void customSleep(int timeInMilliSeconds) {
    #ifdef _WIN32
        Sleep(timeInMilliSeconds);
    #else
        //microseconds
        usleep(timeInMilliSeconds*1000);
    #endif
}