#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// Define the structure for a song (node)
struct Song {
    string name;
    Song* next;
};

// Playlist manager structure
struct Playlist {
    Song* head;
    Song* current;

    Playlist() : head(nullptr), current(nullptr) {}

    // Add a song to the playlist
    void addSong(const string& songName) {
        Song* newSong = new Song{songName, nullptr};

        if (head == nullptr) {
            head = newSong;
            current = newSong;
        } else {
            Song* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newSong;
        }
        cout << "Added: " << songName << endl;
    }

    // Play the current song
    void playSong() {
        if (current != nullptr) {
            cout << "Now playing: " << current->name << endl;
        } else {
            cout << "No song to play." << endl;
        }
    }

    // Pause the current song
    void pauseSong() {
        if (current != nullptr) {
            cout << "Song paused: " << current->name << endl;
        } else {
            cout << "No song to pause." << endl;
        }
    }

    // Skip to the next song
    void skipSong() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
            cout << "Skipped to: " << current->name << endl;
        } else {
            cout << "No next song to skip to." << endl;
        }
    }

    // Go to the previous song
    void previousSong() {
        if (current != nullptr && current != head) {
            Song* temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            current = temp;
            cout << "Went back to: " << current->name << endl;
        } else {
            cout << "No previous song." << endl;
        }
    }

    // Display the entire playlist
    void displayPlaylist() const {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }
        Song* temp = head;
        cout << "Current Playlist:" << endl;
        while (temp != nullptr) {
            cout << "- " << temp->name << endl;
            temp = temp->next;
        }
    }

    // Show the current song being played
    void showCurrentSong() const {
        if (current != nullptr) {
            cout << "Currently playing: " << current->name << endl;
        } else {
            cout << "No song is currently playing." << endl;
        }
    }

    // Free memory used by the playlist
    ~Playlist() {
        Song* temp = head;
        while (temp != nullptr) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

// Function to safely read an integer input
int getIntegerInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid number: ";
        } else {
            return value;
        }
    }
}

// Function to safely read a string input (song name)
void getStringInput(string& input) {
    cin.ignore(); // To clear any leftover input in the buffer
    getline(cin, input);
}

// Function to validate the song name (must contain only letters, spaces, and hyphens)
bool isValidSongName(const string& songName) {
    for (char c : songName) {
        if (!isalpha(c) && c != ' ' && c != '-') {
            return false; // Invalid song name
        }
    }
    return true; // Valid song name
}

// Function to display the menu and get user input
void displayMenu() {
    cout << "\nOptions:" << endl;
    cout << "s - Pause current song" << endl;
    cout << "n - Skip to next song" << endl;
    cout << "p - Go to previous song" << endl;
    cout << "q - Quit" << endl;
    cout << "Choose an option: ";
}

// Main function to interact with the playlist
int main() {
    Playlist playlist;

    // Get the number of songs to add
    int numSongs;
    cout << "How many songs do you want to add to the playlist? ";
    numSongs = getIntegerInput();

    // Loop to add the songs
    for (int i = 0; i < numSongs; ++i) {
        string songName;

        cout << "Enter the name of song " << (i + 1) << ": ";
        getStringInput(songName);

        // Validate the song name
        while (!isValidSongName(songName)) {
            cout << "Invalid song name. Please enter a valid song name (letters, spaces, and hyphens only): ";
            getStringInput(songName);
        }

        // Add the song to the playlist
        playlist.addSong(songName);
    }

    // Display the playlist
    playlist.displayPlaylist();

    // Start playing the first song
    playlist.playSong();
    playlist.showCurrentSong();

    char userChoice;

    // Main loop to handle user commands
    while (true) {
        displayMenu();
        cin >> userChoice;

        switch (userChoice) {
            case 's': // Pause
                playlist.pauseSong();
                break;

            case 'n': // Next song
                playlist.skipSong();
                playlist.showCurrentSong();
                break;

            case 'p': // Previous song
                playlist.previousSong();
                playlist.showCurrentSong();
                break;

            case 'q': // Quit
                cout << "Exiting playlist manager." << endl;
                return 0;

            default:
                cout << "Invalid option. Please choose again." << endl;
                break;
        }
    }

    return 0;
}
