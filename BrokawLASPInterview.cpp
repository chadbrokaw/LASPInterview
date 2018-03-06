#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;


struct KerbalIdentity;
KerbalIdentity* readFile(string fileName, bool transform_);
KerbalIdentity* generateList(int id_, string firstName_, string lastName_, string job_, int level_,
                             int isFemale_, int courage_, int stupidity_, int badS_, KerbalIdentity* headPtr);
void printJSONList(KerbalIdentity* headPtr);
void printXMLList(KerbalIdentity* headPtr);

//We will use PI in the transform option, it is defined here for simplicity
#define PI 3.14159265

int main(int argc, char* argv[])
{
    if(argc != 4) //Verify that there are enough arguments passed to the program
    {
        cout << "Usage One: Please enter csv file" << endl;  //ex: kerbals.csv
        cout << "Usage Two: Please enter either 'JSON' or 'XML'" << endl;
        cout << "Usage Three: Please enter 'true' or 'false' for transform option" << endl;
        return 0; //If there are insufficient arguments given, program ends
    }

    string fileName = argv[1];
    string outputType = argv[2];
    string transformOption = argv[3]; //Arguments assigned to variables for simplicity


    KerbalIdentity* head = nullptr; //We will be using a singly linked list to store the date, here is the head pointer

    bool transform = false; //The assumption is the transform will not occur

    if(transformOption.compare("true") || transformOption.compare("TRUE"))
    {
        transform = true; //The transform has been selected, it has been turned to true.
    }

    head = readFile(fileName, transform); //We will now read in the file, JUMP readFile

    if(head == nullptr)
    {
        return 0; //If there is nothing in the file, then we will exit here
    }

    if(!outputType.compare("JSON") || !outputType.compare("json")) //The user has selected the JSON output format
    {
        printJSONList(head); //JUMP to printJSONList
    }
    else if(!outputType.compare("XML")|| !outputType.compare("xml")) //The user has selected the XML output format
    {
        printXMLList(head); //JUMP to printXMLList
    }
    else
    {
        cout << "Invalid print option entered." << endl;
    }
    return 0;
}

/*
 * Name: KerbalIdentity
 * Type: struct, singly-linked-list node
 * Purpose: To store all the information regarding a single kerbal (one line in the csv file). Also to store the pointer
 *      to the next struct in the singly linked list (or nullptr, if it is the last one)
 * Values:
 *      All values have been initialized to be empty or zero.
 */
struct KerbalIdentity
{
    int id = 0;
    string firstName = "";
    string lastName = "";
    string job = "";
    int level = 0;
    int isFemale = 0;
    int courage = 0;
    int stupidity = 0;
    int badS = 0;

    KerbalIdentity* next = nullptr;
};

/*
 * Name: readFile
 * Type: Function
 * Return type: KerbalIdentity*
 * Purpose: This function reads in the data from the provided csv file and calls the function to generate a struct based
 *      on that data. This function also maintains the head pointer. If the option is selected, the transform math is also
 *      done here.
 * @param STRING fileName - The name of the file that will be opened and read using fstream/sstream and getline
 * @param BOOL transform_ - True: The user has selected to transform the courage and stupidity values
 *                          False: The user has selected to not transform the courage and stupidity values
 * Return: KerbalIdentity pointer - The pointer to the head of the singly linked list of KerbalIdentity structs
 */

KerbalIdentity* readFile(string fileName, bool transform_)
{
    ifstream csvFile;
    csvFile.open(fileName); //Open the file as a stream, name of the stream is csvFile

    if(!csvFile.is_open())
    {
        cout << "Error opening file. I'm sorry." << endl;
        return nullptr; //Return nullptr if the file is unable to be opened.
    }

    string line;
    string ignore;
    getline(csvFile, ignore); //Gathers the first line with the labels, ignores this

    //Establishes all the variables that will be used to hold the various attributes. String versions have been marked.
    string id_s, firstName_, lastName_, job_, level_s, isFemale_s, courage_s, stupidity_s, BadS_s;

    KerbalIdentity* head = nullptr; //Establishes a pointer that will hold the head

    while(getline(csvFile, line)) //Gathers a line, the while loop will continue until there are no more lines
    {
        stringstream lineStream(line); //Convert the line to a stream

        //The getlines are parsing the line to gather the relevant information. We must also remove the quotations so there
        //are extra getlines to do so.
        getline(lineStream, id_s, ',');
        getline(lineStream,ignore,'"');
        getline(lineStream, firstName_, '"');
        getline(lineStream, ignore, '"');
        getline(lineStream, lastName_, '"');
        getline(lineStream, ignore, '"');
        getline(lineStream, job_,'"');
        getline(lineStream, ignore, ',');

        getline(lineStream, level_s, ',');
        getline(lineStream, isFemale_s, ',');
        getline(lineStream, courage_s, ',');
        getline(lineStream, stupidity_s, ',');
        getline(lineStream, BadS_s);

        if(transform_) //If the user wishes to transform stupidity and courage
        {
            double courage_d, stupidity_d = 0;

            courage_d = stod(courage_s);
            stupidity_d = stod(stupidity_s); //Generate versions of the variables that are doubles

            courage_d = tan(courage_d* PI / 100.0 - PI/2);
            stupidity_d = tan(stupidity_d* PI / 100.0 - PI/2); //Do the relevant math from the cmath library. PI declared above

            //Call the function to create a node and return the refreshed head. Doubles casted to Ints to maintain the function
            head = generateList(stoi(id_s), firstName_, lastName_,  job_, stoi(level_s), stoi(isFemale_s),
                                int(courage_d), int(stupidity_d), stoi(BadS_s), head);
        }
        else //The user does not want to transform
        {
            //gives the variables to the function. Casting Strings to Ints to maintain the function
            head = generateList(stoi(id_s), firstName_, lastName_,  job_, stoi(level_s), stoi(isFemale_s),
                                stoi(courage_s), stoi(stupidity_s), stoi(BadS_s), head);
        }


    }

    return head; //Return the head after all the linked-list is completed
}

/*
 * Name: generateList
 * Type: Function
 * Return Type: KerbalIdentity*
 * Purpose: This function dynamically creates a new KerbalIdentity struct and fills it with the information given to it.
 *          It then adds the nre struct to the linked-list and generates a new head. This function is called for every line
 *          in the csv file.
 * @param INT id_ - ID of the kerbal
 * @param STRING firstName_ - First name of the kerbal
 * @param STRING lastName_ - Last name of the kerbal
 * @param STRING job_ - The job of the kerbal
 * @param INT level_ - The level of the kerbal
 * @param INT isFemale_ - 0 or 1 depending on if the kerbal is female or not.
 * @param INT courage_ - The level of courage of the kerbal
 * @param INT stupidity_ - The level of stupidity of the kerbal
 * @param INT badS_ - Identity characteristic of badS for the kerbal
 * @param KerbalIdentity* headPtr - Pointer to the current head of the linked list. Can be nullptr.
 *
 * Return: The function returns the address of the pointer just generated. This pointer is the new head of the linked list.
 *         The preveious head is now the second in the linked-list.
 */

KerbalIdentity* generateList(int id_, string firstName_, string lastName_, string job_, int level_, int isFemale_, int courage_, int stupidity_, int badS_, KerbalIdentity* headPtr)
{

    KerbalIdentity* kerbalIdentity = new KerbalIdentity; //Dynamically generate a new struct

    //Input all of the relevant details into the new struct.
    kerbalIdentity->id = id_;
    kerbalIdentity->firstName = firstName_;
    kerbalIdentity->lastName = lastName_;
    kerbalIdentity->job = job_;
    kerbalIdentity->level = level_;
    kerbalIdentity->courage = courage_;
    kerbalIdentity->stupidity = stupidity_;
    kerbalIdentity->badS = badS_;
    kerbalIdentity->isFemale = isFemale_;

    kerbalIdentity->next = headPtr; //The previous head becomes the new node's next pointer

    return(kerbalIdentity); //Return the pointer to the new struct which is the new head.
}

/*
 * Name: printJSONList
 * Type; Function
 * Return Type: VOID
 * Purpose: This function generates the JSON output format. It will print everything in the linked list and then stops.
 * @param KerbalIdentity* headPtr - A pointer to the head of the linked-list. If nullptr, then nothing will print.
 * Return: There is no return for this function.
 */

void printJSONList(KerbalIdentity* headPtr)
{
    cout << "{\"Kerbals\":[" << endl; //Begins the first line
    while(headPtr!= nullptr) //For each node, it generates a new portion of the JSON
    {
        cout << "\t { \"ID\":\"" << headPtr->id << "\"" "," << endl;
        cout << "\t\"First Name\":\"" << headPtr->firstName << "\"" "," << endl;
        cout << "\t\"Last Name\":\"" << headPtr->lastName << "\"" "," << endl;
        cout << "\t\"Job\":\"" << headPtr->job << "\"" "," << endl;
        cout << "\t\"Level\":\"" << headPtr->level << "\"" "," << endl;
        cout << "\t\"isFemale\":\"" << headPtr->isFemale << "\"" "," << endl;
        cout << "\t\"Courage\":\"" << headPtr->courage << "\"" "," << endl;
        cout << "\t\"Stupidity\":\"" << headPtr->stupidity << "\"" "," << endl;
        cout << "\t\"BadS\":\"" << headPtr->badS << "\" }";

        if(headPtr->next != nullptr)
        {
            cout << ","; //This prevents a comma after the last element
        }

        headPtr = headPtr->next; //Increment the pointer
    }
    cout << "]}" << endl; //Finish
}
/*
 * Name: printXMLList
 * Type; Function
 * Return Type: VOID
 * Purpose: This function outputs the data to the terminal in XML format. It will print everythin in the linked-list
 *          and then stop.
 * @param KerbalIdentity* headPtr - A pointer to the head of the linked-list. If nullptr, then nothing will print.
 * Return: There is no return for this function.
 */

void printXMLList(KerbalIdentity* headPtr)
{
    cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl; //First line
    cout << "<Kerbals>" << endl; //Begins the Kerbals set
    while(headPtr != nullptr)
    {
        cout << "\t<Kerbal>" << endl;
        cout << "\t\t<ID>" << headPtr->id << "</ID>" << endl;
        cout << "\t\t<FirstName>" << headPtr->firstName << "</FirstName>" << endl;
        cout << "\t\t<LastName>" << headPtr->lastName << "</LastName>" << endl;
        cout << "\t\t<Job>" << headPtr->job << "</Job>" << endl;
        cout << "\t\t<Level>" << headPtr->level << "</Level>" << endl;
        cout << "\t\t<isFemale>" << headPtr->isFemale << "</isFemale>" << endl;
        cout << "\t\t<Courage>" << headPtr->courage << "</Courage>" << endl;
        cout << "\t\t<Stupidity>" << headPtr->stupidity << "</Stupidity>" << endl;
        cout << "\t\t<BadS>" << headPtr->badS << "</BadS>" << endl;
        cout << "\t</Kerbal>" << endl; //Outputs the data in the correct format

        headPtr = headPtr->next; //Increment the pointer
    }
    cout << "</Kerbals>" << endl; //Final end tag

}

