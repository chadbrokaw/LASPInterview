# LASPInterview
Creator: Chad Brokaw
This program was created for a coding interview by LASP.

The language used was C++ and the libraries used are:
    iostream <br/>
    fstream <br/>
    sstream <br/>
    cmath <br/>

The purpose of this program was to read a csv file containing characteristics regarding kerbals. Then, take this data and output it in either XML or JSON format. A seperate option for this program involved a Transform, which changes the values of stupidity and courage.

## Build and run the code
The function requires three command-line arguments. These are: <br/>
    1.)  A csv file containing the relevant and properly formatted Kerbal data. <br/>
    2.) Either "xml" or "json" depending on which you prefer. You are allowed to select one or the other, but not both. <br/>
    3.) Either "true" or "false" depending on if you want the transform option commited. <br/>

### To compile in the command line
g++ -std=c++11 BrokawLASPInterview.cpp -o main

### To run:
./main <.csv file> <xml/json> <true/false> <br/>
Example: ./main kerbals.csv XML TRUE <br/>
(This would output the Kerbal data as XML, with the transform.)


    
    
