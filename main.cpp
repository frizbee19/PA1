//Rizvee Ayub RNA180002

#include <iostream>
#include <string>

using namespace std;

//organizes check function
enum Part { Protocol, Host, Port };

//used to check for valid url input
const string PROT [4] = {"http", "https", "ftp", "ftps"};
const string HOST [5] = {"com", "net", "edu", "biz", "gov"};
const int PORTMAX = 65535;
const string FILEEND [2] = {".html", ".htm"};

static float version = 1.2;

void displayVersion() {
	cout << "Current version is " << version << endl;
}

//checks each part of the url
bool check(Part, string, int, int);

int main() {
	displayVersion();
    //a check to make sure that the program doesnt print information when there's an error
    bool error = false;
    //ask for user input
    string url = "";
    string output = "";
    cout << "Enter a url here: " << endl;
    cin >> url;
    //read until after protocol
    int end = url.find("//:");
    int start = 0;
    //check if protocol exists
    if(end == string::npos) {
        cout << "Invalid URL:\nProtocol:\tdoes not exist." << endl;
        error = true;
    } else {
        //check if protocol matches
        if(check(Protocol, url, start, end)) {
            output += "Protocol:\t" + url.substr(start, end - start) + "\n";
        }
        else {
            //output error if no match
            cout << "Invalid URL:\nProtocol:\t" << url.substr(start, end - start) << " protocol does not exist" << endl;
            error = true;
        }
    }
    //move the beginning to domain
    if(end != string::npos) {
        url = url.substr(end + 3);
    }
    //assume '/' is end of domain
    end = url.find("/");
    if(end == string::npos)
    {
        //if no '/', end of domain set to end of url
        end = url.length();
    }
    //if there is ':', assume that is the end of domain
    if(url.find(":") != string::npos)
    {
        end = url.find(":");
    }
    //check if domain is valid
    if(check(Host, url, start, end)){
        output += "Domain:\t\t" + url.substr(start, end - start) + "\n";
    } else {
        //output error if not valid
        cout << "Invalid URL:\nDomain:\t" << url.substr(start, end - start) << " invalid domain name." << endl;
        error = true;
    }

    //check if port exists
    if(url.find(":") != string::npos) {
        //move beginning, + 1 to make it int
        url = url.substr(url.find(":") + 1);
        //assume '/' is end of port
        end = url.find("/");
        if(end == string::npos)
        {
            //if no '/', end of domain set to end of url
            end = url.length() - 1;
        }
        //check if port is an integer
        if(check(Port, url, start, end)) {
            output += "Port:\t" + url.substr(start, end - start) + "\n";
        } else {
            //error output
            cout << "Invalid URL:\nPort:\t" << url.substr(start, end - start) << " invalid port number." << endl;
            error = true;
        }
    }

    //move the beginning to file path
    if(end != string::npos) {
        url = url.substr(end);
    }

    //stop parameter if file path is empty
    bool endPar = false;
    //check if there is file path, or if there is no filepath at all, it is still valid
    if(url[0] == '/' || url.length() == 0){
        //if only '/' or blank, still valid
        if(url.length() > 1) {
            //check for valid ".html"
            if (url.find(FILEEND[0]) != string::npos) {
                if (url.find(FILEEND[0]) + 5 == url.length() || url[url.find(FILEEND[0]) + 5] == '?') {
                    end = url.find(FILEEND[0]) + 5;
                    output += "File Path:\t" + url.substr(start, end - start) + "\n";
                } else {
                    //error if character after html not '?'
                    cout << "Invalid URL:\nFile Path:\tInvalid file path closure." << endl;
                    error = true;
                }
            } else if (url.find(FILEEND[1]) != string::npos) {
                //check for valid ".htm"
                if (url.find(FILEEND[1]) + 4 == url.length() || url[url.find(FILEEND[1]) + 4] == '?') {
                    end = url.find(FILEEND[1]) + 4;
                    output += "File Path:\t" + url.substr(start, end - start) + "\n";
                } else {
                    //error if character after htm not '?'
                    cout << "Invalid URL:\nFile Path:\tInvalid file path closure." << endl;
                    error = true;
                }

            } else {
                //error if does not end with either html or htm
                cout << "Invalid URL:\nFile Path:\tInvalid file path." << endl;
                error = true;
            }
        } else {
            endPar = true;
        }
    } else {
        cout << "Invalid URL:\nFile Path:\tdoes not exist." << endl;
        error = true;
    }

    //check parameter if everything else is valid
    if(!endPar) {
        //checks if '?' is in string, optional
        if(url.find("?") != string::npos){
            //move beginning of url
            url = url.substr(url.find("?"));
            //makes sure format is right
            if(url.length() > 1 && url.find("=") != string::npos && url.find("=") != 1 && url.find("=") != url.length() - 1) {
                output += "Parameters:\t" + url.substr(1) + "\n";
            }
            else
            {
                //output error
                cout << "Invalid URL:\nParameters:\tInvalid parameter format" << endl;
                error = true;
            }
        }
    }

    //prints info if everything is valid
    if(!error)
    {
        cout << output << endl;
    }

    return 0;
}

bool check(Part part, string url, int start, int end) {
    //for checking if domain is divided correctly
    int count = 0;
    //for checking port validity
    bool isInt = true;
    //isolates the element
    string segment = url.substr(start, end - start);
    bool check = false;
    //checks based on the type of element
    switch (part) {
        case Protocol:
            //loops through list of calid protocols for check
            for(int i = 0; i < 4; i++) {
                if (segment == PROT[i])
                    check = true;
            }
            break;
        case Host:
            //counts amount of dots in domain name, must be 2
            for(int i = 0; i < segment.length(); i++)
            {
                if(segment[i] == '.') {
                    count++;
                }
            }
            if(count == 2){
                //makes sure that the dots are not next to each other, if it is valid
                if(segment[0] != '.' && segment.find(".") + 1 != segment.find(".", segment.find(".") + 1)){
                    //isolates the host
                    segment = segment.substr(segment.find(".", segment.find(".") + 1) + 1);
                    //compares input host to list
                    for(int i = 0; i < 5; i++) {
                        if(segment == HOST[i])
                            check = true;
                    }
                }
            }
            break;
        case Port:
            //check if port is valid int
            if(segment.length() > 0) {
                for (int i = 0; i < segment.length(); i++) {
                    if (!isdigit(segment[i])) {
                        isInt = false;
                    }
                }
                //convert string to int
                if (isInt) {
                    int portNum = stoi(segment);
                    //checks if port number is between 1 and 65535
                    if (portNum >= 1 && portNum <= PORTMAX)
                        check = true;
                }
            }
            break;
    }
    return check;
}
