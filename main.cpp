#include <iostream>
#include <string>
#include <vector> //library import
#include <ctype.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void importSpotifyPlaylist(vector<string>& Songs) { //imports spotify playlist
    int result = system("python main.py"); //runs python script
    if (result != 0) {
        std::cerr << "Error running the Python script" << std::endl; //checks
        return;
    }

    std::ifstream file("track_list.txt"); //reads txt file created by .py file
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl; //checks
        return;
    }

    std::string line; //txtline creation

    while (std::getline(file, line)) {
        Songs.push_back(line); //adds each line to the Passed vector
    }

    file.close();

}

int main() {
  vector<string> Songs{"Last Christmas", "Deck the Halls", "Carol of the Bells", "Jingle Bells", "Feliz Navidad"};
  while (true) {
    cout << (char) 27 << "[32m" <<  "Menu: \n "; //menu w/ options
    cout << (char) 27 << "[37m" << "\t1) Select Song ";
    cout << "\n\t2) Add song ";
    cout << "\n\t3) Play songs  ";
    cout << "\n\t4) Import Spotify Playlist";
    cout << "\n\t5) Exit Menu ";
    cout << (char) 27 << "[32m" << "\n\nChoice: "; 

    string menuchoice, song, queue, select;
    getline(cin, menuchoice);
    int choice;
    if (isdigit(menuchoice[0])) { //menu response
      choice = menuchoice[0] - '0';

      switch (choice) {
      case 1: //#1
        cout << (char) 27 << "[32m" << "Select song: \n";
        for (int i = 0; i < Songs.size(); i++) {
          cout << (char) 27 << "[37m"  << i+1 << ": " << Songs[i] << endl; //prints songs
        }
        cout << "Choice: "; //choice receive
        getline(cin, select);
        if (isdigit(select[0])) {
          if (stoi(select) <= Songs.size()) { 
            cout << "Playing " << Songs[stoi(select)-1] << endl; //play
          } else {
            cout << "Did not enter valid answer, going back to menu..." << endl; //traps
          }
        } else {
          cout << "Did not enter valid answer, going back to menu..." << endl;
        }
      break;

      case 2:
        cout << (char) 27 << "[32m" << "Add song: "; //add song input
        cout << (char) 27 << "[37m" << "\nEnter song name: ";
        getline(cin, song);
        Songs.push_back(song); //add song to list
        break;

      case 3:
        cout << (char) 27 << "[32m" << "\n Play Songs: ";
        cout << (char) 27 << "[37m" << "\n\tQueue Type: ";
        cout << "\n\t\t1. Ordered: "; //ordered songs menu
        cout << "\n\t\t2. Shuffled: \nChoice: ";
        getline(cin, queue);
        if (stoi(queue) == 1) {
          // ordered
          cout << "\nSongs: \n";
          for (int i = 0; i < Songs.size(); i++) {
            cout << "\nSong # " << i+1 << ": " << Songs[i]; //print songs in order
          }
          cout << "\n";
        }
        else {
          // shuffled
          int numofsongs = Songs.size();
          vector<bool> printed(numofsongs, false);
          for(int i = 0; i != numofsongs; i++){ 
            int randnum;
            do {
              randnum = rand() % Songs.size(); //new random num 
            } while(printed[randnum]); // check if the song at the generated index has already been printed
            printed[randnum] = true; // mark the song as printed
            cout << "#" << i+1 << ": "<< Songs[randnum]<<endl; //prints songs in random order
          }
        }
        break;

      case 4:
        importSpotifyPlaylist(Songs); //calls above function
        break;
        
      case 5:
        cout << (char) 27 << "[95m" <<  "Thank you for using our playlist simulator!"; //ends program
        exit(0);
        break;
      default:
        cout << "Invalid choice. Enter a number present in the menu (1-4)\n"; //trap
        break;
      }
    } else {
      cout << "Please enter a valid choice." << endl; //trap
    }
  }
}
