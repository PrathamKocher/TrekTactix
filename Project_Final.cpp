#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Location {
    string name;
    double rating;
    double cost;
    int hours;

    Location() {}

    Location(const string& name, double rating, double cost, int hours)
        : name(name), rating(rating), cost(cost), hours(hours) {}
};

bool issafe(vector<vector<int> >& v, int row, int col, int i, int j, vector<vector<bool> >& copyvector) {
    if (i >= 0 && i < row && j >= 0 && j < col && !copyvector[i][j]) {
        return true;
    }
    return false;
}

void shortestpath(vector<vector<int> >& v, int row, int col, int i, int j, vector<vector<bool> >& copyvector, vector<pair<int, string> >& output, int sum, string semioutput) {
    if (i == row - 1 && j == col - 1) {
        output.push_back(make_pair(sum, semioutput));
        return;
    }

    if (issafe(v, row, col, i + 1, j, copyvector)) {
        copyvector[i + 1][j] = true;
        shortestpath(v, row, col, i + 1, j, copyvector, output, sum + v[i + 1][j], semioutput + 'D');
        copyvector[i + 1][j] = false;
    }
    if (issafe(v, row, col, i, j + 1, copyvector)) {
        copyvector[i][j + 1] = true;
        shortestpath(v, row, col, i, j + 1, copyvector, output, sum + v[i][j + 1], semioutput + 'R');
        copyvector[i][j + 1] = false;
    }

    
}

struct RatingComparator {
    bool operator()(const Location& a, const Location& b) {
        return a.rating > b.rating;
    }
};

vector<Location> filterLocations(const vector<Location>& allLocations, double budget, int age) {
    vector<Location> filteredLocations;
    for (size_t i = 0; i < allLocations.size(); ++i) {
        const Location& loc = allLocations[i];
        if (loc.cost <= budget && (age >= 18 || loc.name != "Nightclub")) {
            filteredLocations.push_back(loc);
        }
    }
    return filteredLocations;
}

vector<Location> recommendLocations(const vector<Location>& locations, int numDays, int hoursPerDay) {
    vector<Location> recommendedLocations = locations;
    sort(recommendedLocations.begin(), recommendedLocations.end(), RatingComparator());

    vector<Location> recommendedPlaces;
    int totalHours = numDays * hoursPerDay;

    for (size_t i = 0; i < recommendedLocations.size(); ++i) {
        const Location& loc = recommendedLocations[i];
        if (loc.hours <= hoursPerDay) {
            recommendedPlaces.push_back(loc);
            totalHours -= loc.hours;

            if (totalHours <= 0) {
                break; // No more hours left for the day
            }
        }
    }

    return recommendedPlaces;
}

int main() {
    string userName;

    cout << "===============================================================\n";
    cout << "                   Welcome to Trek Tactix!\n";
    cout << "     We'd love to recommend some amazing places for your trip!\n";
    cout << "===============================================================\n\n";

    cout << "Please enter your name: ";
    cin >> userName;

    double budget;
    int age, numDays, hoursPerDay;

    cout << "\nLet's get started, " << userName << "!\n\n";

    cout << "Enter your budget for the trip (in INR): ";
    cin >> budget;
    cout << "Enter your age: ";
    cin >> age;
    cout << "How many days are you planning to explore (approx): ";
    cin >> numDays;
    cout << "How many hours do you plan to hang out each day: ";
    cin >> hoursPerDay;
    cout << endl;

    vector<Location> allLocations;
    allLocations.push_back(Location("Taj Mahal, Agra", 4.6, 10000.0, 3));
    allLocations.push_back(Location("Varanasi Ghats, Varanasi", 4.5, 3000.0, 6));
    allLocations.push_back(Location("Mysore Palace, Mysore", 4.7, 15000.0, 5));
    allLocations.push_back(Location("Jaipur, Rajasthan", 4.6, 12000.0, 7));
    allLocations.push_back(Location("Goa Beaches, Goa", 4.8, 10000.0, 8));
    allLocations.push_back(Location("Amber Fort, Jaipur", 4.5, 1500.0, 6));
    allLocations.push_back(Location("Kerala Backwaters, Kerala", 4.7, 20000.0, 8));
    allLocations.push_back(Location("Qutub Minar, Delhi", 4.4, 500.0, 2));
    allLocations.push_back(Location("Hampi, Karnataka", 4.6, 1500.0, 6));
    allLocations.push_back(Location("Ajanta and Ellora Caves, Maharashtra", 4.5, 3000.0, 2));
    allLocations.push_back(Location("Rann of Kutch, Gujarat", 4.4, 5000.0, 4));
    allLocations.push_back(Location("Kaziranga National Park, Assam", 4.8, 10000.0, 5));
    allLocations.push_back(Location("Leh Ladakh, Jammu and Kashmir", 4.6, 15000.0, 6));
    allLocations.push_back(Location("Sundarbans National Park, West Bengal", 4.5, 7000.0, 7));
    allLocations.push_back(Location("Khajuraho Temples, Madhya Pradesh", 4.7, 2000.0, 5));
    allLocations.push_back(Location("Kanyakumari, Tamil Nadu", 4.6, 2000.0, 4));
    allLocations.push_back(Location("Ajmer Sharif, Rajasthan", 4.8, 500.0, 6));
    allLocations.push_back(Location("Mahabalipuram, Tamil Nadu", 4.5, 1000.0, 1));
    allLocations.push_back(Location("Manali, Himachal Pradesh", 4.6, 5000.0, 7));
    allLocations.push_back(Location("Pushkar, Rajasthan", 4.5, 3000.0, 5));
    allLocations.push_back(Location("Halebid and Belur Temples, Karnataka", 4.7, 1500.0, 7));
    allLocations.push_back(Location("Amritsar Golden Temple, Punjab", 4.8, 1500.0, 4));
    allLocations.push_back(Location("Kashmir Valley, Jammu and Kashmir", 4.6, 15000.0, 6));
    allLocations.push_back(Location("Ellora Caves, Maharashtra", 4.7, 2000.0, 5)); 
    allLocations.push_back(Location("Gir Forest National Park, Gujarat", 4.8, 5000.0, 6));
    allLocations.push_back(Location("Srinagar, Jammu and Kashmir", 4.5, 5000.0, 5));
    allLocations.push_back(Location("Hawa Mahal, Jaipur", 4.6, 1500.0, 6));
    allLocations.push_back(Location("Munnar, Kerala", 4.7, 3000.0, 3));
    allLocations.push_back(Location("Rameshwaram, Tamil Nadu", 4.6, 1500.0, 7));
    allLocations.push_back(Location("Kedarnath Temple, Uttarakhand", 4.5, 1000.0, 6));
    allLocations.push_back(Location("Andaman and Nicobar Islands", 4.8, 15000.0, 8));
    allLocations.push_back(Location("Darjeeling, West Bengal", 4.5, 7000.0, 4));
    allLocations.push_back(Location("Charminar, Hyderabad", 4.4, 1000.0, 7));
    allLocations.push_back(Location("Ajmer Sharif, Rajasthan", 4.7, 500.0, 1));
    allLocations.push_back(Location("Rishikesh, Uttarakhand", 4.6, 3000.0, 6));
    allLocations.push_back(Location("Mahabaleshwar, Maharashtra", 4.5, 2000.0, 7));
    allLocations.push_back(Location("Ooty, Tamil Nadu", 4.4, 1500.0, 2));
    allLocations.push_back(Location("Bodh Gaya, Bihar", 4.8, 1000.0, 5));
    allLocations.push_back(Location("Jaisalmer, Rajasthan", 4.5, 3000.0, 6));
    allLocations.push_back(Location("Pondicherry, Tamil Nadu", 4.6, 5000.0, 7));
    allLocations.push_back(Location("Kolkata, West Bengal", 4.7, 7000.0, 1));
    allLocations.push_back(Location("Khajuraho Temples, Madhya Pradesh", 4.6, 2000.0, 2));
    allLocations.push_back(Location("Konark Sun Temple, Odisha", 4.8, 15000.0, 3));

    vector<Location> filteredLocations = filterLocations(allLocations, budget, age);

    vector<Location> recommendedLocations = recommendLocations(filteredLocations, numDays, hoursPerDay);

    cout << "===============================================================\n";
    cout << "Dear " << userName << ", Here are the Recommended Locations for your Trip:\n";
    cout << "===============================================================\n";

    for (size_t i = 0; i < recommendedLocations.size(); ++i) {
        const Location& loc = recommendedLocations[i];
        cout << "   " << loc.name << " (Rating: " << loc.rating << ", Cost: " << loc.cost << ", Time: " << loc.hours << " hours)\n";
    }

    cout << "===============================================================\n";
    cout << "Enjoy your trip, " << userName << "!\n";
    cout << "===============================================================\n";

    int choice;

    cout << "Would you like to plan the shortest path in addition to location recommendations?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";

    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "===============================================================\n";
            cout << "Welcome to the Shortest Path Finder!\n";
            cout << "===============================================================\n";

            int row1, col1;
            cout << "Enter the number of rows: ";
            cin >> row1;
            cout << "Enter the number of columns: ";
            cin >> col1;

            vector< vector<int> > v(row1, vector<int>(col1, 0));
            cout << "\nEnter the values for the matrix:" << endl;
            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < col1; j++) {
                    cin >> v[i][j];
                }
            }

            cout << "\nMatrix:" << endl;
            for (int i = 0; i < row1; i++) {
                for (int j = 0; j < col1; j++) {
                    cout << v[i][j] << " ";
                }
                cout << endl;
            }

            int row, col;
            cout << "\nEnter the final destination row: ";
            cin >> row;
            cout << "Enter the final destination column: ";
            cin >> col;

            vector< vector<bool> > copyvector(row, vector<bool>(col, false));
            v[0][0] = true;

            int i = 0;
            int j = 0;

            vector< pair<int, string> > output;
            int sum = v[i][j];
            string smalloutput;

            shortestpath(v, row, col, i, j, copyvector, output, sum, smalloutput);

            string ans;
            int mini = INT_MAX;

            cout << "\nAll possible directions: " << endl;
            for (int i = 0; i < output.size(); i++) {
                cout << "Path: " << output[i].second << ", Sum: " << output[i].first << endl;
                if (mini > output[i].first) {
                    mini = output[i].first;
                    ans = output[i].second;
                }
            }

            cout << "===============================================================\n";
            cout << "Shortest path is: " << ans << " with a total sum of " << mini << endl;
            cout << "===============================================================\n";

            return 0;
        }
        case 2: // Continue with other operations or exit
            cout << "Thank you for using Trek Tactix. Have a great day!\n";
            break;
        default:
            cout << "Invalid choice. Exiting...\n";
            break;
    }

    return 0;
}
