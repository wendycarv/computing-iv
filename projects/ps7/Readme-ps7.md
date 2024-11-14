# PS7: Kronos Log Parsing

## Contact
Name: Wendy Carvalho
Section: 202
Time to Complete: 6 hours


## Description
This project takes a log produced by the Kronos InTouch time clock and creates a report with the startup times for each bootup and their completed times (if they were completed). If the bootups were unsuccessful, it also says this in the report. This is done by reading in each line from the log file and comparing it to regexes that have the expected startup and success messages. Depending on if and what regexes are found in the file, output that describes successful bootups and incomplete bootups are saved in the report. The report also includes what lines these events happen at in the logs.

### Features
My major decisions included using std::regex_search(line, re) because I was reading the log file line by line and I wanted to match each line to one of the two regexes I created, one for the startup message and the other for the success message. 

I also used a bool called booting, making it true when a startup message was found and only changing it to false once a corresponding success message was found. Any other time the program finds the bool to be true, it considers it an incomplete bootup. I figured this would be the easiest way to keep track of incomplete bootups.

Then came getting the elapsed time. I used the line the program is looking at to compare to the regex to capture the date and time stamps. I get a substring from the line and assign it to a variable called timestamp for readability. I also saved the day using a substring. I used both of these to create a ptime, which offers construction from a time_duration, which would in the end be able to give me the time elapsed in milliseconds. So, using the day substring, I created a date, which would be considered the "starting" point for ptime when using its constructor from a date and offset (since the date is considered to have an initial time of 00:00:00). Then, I used substring of the timestamp substring to capture the hours, minutes, and seconds of the startup time and the completed time inside time_duration(), which, in turn, was used in the ptime constructor. I did this for both the startup times and the completed bootup time, in the event that they correlate (when it's not an incomplete boot). Only then does the program subtract these ptimes from each other to construct a time_duration (which is a class). This, in turn, can be displayed in milliseconds, which is what is saved in the file. 

### Approach
I first approached this project by figuring out how to use regexes to read in small strings, and then moved on to identifying the startup message (log.c.166). Then I started keeping track of the line numbers and outputting this along with the startup message and piping things into an ofstream using a stringstream. I did the same with the message indicating that the startup was completed. I accounted for the incomplete bootups by using a bool to keep track of whether a bootup had started and completed and if statements. After setting up these if statements to keep track of startups, I started trying to figure out how to see the time duration for each bootup. This involved doing lots of researching on the date and time library and converting strings to dates and times and doing the math for these. 

### Regex
The regexes I used were made from strings I made while trying to break it into pieces and figure out which parts were accurately identifying something in the logs. I then kept it separated for readability.

std::string _date = "\\d{4}-\\d{2}-\\d{2}\\s";

In _date, \\d{4} matches exactly four digits, representing the year. - matches a hyphen. \\d{2} matches exactly two digits, representing the month. - matches another hyphen. \\d{2} matches exactly two digits, representing the day.\\s matches any whitespace character after the date, as there are white spaces after the date in the logs.

std::string _time = "\\d{2}:\\d{2}:\\d{2}[:.]";

In _time, \\d{2} matches exactly two digits, representing the hour. The ":" match a colon separating each part of the time. \\d{2} matches exactly two digits, representing the minute.\\d{2} matches exactly two digits, representing the second. Lastly, [:.] matches either a colon or a dot after the time, which differs in the startup message and the success message, so I accounted for either here.

std::string _start = "\\s(.*log.c.166.*)";
In _start, \\s matches any whitespace character. I put this here instead of in the time because the success message does not have this extra space after the time. The parentheses are capturing a group. .* matches any character zero or more times. log.c.166 matches the string "log.c.166" exactly.

std::string _success = "\\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector";
In _success, \\d{3} matches exactly three digits, the three numbers that come after the time in the success message. :INFO:oejs.AbstractConnector:Started SelectChannelConnector matches this specific string exactly in the success message.

In std::regex re(_date + _time + _start) I concatenate _date, _time, and _start, and look for this full std::regex inside the log line by line using std::regex_search. I do the same with std::regex reDone(_date + _time + _success), the only difference being I'm looking for the success message instead here.

I created two additional regexes for the extra credit that involved identifiying each individual service:

std::regex serviceStart("Starting Service\\.\\s\\s([A-Za-z]+)\\s(\\d+(?:\\.\\d+)*)");
Here, "Starting Service\\." matches the literal string "Starting Service." \\s\\s matches two whitespace characters. ([A-Za-z]+) captures a group that matches one or more alphabetic characters (uppercase or lowercase) for the service name. (\\d+(?:\\.\\d+)*) is another capturing group that matches the version number. \\d+ matches one or more digits.(?: ... ) matches zero or more occurrences of a dot followed by one or more digits. This allows for versions with additional dot-separated numbers.

std::regex serviceDone("Service started successfully\\.\\s\\s([A-Za-z]+)\\s(\\d+(?:\\.\\d+)*)\\s(.(\\d+)\\s(ms).)");
This regex is almost identicaly to serviceStart, but it has different starting literal string and it captures an additional group that matches the time in milliseconds: .(\\d+)\\s(ms). \\d+ captures 1 or more digits for the time, \\s matches a whitespace, and (ms) matches literally "(ms)".

### Issues
Everything seems to work as expected. I had trouble at first figuring out how regexes worked, specifically when trying to identify certain characters and making sure to use (), [], ., and * when appropriate. But I eventually figured this out with the help of the slides and cplusplus.com.

I also had an issue with the autograder timing out, but this was because I was creating my regex inside my while loop, which is costly. This was fixed after I created it outside the while loop.

### Extra Credit
I added a summary header to show up for every log file that specifies the file name of the log and how many lines were scanned.

I also included the start and complete time for each individual service for additional credit. I did this by creating a map of the service name and a stringstream that got updated with its start and completed time. I then output this to the "boots" stringstream when updating the report every time a bootup was completed successfully. I also used the additional parameter for regex_search, "match" to get the service name and milliseconds it took for the service to finish. 

## Acknowledgements
More info on regexes: https://cplusplus.com/reference/regex/ECMAScript/
Searching files for regexes: https://stackoverflow.com/questions/40838504/how-to-search-a-txt-file-for-regex
Remembering how to convert a string to an int: https://www.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example/
Date_Time: https://www.boost.org/doc/libs/1_57_0/doc/html/date_time/examples.html#date_time.examples.time_math
Posix Time System: https://www.boost.org/doc/libs/1_57_0/doc/html/date_time/posix_time.html#date_time.posix_time.time_duration
https://stackoverflow.com/questions/478075/creating-files-in-c
